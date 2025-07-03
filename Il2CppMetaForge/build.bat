@echo off
echo [*] 빌드 폴더를 준비 중...
if not exist build mkdir build
cd build

echo [*] CMake 설정 중...
cmake ..

echo [*] 빌드 진행 중...
cmake --build . --config Release

echo [?] 빌드가 완료되었습니다!
pause
