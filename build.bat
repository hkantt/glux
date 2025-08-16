@echo off

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

for /f %%a in ('powershell -NoProfile -Command "Get-Date -Format \"ddMMyy_HHmmss\""') do set TIMESTAMP=%%a

echo Creating release glux.pyd in release...
if not exist release mkdir release
copy /Y "build\Release\glux.pyd" "release\glux.pyd"

echo Creating backup glux_%TIMESTAMP%.pyd in backups...
if not exist backups mkdir backups
copy /Y "build\Release\glux.pyd" "backups\glux_%TIMESTAMP%.pyd"

echo Build Successful!
exit /b
