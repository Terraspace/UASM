package main

import (
	"bytes"
	"testing"
)

func TestPortableText(t *testing.T) {
	a := []byte("..\\src\\group\\test.asm(2) : Error A2000: bad\r\n")
	b := []byte("../src/group/test.asm(2) : Error A2000: bad\n")
	if d, _ := compare(a, b, ".err"); d != "" {
		t.Fatal(d)
	}
	if d, _ := compare(a, b, ".bin"); d == "" {
		t.Fatal("binary bytes normalized")
	}
	for _, changed := range [][]byte{bytes.Replace(b, []byte("test.asm"), []byte("other.asm"), 1), bytes.Replace(b, []byte("A2000"), []byte("A2001"), 1)} {
		if d, _ := compare(a, changed, ".err"); d == "" {
			t.Fatal("meaningful diagnostic change ignored")
		}
	}
}

func TestCOFFFilePathNormalization(t *testing.T) {
	b := make([]byte, 60+54)
	le.PutUint16(b, 0x8664)
	le.PutUint16(b[2:], 1)
	le.PutUint32(b[8:], 60)
	le.PutUint32(b[12:], 3)
	copy(b[60:], ".file")
	b[76] = 103
	b[77] = 2
	copy(b[78:], "..\\src\\test.asm")
	want := append([]byte(nil), b...)
	copy(want[78:], "../src/test.asm")
	if !bytes.Equal(portableCOFFPaths(b), want) {
		t.Fatal("file path not normalized")
	}
	b[76] = 2
	if !bytes.Equal(portableCOFFPaths(b), b) {
		t.Fatal("non-file symbol changed")
	}
	b[76] = 103
	b[77] = 4
	if !bytes.Equal(portableCOFFPaths(b), b) {
		t.Fatal("malformed object changed")
	}
}
