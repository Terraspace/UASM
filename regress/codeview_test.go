package main

import (
	"bytes"
	"encoding/binary"
	"os"
	"testing"
)

func cvRecord(kind uint16, body []byte) []byte {
	b := make([]byte, 4)
	le.PutUint16(b, uint16(len(body)+2))
	le.PutUint16(b[2:], kind)
	return append(b, body...)
}
func cvFixture(path string, version byte) []byte {
	obj := append(make([]byte, 4), []byte(path+"\x00")...)
	compile := make([]byte, 22)
	compile[14] = version
	compile = append(compile, []byte("UASM\x00")...)
	env := append([]byte{0}, []byte("cwd\x00"+path+"\x00exe\x00"+path+"\\UASM.exe\x00src\x00test.asm\x00\x00")...)
	records := cvRecord(0x1101, obj)
	records = append(records, cvRecord(0x113c, compile)...)
	records = append(records, cvRecord(0x113d, env)...)
	target := 12 + len(records) + 4
	records = append(records, cvRecord(0x110d, []byte{1, 2, 3, 4, 5, 6, 7, 8})...)
	debug := make([]byte, 12)
	le.PutUint32(debug, 4)
	le.PutUint32(debug[4:], 0xf1)
	le.PutUint32(debug[8:], uint32(len(records)))
	debug = append(debug, records...)
	for len(debug)%4 != 0 {
		debug = append(debug, 0)
	}
	b := make([]byte, 100)
	le.PutUint16(b, 0x8664)
	le.PutUint16(b[2:], 2)
	copy(b[20:], ".debug$S")
	le.PutUint32(b[36:], uint32(len(debug)))
	le.PutUint32(b[40:], 100)
	le.PutUint32(b[44:], uint32(100+len(debug)))
	le.PutUint16(b[52:], 1)
	copy(b[60:], ".debug$T")
	le.PutUint32(b[76:], 4)
	le.PutUint32(b[80:], uint32(110+len(debug)))
	b = append(b, debug...)
	rel := make([]byte, 10)
	le.PutUint32(rel, uint32(target))
	le.PutUint16(rel[8:], 0xb)
	b = append(b, rel...)
	b = append(b, 4, 0, 0, 0)
	le.PutUint32(b[8:], uint32(len(b)))
	le.PutUint32(b[12:], 2)
	sym := make([]byte, 36)
	copy(sym, ".debug$S")
	le.PutUint16(sym[12:], 1)
	sym[16] = 3
	sym[17] = 1
	le.PutUint32(sym[18:], uint32(len(debug)))
	b = append(b, sym...)
	return append(b, 4, 0, 0, 0)
}
func TestCV8MetadataAndLayout(t *testing.T) {
	a, b := cvFixture("D:\\old\\long\\path", 55), cvFixture("C:\\new", 59)
	if d, ignored := compare(a, b, ".obj"); d != "" || len(ignored) == 0 {
		t.Fatal(d, ignored)
	}
	if d, _ := compare(a, b, ".bin"); d == "" {
		t.Fatal("normalized binary")
	}
	// Source identity, producer and unknown symbol records must remain exact.
	for _, needle := range [][]byte{[]byte("test.asm"), []byte("UASM\x00"), {1, 2, 3, 4, 5, 6, 7, 8}} {
		c := append([]byte(nil), b...)
		i := bytes.Index(c, needle)
		if i < 0 {
			t.Fatal("needle")
		}
		c[i] ^= 1
		if d, _ := compare(a, c, ".obj"); d == "" {
			t.Fatalf("ignored %q", needle)
		}
	}
	for _, offset := range []int{0, 58, 96, int(le.Uint32(b[80:])), int(le.Uint32(b[44:])) + 4, int(le.Uint32(b[44:])) + 8} {
		c := append([]byte(nil), b...)
		c[offset] ^= 1
		if d, _ := compare(a, c, ".obj"); d == "" {
			t.Fatalf("missed offset %d", offset)
		}
	}
	c := append([]byte(nil), b...)
	p := int(le.Uint32(c[44:]))
	le.PutUint32(c[p:], le.Uint32(c[p:])+1)
	if d, _ := compare(a, c, ".obj"); d == "" {
		t.Fatal("ignored relocation offset")
	}
	for i := 0; i < len(b); i++ {
		if d, _ := compare(a, b[:i], ".obj"); d == "" {
			t.Fatalf("accepted truncation %d", i)
		}
	}
	for _, p := range []int{8, 36, 40, 44, 76, 80, 108} {
		c := append([]byte(nil), b...)
		binary.LittleEndian.PutUint32(c[p:], 0xffffffff)
		if d, _ := compare(a, c, ".obj"); d == "" {
			t.Fatal("accepted malformed object", p)
		}
	}
}

// These archived fixtures are part of the suite, so verify their C13 structure
// is supported without needing an assembler or a results directory.
func TestArchivedCV8(t *testing.T) {
	for _, p := range []string{"exp/codeview8_32/cv8_1.obj", "exp/codeview8_64/cv8_2.obj"} {
		b, e := os.ReadFile(p)
		if e != nil {
			t.Fatal(e)
		}
		if _, e = canonicalCV8(b); e != nil {
			t.Fatal(p, e)
		}
	}
}

func TestCV8PreservesSemanticSubsections(t *testing.T) {
	a, err := os.ReadFile("exp/codeview8_64/cv8_2.obj")
	if err != nil {
		t.Fatal(err)
	}
	for i := 0; i < int(le.Uint16(a[2:])); i++ {
		h := a[20+i*40 : 60+i*40]
		if string(bytes.TrimRight(h[:8], "\x00")) != ".debug$S" {
			continue
		}
		start, size := int(le.Uint32(h[20:])), int(le.Uint32(h[16:]))
		for p := start + 4; p < start+size; {
			kind, n := le.Uint32(a[p:]), int(le.Uint32(a[p+4:]))
			body := p + 8
			if kind != 0xf1 && n > 0 {
				b := append([]byte(nil), a...)
				b[body] ^= 1
				if d, _ := compare(a, b, ".obj"); d == "" {
					t.Fatalf("ignored subsection %x", kind)
				}
			}
			if kind == 0xf1 {
				for q := body; q < body+n; {
					if le.Uint16(a[q+2:]) == 0x113c {
						for _, offset := range []int{4, 8, 10, 26} {
							b := append([]byte(nil), a...)
							b[q+offset] ^= 1
							if d, _ := compare(a, b, ".obj"); d == "" {
								t.Fatal("ignored compiler semantics", offset)
							}
						}
					}
					q += int(le.Uint16(a[q:])) + 2
				}
			}
			p = (body + n + 3) &^ 3
		}
	}
}
