"""SDK-sized export-check benchmark; no SDK or third-party modules required.
Run: python export-check-performance.py /path/to/uasm [--max-seconds 10]
The ceiling is deliberately generous; raise it for slow/emulated machines.
"""
import argparse
from pathlib import Path
import subprocess
import tempfile
import time

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('assembler', type=Path)
parser.add_argument('--symbols', type=int, default=20000)
parser.add_argument('--max-seconds', type=float, default=10)
args = parser.parse_args()
assembler = args.assembler.resolve(strict=True)
with tempfile.TemporaryDirectory(prefix='uasm-export-perf-') as tmp:
    root = Path(tmp)
    source = ['option casemap:none', 'option literals:on',
              'option win64:15', 'sink proto :ptr byte']
    source += [f'extern sdk_function_{i:05}:proc' for i in range(args.symbols)]
    source += ['.data', 'dummy db 0', '.code', 'entry proc frame',
               'invoke sink, "activate global-qualified literal lookup"',
               'ret', 'entry endp', 'end']
    (root / 'test.asm').write_text('\n'.join(source) + '\n', encoding='ascii')
    started = time.perf_counter()
    try:
        result = subprocess.run([str(assembler), '-q', '-win64', '-Foresult.obj',
                                 'test.asm'], cwd=root, capture_output=True,
                                text=True, timeout=args.max_seconds)
    except subprocess.TimeoutExpired:
        raise SystemExit(f'FAIL: export check exceeded {args.max_seconds}s for {args.symbols} externals')
    elapsed = time.perf_counter() - started
    if result.returncode or not (root / 'result.obj').is_file():
        raise SystemExit(f'FAIL: assembly failed\n{result.stdout}\n{result.stderr}')
    print(f'PASS: {args.symbols} externals plus string literal assembled in {elapsed:.3f}s')
