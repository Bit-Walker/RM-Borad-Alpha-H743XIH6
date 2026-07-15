@echo off
cd /d "%~dp0\.."
python Tools\sync_bsp_handles.py
exit /b %errorlevel%