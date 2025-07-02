#!/bin/bash
echo "[*] 빌드 디렉토리 생성 중..."
mkdir -p build
cd build

echo "[*] CMake 설정 중..."
cmake ..

echo "[*] Make 빌드 중..."
make -j$(nproc)

echo "[✔] 빌드 완료!"