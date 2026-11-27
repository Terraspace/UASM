# UASM coding skill pack

Version 1.0.3, for the UASM 2.60 snapshot identified in `uasm-coding/references/provenance.md`.

This pack gives a fresh Codex conversation reusable UASM instructions, feature references and source-only examples. It does not install an assembler, SDK or debugger and does not depend on this conversation. Read `VALIDATION.md` for the exact checks performed.

## Install for one project (recommended)

Extract the ZIP. Copy the complete `uasm-coding` folder, not only SKILL.md, into your project's `.agents/skills` directory:

```text
your-project/
  .agents/
    skills/
      uasm-coding/
        SKILL.md
        agents/
        references/
        assets/
        scripts/
```

PowerShell, from the extracted pack directory (choose your own project path):

```powershell
$project = 'D:\projects\my-uasm-app'
$destination = Join-Path $project '.agents\skills'
New-Item -ItemType Directory -Path $destination -Force | Out-Null
Copy-Item -LiteralPath '.\uasm-coding' -Destination $destination -Recurse
```

If already installed, review/replace the existing skill folder deliberately rather than creating nested copies. Merge the optional `AGENTS.md.template` content into the project's AGENTS.md; do not overwrite existing project instructions. Record the project's real assembler/build/test commands there.

## Install for all your projects

Alternatively copy `uasm-coding` to your user-level `.agents/skills` directory (`%USERPROFILE%\.agents\skills` on Windows; `~/.agents/skills` on Linux/macOS). Choose one scope to avoid duplicate same-name skills. When Codex runs inside WSL/a container/another machine, install in that environment's project or user location.

These are the current documented local discovery locations. Codex detects changes; restart it if the skill does not appear. Official instructions: [Build skills](https://learn.chatgpt.com/docs/build-skills), checked 2026-11-27.

## Start a new conversation

Open the target project in Codex and begin with:

```text
Use $uasm-coding for this project. Target Windows x64 with UASM 2.60.
Use typed PROC/PROTO, namespaces and the supported HLL/OO features where
appropriate. Read our build files and follow the skill's ABI/call restrictions.
Assemble and test your changes, reporting which checks actually ran.
```

Change the target to Linux ELF64/System V where appropriate. In clients offering a skill selector, select UASM Coding. If a client does not discover the folder, explicitly ask it to read the full path to `uasm-coding/SKILL.md` and the linked references. A ZIP attachment alone is not proof that a local skill has been installed.

## Contents and use

- `uasm-coding/SKILL.md`: small entry point; loads topic references only as needed.
- `uasm-coding/references/`: exact language/call/ABI/platform contracts, evidence and example catalog.
- `uasm-coding/assets/examples/`: namespace, nested-call, OO, Direct2D and Linux PIE/SO/GTK projects, plus small probes.
- `uasm-coding/scripts/check_examples.py`: compile checks with an explicit assembler path.
- `AGENTS.md.template`: optional project guidance to merge.
- `package.py`: reproducible source-only ZIP creation; excludes generated build products.

Do not expect an installed skill folder to be writable. Copy an example to your project before adapting/building it. For Windows sample builds pass the assembler path explicitly to build.cmd; for Linux make pass ASSEMBLER=/absolute/path/to/uasm. See the example catalog for dependencies, entry points, runtime checks and debugger expectations.

To recreate the distribution from this directory:

```text
python package.py --output /path/to/uasm-coding-skill-1.0.3.zip
```

Keep the source manifest and provenance current when refreshing the pack. Local installation copies do not auto-update from GitHub. No personal Codex settings are modified by the packaging or example-check scripts.
