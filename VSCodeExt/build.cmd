@echo off
setlocal
cd /d "%~dp0"
where node >nul 2>nul
if errorlevel 1 (echo Install Node.js 22 or newer first.& exit /b 1)
set "npm_config_cache=%~dp0.npm-cache"
call npm.cmd ci --ignore-scripts
if errorlevel 1 exit /b 1
call npm.cmd run package
exit /b %errorlevel%
