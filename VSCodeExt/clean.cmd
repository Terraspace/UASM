@echo off
setlocal
cd /d "%~dp0"
node scripts\clean.js
exit /b %errorlevel%
