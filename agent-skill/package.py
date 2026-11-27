"""Create a portable source-only skill archive; never install or publish it."""
from pathlib import Path
import argparse
import zipfile

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parent
    target = Path(args.output).resolve()
    if target.exists():
        parser.error('Output already exists; choose a new filename or remove it explicitly.')
    excluded = {'build', 'dist', '__pycache__', '.git', '.vs'}
    allowed = {'.md', '.template', '.yaml', '.json', '.py', '.asm', '.inc', '.cmd', '.sln', '.vcxproj', '.txt'}
    files = [p for p in root.rglob('*') if p.is_file() and not any(x in excluded for x in p.relative_to(root).parts) and (p.suffix in allowed or p.name in {'Makefile', '.gitignore'})]
    assert root/'uasm-coding/SKILL.md' in files
    target.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(target, 'x', zipfile.ZIP_DEFLATED) as archive:
        for file in sorted(files):
            info = zipfile.ZipInfo('agent-skill/'+file.relative_to(root).as_posix(), (2026,11,27,0,0,0))
            info.compress_type = zipfile.ZIP_DEFLATED
            info.external_attr = 0o100644 << 16
            archive.writestr(info, file.read_bytes())
    with zipfile.ZipFile(target) as archive:
        assert archive.testzip() is None
    print(f'{len(files)} source/document files: {target}')

if __name__ == '__main__':
    main()
