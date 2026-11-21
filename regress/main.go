package main

import (
	"bytes"
	"context"
	"encoding/binary"
	"encoding/json"
	"flag"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"sort"
	"strings"
	"time"
)

type Case struct {
	Source   string
	Expected []string
	Args     []string
	Problems []string
}
type Result struct {
	Source  string
	Status  string
	Exit    int
	Details []string
	Ignored []string
}
type Report struct {
	Assembler                  string
	Results                    []Result
	Passed, Failed, Incomplete int
}

var errorDiagnostic = regexp.MustCompile(`(?i)\berror A[0-9]+`)

func main() { os.Exit(run()) }
func run() int {
	rootFlag := flag.String("root", ".", "suite directory containing src, exp and groups.json")
	asmFlag := flag.String("asm", "", "assembler (default: ../x64/Release/UASM.exe)")
	filter := flag.String("filter", "", "case-insensitive source-path substring")
	audit := flag.Bool("audit", false, "report missing baselines/configuration without running or clearing results")
	timeout := flag.Duration("timeout", 30*time.Second, "maximum time per assembly")
	flag.Parse()
	root, err := filepath.Abs(*rootFlag)
	if err != nil {
		fmt.Println(err)
		return 2
	}
	cases, notes, err := discover(root, *filter)
	if err != nil {
		fmt.Println(err)
		return 2
	}
	for _, n := range notes {
		fmt.Println("AUDIT", n)
	}
	incomplete := 0
	for _, c := range cases {
		if len(c.Problems) > 0 {
			incomplete++
			fmt.Printf("INCOMPLETE %s: %s\n", c.Source, strings.Join(c.Problems, "; "))
		}
	}
	fmt.Printf("Audit: %d sources, %d ready, %d incomplete\n", len(cases), len(cases)-incomplete, incomplete)
	if len(cases) == 0 {
		return 2
	}
	if *audit {
		if incomplete > 0 {
			return 1
		}
		return 0
	}
	asm := *asmFlag
	if asm == "" {
		asm = filepath.Join(root, "..", "x64", "Release", "UASM.exe")
	}
	asm, err = filepath.Abs(asm)
	if err != nil {
		fmt.Println(err)
		return 2
	}
	if info, e := os.Stat(asm); e != nil || info.IsDir() {
		fmt.Printf("Assembler not found: %s\n", asm)
		return 2
	}
	results := filepath.Join(root, "results")
	if err = clearResults(root, results); err != nil {
		fmt.Println(err)
		return 2
	}
	report := Report{Assembler: asm}
	for _, c := range cases {
		r := Result{Source: c.Source, Exit: -1}
		if len(c.Problems) > 0 {
			r.Status = "INCOMPLETE"
			r.Details = c.Problems
			report.Incomplete++
		} else {
			r = assemble(root, results, asm, c, *timeout)
			if r.Status == "PASS" {
				report.Passed++
			} else {
				report.Failed++
			}
			fmt.Printf("%s %s", r.Status, c.Source)
			if len(r.Details) > 0 {
				fmt.Printf(": %s", strings.Join(r.Details, "; "))
			}
			if len(r.Ignored) > 0 {
				fmt.Printf(" [ignored %s]", strings.Join(r.Ignored, ", "))
			}
			fmt.Println()
		}
		report.Results = append(report.Results, r)
	}
	data, err := json.MarshalIndent(report, "", "  ")
	if err == nil {
		err = os.WriteFile(filepath.Join(results, "report.json"), append(data, '\n'), 0644)
	}
	if err != nil {
		fmt.Println(err)
		return 2
	}
	fmt.Printf("\n%d passed, %d failed, %d incomplete. Failed artifacts and report: %s\n", report.Passed, report.Failed, report.Incomplete, results)
	if report.Failed+report.Incomplete > 0 {
		return 1
	}
	return 0
}

