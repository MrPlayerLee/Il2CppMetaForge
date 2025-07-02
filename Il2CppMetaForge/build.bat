@echo off
echo [*] 빌드 디렉토리 생성 중...
if not exist build mkdir build
cd build

echo [*] CMake 설정 중...
cmake ..

echo [*] 솔루션 빌드 중...
cmake --build . --config Release

echo [?] 빌드 완료!
pause