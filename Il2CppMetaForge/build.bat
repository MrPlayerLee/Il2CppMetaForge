@echo off
echo [*] ���� ���丮 ���� ��...
if not exist build mkdir build
cd build

echo [*] CMake ���� ��...
cmake ..

echo [*] �ַ�� ���� ��...
cmake --build . --config Release

echo [?] ���� �Ϸ�!
pause