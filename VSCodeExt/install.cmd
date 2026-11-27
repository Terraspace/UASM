@echo off
setlocal
cd /d "%~dp0"
if not exist "dist\uasm-intellisense.vsix" (echo Run build.cmd first.& exit /b 1)
call code.cmd --install-extension "%~dp0dist\uasm-intellisense.vsix" --force
if errorlevel 1 exit /b 1
echo Installed. Run Developer: Reload Window in VS Code.
