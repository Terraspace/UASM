"""Assemble source examples with an explicit UASM; no SDK/linker required."""
from pathlib import Path
import argparse
import json
import os
import subprocess

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--assembler', required=True, help='Path to UASM executable')
    parser.add_argument('--include-dir', action='append', default=[], help='Additional assembler include search directory; enables WinInc example')
    parser.add_argument('--output', required=True, help='Directory for generated objects/report')
    args = parser.parse_args()
    assembler = Path(args.assembler).resolve(strict=True)
    output = Path(args.output).resolve()
    output.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1] / 'assets' / 'examples'
    env = dict(os.environ)
    env.pop('UASM', None)
    results = []
    for source in sorted(root.rglob('*.asm')):
        relative = source.relative_to(root)
        if source.name == 'wininc.asm' and not args.include_dir:
            print('SKIP '+relative.as_posix()+' (provide --include-dir for WinInc)')
            continue
        binary = source.name == 'namespace_scope.asm'
        flags = ['-bin'] if binary else (['-elf64', '-Zi'] if relative.parts[0] == 'linux64' else ['-win64', '-Zp8', '-Zi8'])
        target = (output / relative).with_suffix('.bin' if binary else '.obj')
        target.parent.mkdir(parents=True, exist_ok=True)
        # No stale result can satisfy the output check after a failed invocation.
        target.unlink(missing_ok=True)
        command = [str(assembler), '-q', *flags, *['-I'+str(Path(p).resolve()) for p in args.include_dir], '-Fo'+str(target), source.name]
        run = subprocess.run(command, cwd=source.parent, env=env, capture_output=True, text=True, errors='replace', timeout=60)
        passed = run.returncode == 0 and target.is_file() and target.stat().st_size > 0
        if binary and passed:
            passed = target.read_bytes() == bytes([1,2,3,2,1,2,4,5,6,2,7,8])
        results.append({'source':relative.as_posix(), 'passed':passed, 'exit':run.returncode, 'command':command, 'output':run.stdout+run.stderr})
        print(('PASS ' if passed else 'FAIL ')+relative.as_posix())
    (output/'report.json').write_text(json.dumps(results,indent=2)+'\n',encoding='utf8')
    print(f'{sum(r["passed"] for r in results)}/{len(results)} passed; assembly checks, not linked runtime tests.')
    return 0 if results and all(r['passed'] for r in results) else 1

if __name__ == '__main__':
    raise SystemExit(main())
