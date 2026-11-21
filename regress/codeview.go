package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
)

var le = binary.LittleEndian

// canonicalCV8 changes only C13 build metadata and the layout fields affected
// by its length. Unsupported/malformed objects fall back to byte comparison.
func canonicalCV8(in []byte) ([]byte, error) {
	bad := func() ([]byte, error) { return nil, fmt.Errorf("unsupported or malformed CV8 COFF") }
	if timestampOffset(in, ".obj") != 4 || le.Uint16(in[16:]) != 0 {
		return bad()
	}
	n := int(le.Uint16(in[2:]))
	section := -1
	start, size := 0, 0
	for i := 0; i < n; i++ {
		h := in[20+i*40 : 60+i*40]
		if string(bytes.TrimRight(h[:8], "\x00")) == ".debug$S" {
			if section >= 0 {
				return bad()
			}
			section = i
			size = int(le.Uint32(h[16:]))
			start = int(le.Uint32(h[20:]))
		}
	}
	if section < 0 || start < 20+n*40 || size < 4 || start > len(in)-size {
		return bad()
	}
	data, positions, err := canonicalC13(in[start : start+size])
	if err != nil {
		return nil, err
	}
	delta := len(data) - size
	out := append([]byte(nil), in[:start]...)
	out = append(out, data...)
	out = append(out, in[start+size:]...)
	move := func(p uint32) (uint32, bool) {
		if p == 0 {
			return 0, true
		}
		if uint64(p) > uint64(len(in)) {
			return 0, false
		}
		if int(p) <= start {
			return p, true
		}
		if int(p) >= start+size {
			return uint32(int(p) + delta), true
		}
		return 0, false
	}
	sympos := int(le.Uint32(in[8:]))
	count := int(le.Uint32(in[12:]))
	if sympos < 20+n*40 || sympos > len(in) || count > (len(in)-sympos)/18 {
		return bad()
	}
	sp, ok := move(uint32(sympos))
	if !ok {
		return bad()
	}
	le.PutUint32(out[8:], sp)
	for i := 0; i < n; i++ {
		h := out[20+i*40 : 60+i*40]
		orig := in[20+i*40 : 60+i*40]
		raw, sz := int(le.Uint32(orig[20:])), int(le.Uint32(orig[16:]))
		rp, nr := int(le.Uint32(orig[24:])), int(le.Uint16(orig[32:]))
		if sz > 0 && (raw < 20+n*40 || raw > len(in)-sz || (i != section && raw < start+size && raw+sz > start)) {
			return bad()
		}
		if nr > 0 && (rp < 20+n*40 || nr > (len(in)-rp)/10 || (rp < start+size && rp+nr*10 > start)) {
			return bad()
		}
		for _, off := range []int{20, 24, 28} {
			p, ok := move(le.Uint32(orig[off:]))
			if !ok {
				return bad()
			}
			le.PutUint32(h[off:], p)
		}
		if i == section {
			le.PutUint32(h[16:], uint32(len(data)))
			relocated := int(le.Uint32(h[24:]))
			for j := 0; j < nr; j++ {
				p := relocated + j*10
				old := int(le.Uint32(out[p:]))
				mapped, ok := positions[old]
				if !ok {
					return bad()
				}
				le.PutUint32(out[p:], uint32(mapped))
			}
		}
	}
	for i := 0; i < count; {
		p := int(sp) + i*18
		s := out[p : p+18]
		aux := int(s[17])
		if i+aux >= count {
			return bad()
		}
		if int(int16(le.Uint16(s[12:]))) == section+1 && s[16] == 3 && aux > 0 && le.Uint32(s[8:]) == 0 && le.Uint16(s[14:]) == 0 {
			if aux != 1 || le.Uint32(out[p+18:]) != uint32(size) {
				return bad()
			}
			le.PutUint32(out[p+18:], uint32(len(data)))
		}
		i += 1 + aux
	}
	return out, nil
}

func canonicalC13(in []byte) ([]byte, map[int]int, error) {
	fail := func() ([]byte, map[int]int, error) { return nil, nil, fmt.Errorf("malformed C13 records") }
	if len(in) < 4 || le.Uint32(in) != 4 {
		return fail()
	}
	out := append([]byte(nil), in[:4]...)
	positions := map[int]int{}
	for pos := 4; pos < len(in); {
		if len(in)-pos < 8 {
			return fail()
		}
		kind := le.Uint32(in[pos:])
		size := int(le.Uint32(in[pos+4:]))
		base := pos + 8
		if size > len(in)-base {
			return fail()
		}
		end := base + size
		next := (end + 3) &^ 3
		if next > len(in) {
			return fail()
		}
		for _, b := range in[end:next] {
			if b != 0 {
				return fail()
			}
		}
		head := len(out)
		out = append(out, in[pos:base]...)
		body := len(out)
		if kind != 0xf1 {
			for i := base; i < end; i++ {
				positions[i] = len(out)
				out = append(out, in[i])
			}
		} else {
			for p := base; p < end; {
				if end-p < 4 {
					return fail()
				}
				length := int(le.Uint16(in[p:])) + 2
				if length < 4 || length > end-p {
					return fail()
				}
				record := in[p : p+length]
				normalized, err := canonicalCVRecord(record)
				if err != nil {
					return fail()
				}
				// Relocations must refer to preserved records, never ignored metadata.
				if bytes.Equal(record, normalized) {
					for i := 0; i < length; i++ {
						positions[p+i] = len(out) + i
					}
				}
				out = append(out, normalized...)
				p += length
			}
		}
		le.PutUint32(out[head+4:], uint32(len(out)-body))
		for len(out)%4 != 0 {
			out = append(out, 0)
		}
		pos = next
	}
	return out, positions, nil
}

func canonicalCVRecord(r []byte) ([]byte, error) {
	fail := func() ([]byte, error) { return nil, fmt.Errorf("malformed metadata") }
	out := append([]byte(nil), r...)
	switch le.Uint16(r[2:]) {
	case 0x1101: // S_OBJNAME: retain signature, ignore object pathname only.
		if len(r) < 9 || r[len(r)-1] != 0 || bytes.IndexByte(r[8:], 0) != len(r)-9 {
			return fail()
		}
		out = append(out[:8], 0)
	case 0x113c: // S_COMPILE3: keep flags, machine, frontend, producer; ignore backend version.
		if len(r) < 27 || r[len(r)-1] != 0 {
			return fail()
		}
		clear(out[18:26])
	case 0x113d: // S_ENVBLOCK: preserve flags, keys, source path and unknown values.
		if len(r) < 6 {
			return fail()
		}
		out = out[:5]
		p := 5
		for {
			if p >= len(r) {
				return fail()
			}
			q := bytes.IndexByte(r[p:], 0)
			if q < 0 {
				return fail()
			}
			key := r[p : p+q]
			p += q + 1
			out = append(out, key...)
			out = append(out, 0)
			if len(key) == 0 {
				if p != len(r) {
					return fail()
				}
				break
			}
			q = bytes.IndexByte(r[p:], 0)
			if q < 0 {
				return fail()
			}
			if string(key) != "cwd" && string(key) != "exe" {
				value := r[p : p+q]
				if string(key) == "src" {
					value = bytes.ReplaceAll(value, []byte("\\"), []byte("/"))
				}
				out = append(out, value...)
			}
			out = append(out, 0)
			p += q + 1
		}
	}
	le.PutUint16(out, uint16(len(out)-2))
	return out, nil
}
