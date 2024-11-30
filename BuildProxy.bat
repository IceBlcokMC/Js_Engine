@echo off
powershell -Command "$Env:http_proxy='http://127.0.0.1:7890';$Env:https_proxy='http://127.0.0.1:7890'"
powershell -Command "Write-Host 'Current proxy settings:' $Env:http_proxy"

cmake -B build -S .
cmake --build ./build

pause