func discover(root, filter string) ([]Case, []string, error) {
	data, err := os.ReadFile(filepath.Join(root, "groups.json"))
	if err != nil {
		return nil, nil, err
	}
	groups := map[string][]string{}
	if err = json.Unmarshal(data, &groups); err != nil {
		return nil, nil, err
	}
	expected := map[string][]string{}
	used := map[string]bool{}
	var notes []string
	err = filepath.WalkDir(filepath.Join(root, "exp"), func(p string, d os.DirEntry, e error) error {
		if e != nil {
			return e
		}
		if d.IsDir() {
			return nil
		}
		rel, _ := filepath.Rel(filepath.Join(root, "exp"), p)
		ext := strings.ToLower(filepath.Ext(rel))
		if ext != ".bin" && ext != ".err" && ext != ".obj" && ext != ".o" && ext != ".exe" {
			return nil
		}
		key := strings.ToLower(strings.TrimSuffix(rel, filepath.Ext(rel)))
		expected[key] = append(expected[key], rel)
		return nil
	})
	if err != nil {
		return nil, nil, err
	}
	var cases []Case
	seenGroups := map[string]bool{}
	err = filepath.WalkDir(filepath.Join(root, "src"), func(p string, d os.DirEntry, e error) error {
		if e != nil {
			return e
		}
		if d.IsDir() {
			if d.Name() == ".vs" {
				return filepath.SkipDir
			}
			return nil
		}
		if !strings.EqualFold(filepath.Ext(p), ".asm") {
			return nil
		}
		rel, _ := filepath.Rel(filepath.Join(root, "src"), p)
		group := strings.ToLower(filepath.Dir(rel))
		seenGroups[group] = true
		key := strings.ToLower(strings.TrimSuffix(rel, filepath.Ext(rel)))
		used[key] = true
		if !strings.Contains(strings.ToLower(filepath.ToSlash(rel)), strings.ToLower(filter)) {
			return nil
		}
		c := Case{Source: rel, Expected: expected[key], Args: groups[group]}
		sort.Strings(c.Expected)
		if len(c.Expected) == 0 {
			c.Problems = append(c.Problems, "no EXP entry")
		}
		if len(c.Args) == 0 {
			c.Problems = append(c.Problems, "no assembler command in groups.json (not in legacy runner)")
		}
		cases = append(cases, c)
		return nil
	})
	if err != nil {
		return nil, nil, err
	}
	if filter == "" {
		for key, files := range expected {
			if !used[key] {
				notes = append(notes, "orphan expectation: "+strings.Join(files, ", "))
			}
		}
		for group := range groups {
			if !seenGroups[group] {
				notes = append(notes, "configured group has no ASM sources: "+group)
			}
		}
	}
	sort.Slice(cases, func(i, j int) bool { return strings.ToLower(cases[i].Source) < strings.ToLower(cases[j].Source) })
	sort.Strings(notes)
	return cases, notes, nil
}

// Only clear the named results directory under the absolute suite root.
// Refuse symlinks/junctions before recursive deletion.
func clearResults(root, target string) error {
	if !filepath.IsAbs(root) || target != filepath.Join(root, "results") {
		return fmt.Errorf("unsafe results path: %s", target)
	}
	for _, name := range []string{".", "src", "exp"} {
		if s, e := os.Lstat(filepath.Join(root, name)); e != nil || !s.IsDir() || s.Mode()&os.ModeSymlink != 0 {
			return fmt.Errorf("not a suite root: %s", root)
		}
	}
	if _, e := os.Lstat(target); e == nil {
		e = filepath.WalkDir(target, func(p string, d os.DirEntry, e error) error {
			if e != nil {
				return e
			}
			if d.Type()&os.ModeSymlink != 0 {
				return fmt.Errorf("refusing link in results: %s", p)
			}
			return nil
		})
		if e != nil {
			return e
		}
		if e = os.RemoveAll(target); e != nil {
			return e
		}
	} else if !os.IsNotExist(e) {
		return e
	}
	return os.MkdirAll(target, 0755)
}

