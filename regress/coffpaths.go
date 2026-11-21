package main

import "bytes"

// Normalize separators only in parsed COFF .file auxiliary records and
// C13 filename string tables. All filename characters remain significant.
func portableCOFFPaths(in []byte) []byte {
	if timestampOffset(in, ".obj") != 4 {
		return in
	}
	n := int(le.Uint16(in[2:]))
	opt := int(le.Uint16(in[16:]))
	head := 20 + opt
	if n > (len(in)-head)/40 {
		return in
	}
	sp, count := uint64(le.Uint32(in[8:])), uint64(le.Uint32(in[12:]))
	if sp > uint64(len(in)) || count > (uint64(len(in))-sp)/18 {
		return in
	}
	out := append([]byte(nil), in...)
	slash := func(b []byte) {
		for i := range b {
			if b[i] == '\\' {
				b[i] = '/'
			}
		}
	}
	for i := uint64(0); i < count; {
		p := sp + i*18
		aux := uint64(in[p+17])
		if i+aux >= count {
			return in
		}
		if in[p+16] == 103 && bytes.Equal(in[p:p+8], []byte{'.', 'f', 'i', 'l', 'e', 0, 0, 0}) {
			slash(out[p+18 : p+18*(aux+1)])
		}
		i += 1 + aux
	}
	for i := 0; i < n; i++ {
		h := head + i*40
		if string(bytes.TrimRight(in[h:h+8], "\x00")) != ".debug$S" {
			continue
		}
		start, size := uint64(le.Uint32(in[h+20:])), uint64(le.Uint32(in[h+16:]))
		if start > uint64(len(in)) || size > uint64(len(in))-start || size < 4 {
			return in
		}
		if le.Uint32(in[start:]) != 4 {
			continue
		}
		for p := start + 4; p < start+size; {
			if start+size-p < 8 {
				return in
			}
			kind, sz := le.Uint32(in[p:]), uint64(le.Uint32(in[p+4:]))
			if sz > start+size-p-8 {
				return in
			}
			if kind == 0xf3 {
				slash(out[p+8 : p+8+sz])
			}
			p = start + ((p - start + 8 + sz + 3) &^ 3)
			if p > start+size {
				return in
			}
		}
	}
	return out
}
