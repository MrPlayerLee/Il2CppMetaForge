# Il2CppMetaForge

Il2CppMetaForge는 Unity 게임의 `.data` 섹션에서 추출한 메타데이터 포인터를 이용해
`global-metadata.dat`을 정적으로 재구성하는 도구입니다. 기존 Il2CppDumper를 사용하기
어려운 환경에서도 메모리 덤프만으로 `Assembly-CSharp.dll`을 분석할 수 있도록 돕는 것을
목표로 합니다.

## 📂 프로젝트 파일트리
```
Il2CppMetaForge/
├── Il2CppMetaForge.sln
├── Il2CppMetaForge/include/
│   └── Il2CppMetadataStructs.h
└── Il2CppMetaForge/src/
    ├── main.cpp
    ├── MemoryReader.cpp
    └── MetadataBuilder.cpp
```

## 📄 스크립트별 마크다운 문서
- `Il2CppMetaForge/include/Il2CppMetadataStructs.md`
- `Il2CppMetaForge/src/MemoryReader.md`
- `Il2CppMetaForge/src/MetadataBuilder.md`
- `Il2CppMetaForge/src/main.md`

## ⚙️ 작동 방식
1. `MemoryReader.cpp`가 `.data` 섹션에서 메타데이터 관련 포인터를 읽어옵니다.
2. `MetadataBuilder.cpp`가 읽어 온 구조체 데이터를 기반으로 Unity 호환 형식의
   `global-metadata.dat`을 생성합니다.
3. `main.cpp`가 위 과정을 순차적으로 실행하여 결과 파일을 디스크에 저장합니다.

## 🏦 필수 구성요소
- `.data` 섹션 덤프와 해당 포인터 값들
- Unity Il2Cpp v31 구조체 정의
- Visual Studio 2022 또는 mingw-w64 환경

## 🔧 mingw-w64 설치 및 빌드 예시
Ubuntu 기준으로 다음 명령으로 크로스 컴파일 도구를 설치할 수 있습니다.
```bash
sudo apt-get update
sudo apt-get install mingw-w64
```
설치 후에는 `x86_64-w64-mingw32-g++`를 이용해 다음과 같이 빌드합니다.
```bash
x86_64-w64-mingw32-g++ -std=c++17 -IIl2CppMetaForge/include \
    Il2CppMetaForge/src/*.cpp -o Il2CppMetaForge.exe
```

## 🔧 사용할 함수 목록
- `void* ReadPointer(uint64_t address)`
- `template<typename T> T ReadStruct(uint64_t address)`
- `void WriteMetadataHeader(...)`
- `void WriteTypeDefinitions(...)`
- `void WriteMethodDefinitions(...)`
- `void WriteStringLiteralTable(...)`
- `void WriteMetadataUsages(...)`
- `void WriteImageDefinitions(...)`

## 🎯 최종 목표
- 메모리 덤프만으로 Unity 게임의 메타데이터 구조를 복원하여
  디컴파일 도구가 필요한 환경을 우회하는 것
- 보호된 게임에서 분석을 위한 정적 `global-metadata.dat` 파일 생성

## ⚠️ 주의점
- 메모리 오프셋 오류나 버전 차이로 인한 구조체 불일치는 빌드 실패를 초래할 수 있습니다.
- 본 도구는 분석 목적이며 게임 개조가 아닌 학습용으로 사용해야 합니다.