func assemble(root, results, asm string, c Case, timeout time.Duration) Result {
	r := Result{Source: c.Source, Status: "FAIL", Exit: -1}
	stem := strings.TrimSuffix(filepath.Base(c.Source), filepath.Ext(c.Source))
	args := make([]string, len(c.Args))
	for i, a := range c.Args {
		args[i] = strings.ReplaceAll(a, "{stem}", stem)
	}
	// Preserve legacy relative source paths in diagnostics, including original case.
	args = append(args, filepath.Join("..", "src", c.Source))
	ctx, cancel := context.WithTimeout(context.Background(), timeout)
	defer cancel()
	cmd := exec.CommandContext(ctx, asm, args...)
	cmd.Dir = results
	for _, v := range os.Environ() {
		if !strings.HasPrefix(strings.ToUpper(v), "UASM=") {
			cmd.Env = append(cmd.Env, v)
		}
	}
	output, runErr := cmd.CombinedOutput()
	if cmd.ProcessState != nil {
		r.Exit = cmd.ProcessState.ExitCode()
	}
	if ctx.Err() != nil {
		r.Details = append(r.Details, "assembler timed out")
	} else if runErr != nil && r.Exit != 1 {
		r.Details = append(r.Details, fmt.Sprintf("assembler failed: %v", runErr))
	}
	wantExit := 0
	expectedNames := map[string]bool{}
	for _, rel := range c.Expected {
		want, e := os.ReadFile(filepath.Join(root, "exp", rel))
		if e != nil {
			r.Details = append(r.Details, e.Error())
			continue
		}
		ext := strings.ToLower(filepath.Ext(rel))
		if ext == ".err" && errorDiagnostic.Match(want) {
			wantExit = 1
		}
		name := stem + ext
		if ext == ".o" {
			name = stem + ".obj"
		}
		expectedNames[strings.ToLower(name)] = true
		got, e := os.ReadFile(filepath.Join(results, name))
		if os.IsNotExist(e) && len(want) == 0 && ext == ".err" {
			continue
		}
		if e != nil {
			r.Details = append(r.Details, "missing output "+name)
			continue
		}
		diff, ignored := compare(got, want, ext)
		if diff != "" {
			r.Details = append(r.Details, name+": "+diff)
		}
		for _, x := range ignored {
			r.Ignored = append(r.Ignored, name+": "+x)
		}
	}
	if r.Exit != wantExit {
		r.Details = append(r.Details, fmt.Sprintf("exit %d, expected %d", r.Exit, wantExit))
	}
	entries, e := os.ReadDir(results)
	if e != nil {
		r.Details = append(r.Details, e.Error())
	}
	var artifacts []string
	for _, entry := range entries {
		if entry.IsDir() || entry.Name() == "report.json" {
			continue
		}
		artifacts = append(artifacts, entry.Name())
		if !expectedNames[strings.ToLower(entry.Name())] {
			r.Details = append(r.Details, "unexpected output "+entry.Name())
		}
	}
	if len(r.Details) == 0 {
		r.Status = "PASS"
		for _, name := range artifacts {
			if e := os.Remove(filepath.Join(results, name)); e != nil {
				r.Status = "FAIL"
				r.Details = append(r.Details, e.Error())
			}
		}
		return r
	}
	dest := filepath.Join(results, filepath.Dir(c.Source), stem)
	if e := os.MkdirAll(dest, 0755); e != nil {
		r.Details = append(r.Details, e.Error())
		return r
	}
	for _, name := range artifacts {
		if e := os.Rename(filepath.Join(results, name), filepath.Join(dest, name)); e != nil {
			r.Details = append(r.Details, e.Error())
		}
	}
	log := fmt.Sprintf("Assembler: %s\nArguments: %q\nExit: %d\nExpected: %v\n%s\n\n%s", asm, args, r.Exit, c.Expected, strings.Join(r.Details, "\n"), output)
	if e := os.WriteFile(filepath.Join(dest, "run.txt"), []byte(log), 0644); e != nil {
		r.Details = append(r.Details, e.Error())
	}
	return r
}

// Locate only a structurally plausible COFF timestamp. ELF, Mach-O and MZ
// receive no exclusions. C13 metadata is handled separately below.
func timestampOffset(b []byte, ext string) int {
	offset := 0
	if ext == ".exe" {
		if len(b) < 64 || string(b[:2]) != "MZ" {
			return -1
		}
		pe := uint64(binary.LittleEndian.Uint32(b[60:64]))
		if pe+24 > uint64(len(b)) {
			return -1
		}
		offset = int(pe) + 4
		if string(b[int(pe):offset]) != "PE\x00\x00" {
			return -1
		}
	} else if ext != ".obj" {
		return -1
	}
	if len(b) < offset+20 {
		return -1
	}
	h := b[offset:]
	machine := binary.LittleEndian.Uint16(h)
	if machine != 0x14c && machine != 0x8664 {
		return -1
	}
	sections := int(binary.LittleEndian.Uint16(h[2:]))
	optional := int(binary.LittleEndian.Uint16(h[16:]))
	if sections == 0 || offset+20+optional+sections*40 > len(b) {
		return -1
	}
	return offset + 4
}
func compare(got, want []byte, ext string) (string, []string) {
	var cvIgnored bool
	if ext == ".obj" && !bytes.Equal(got, want) {
		cg, eg := canonicalCV8(got)
		cw, ew := canonicalCV8(want)
		if eg == nil && ew == nil {
			cvIgnored = !bytes.Equal(cg, got) || !bytes.Equal(cw, want)
			got, want = cg, cw
		}
	}
	a, b := timestampOffset(got, ext), timestampOffset(want, ext)
	var ignored []string
	if cvIgnored {
		ignored = append(ignored, "CV8 object/cwd/exe paths and backend version (derived layout adjusted)")
	}
	if a >= 0 && a == b && !bytes.Equal(got[a:a+4], want[b:b+4]) {
		ignored = append(ignored, "COFF timestamp")
	}
	n := len(got)
	if len(want) < n {
		n = len(want)
	}
	for i := 0; i < n; i++ {
		if a >= 0 && a == b && i >= a && i < a+4 {
			continue
		}
		if got[i] != want[i] {
			return fmt.Sprintf("first difference at 0x%X: actual %02X, expected %02X (sizes %d/%d)", i, got[i], want[i], len(got), len(want)), ignored
		}
	}
	if len(got) != len(want) {
		return fmt.Sprintf("length differs: actual %d, expected %d; first difference at 0x%X", len(got), len(want), n), ignored
	}
	return "", ignored
}
