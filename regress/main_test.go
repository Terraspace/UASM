package main

import (
	"encoding/binary"
	"os"
	"path/filepath"
	"testing"
)

func coff() []byte {
	b := make([]byte, 64)
	binary.LittleEndian.PutUint16(b, 0x8664)
	binary.LittleEndian.PutUint16(b[2:], 1)
	copy(b[20:], ".text")
	b[60] = 0xc3
	return b
}
func TestComparison(t *testing.T) {
	original := coff()
	stamp := append([]byte(nil), original...)
	stamp[4] = 99
	if d, ignored := compare(stamp, original, ".obj"); d != "" || len(ignored) != 1 {
		t.Fatal(d, ignored)
	}
	for _, offset := range []int{0, 8, 16, 20, 60} {
		modified := append([]byte(nil), stamp...)
		modified[offset] ^= 1
		if d, _ := compare(modified, original, ".obj"); d == "" {
			t.Fatalf("missed change at %d", offset)
		}
	}
	for _, ext := range []string{".bin", ".err", ".o"} {
		if d, _ := compare(stamp, original, ext); d == "" {
			t.Fatal("masked bytes in", ext)
		}
	}
	if d, _ := compare([]byte("a\r\n"), []byte("a\n"), ".err"); d == "" {
		t.Fatal("normalized line endings")
	}
	if d, _ := compare([]byte{1}, []byte{1, 2}, ".bin"); d == "" {
		t.Fatal("missed truncation")
	}
	if d, _ := compare([]byte{1, 2}, []byte{1}, ".bin"); d == "" {
		t.Fatal("missed extra byte")
	}
	// ELF/Mach-O data renamed .obj must not have any bytes masked.
	for _, magic := range [][]byte{{0x7f, 'E', 'L', 'F'}, {0xcf, 0xfa, 0xed, 0xfe}} {
		a := coff()
		copy(a, magic)
		b := append([]byte(nil), a...)
		b[4]++
		if d, _ := compare(a, b, ".obj"); d == "" {
			t.Fatal("masked non-COFF header")
		}
	}
}
func TestPETimestamp(t *testing.T) {
	a := make([]byte, 128)
	copy(a, "MZ")
	binary.LittleEndian.PutUint32(a[60:], 64)
	copy(a[64:], "PE\x00\x00")
	copy(a[68:], coff())
	b := append([]byte(nil), a...)
	b[72] = 1
	if d, _ := compare(a, b, ".exe"); d != "" {
		t.Fatal(d)
	}
	b[100] = 1
	if d, _ := compare(a, b, ".exe"); d == "" {
		t.Fatal("missed PE section change")
	}
}
func TestAuditAndCleanup(t *testing.T) {
	root := t.TempDir()
	for _, dir := range []string{"src/g", "exp/g", "results/failed"} {
		if e := os.MkdirAll(filepath.Join(root, dir), 0755); e != nil {
			t.Fatal(e)
		}
	}
	for name, body := range map[string]string{"groups.json": `{"g":["-bin"]}`, "src/g/a.asm": "end", "src/g/b.asm": "end", "exp/g/A.BIN": "x", "results/failed/old.bin": "x"} {
		if e := os.WriteFile(filepath.Join(root, name), []byte(body), 0644); e != nil {
			t.Fatal(e)
		}
	}
	cases, _, err := discover(root, "")
	if err != nil || len(cases) != 2 || len(cases[0].Problems) != 0 || len(cases[1].Problems) != 1 {
		t.Fatal(cases, err)
	}
	if e := clearResults(root, filepath.Join(root, "src")); e == nil {
		t.Fatal("allowed deletion of sources")
	}
	if e := clearResults(root, filepath.Join(root, "results")); e != nil {
		t.Fatal(e)
	}
	if _, e := os.Stat(filepath.Join(root, "results/failed/old.bin")); !os.IsNotExist(e) {
		t.Fatal("stale artifact survived", e)
	}
	if _, e := os.Stat(filepath.Join(root, "src/g/a.asm")); e != nil {
		t.Fatal(e)
	}
}
