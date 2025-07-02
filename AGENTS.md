# AGENTS.md

## 📂 프로젝트 파일티리

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

---

## 📄 스크립트별 마크다운 문서

- `Il2CppMetaForge/include/Il2CppMetadataStructs.md`
- `Il2CppMetaForge/src/MemoryReader.md`
- `Il2CppMetaForge/src/MetadataBuilder.md`
- `Il2CppMetaForge/src/main.md`

---

## ⚙️ 작동 방식

1. `MemoryReader.cpp`가 `.data` 세츠션에서 추출된 메타데이터 포인터들을 파시합니다.
2. 추출된 구조체 데이터를 `MetadataBuilder.cpp`가 Unity Il2Cpp 호환 형식의 `global-metadata.dat` 형식으로 빌드합니다.
3. `main.cpp`는 전체 과정을 순차적으로 호출하며, 완성된 metadata 파일을 디스크에 저장합니다.

---

## 🏦 필수 구성요소

- GameAssembly.dll에서 추출한 `.data` 세츠션 데스크 데이터 (바이널리 또는 메모리 접근)
- 추출된 포인터 (ex: `typeDefinitions`, `methodDefinitions`, `stringLiteralTable`, `metadataUsages`, `metadataUsagesCount`, `imageDefinitionsCount`)
- Unity Il2Cpp v31 기준 구조체 정의
- Visual Studio 2022 (Windows 10, x64)

---

## 🔧 사용할 함수 목록

- `void* ReadPointer(uint64_t address)`
- `template<typename T> T ReadStruct(uint64_t address)`
- `void WriteMetadataHeader(...)`
- `void WriteTypeDefinitions(...)`
- `void WriteMethodDefinitions(...)`
- `void WriteStringLiteralTable(...)`
- `void WriteMetadataUsages(...)`
- `void WriteImageDefinitions(...)`

---

## 🎯 최종 목표

- 실 기기 또는 PC 환경에서 Il2CppDumper를 사용할 수 없는 경우, 해당 게임의 `.data` 섹션 메모리만으로 `Assembly-CSharp.dll`의 분석이 가능하도록 **정적 global-metadata.dat 파일을 생성**하는 것
- Unity 기반 보호된 게임에서 `dnSpy`, `Il2CppInspector`, `Il2CppDumper`가 작동하지 않는 환경을 용행

---

## ⚠️ 주의점

- 본 도구는 실제 메모리 구조에 의존하며, 각 Unity 버전별 메타데이터 구조의 변화에 무척 무겁함
- 잘못된 오프셀 또는 타입 정렬은 metadata 파시프 오류 또는 dnSpy crash를 유발할 수 있음
- 목적은 `Assembly-CSharp.dll` 디컴파일을 가능케 하려는 **정적 분석용 도구 제작**임 (게임 개조 목적 아닌)

---

## 🧾 REPORTS.md

이 문서는 Il2CppMetaForge 프로젝트의 진행 과정 중 발견된 문제점, 구현되지 않은 항목, 또는 계획은 있었지만 코드에 반영되지 않은 기능 등을 기록하는 리포트 문서입니다.

### 📌 용도

- 누락된 기능 또는 미구현된 섹션을 Codex나 후속 개발자가 파악할 수 있도록 기록
- 스크립트 상에서 예외 처리가 부족한 부분, 추후 개선이 필요한 로직 등도 기술
- 추적 가능한 버그 및 실행 중 에러 발생 위치에 대한 간단한 로그 역할

### 🛠 주요 내용 예시

- `WriteImageDefinitions()` 함수는 현재 구현되지 않았으며, `Il2CppImageDefinition` 출력 로직은 향후 확장 예정
- `main.cpp`에서는 `Set*()` 계열 함수들이 호출되지 않아 기본 `global-metadata.dat`는 헤더만 출력됨
- `MemoryReader::LoadMetadataPointers()`는 현재 오프셋을 하드코딩하고 있어, 동적 스캐닝 또는 config 기반 확장이 필요함
- CLI 인자 처리 시 GameAssembly.dll 경로 누락 시 에러 메시지 외 종료되며, 유저 가이드는 없음

### 🔍 활용 방법

- Codex나 GPT가 테스트 중 오류를 발견하거나,
- 개발자가 직접 기능 보강을 위해 TODO 리스트화할 항목이 생기면 이곳에 기록

---

## 🏗️ 크로스플랫폼 빌드 시스템 (CMake)

본 프로젝트는 Windows (Visual Studio 2022)와 Linux (GCC, Clang) 양쪽에서 동일하게 빌드 가능한 CMake 기반 크로스플랫폼 구조를 사용합니다.

### 📂 CMake 파일 위치
```
Il2CppMetaForge/
└── Il2CppMetaForge/
    ├── CMakeLists.txt          ← CMake 설정 파일
    ├── build.bat               ← Windows 자동 빌드 스크립트
    ├── build.sh                ← Linux 자동 빌드 스크립트
```

### 🧱 빌드 방법

#### Windows (Visual Studio 환경)
```cmd
cd Il2CppMetaForge\Il2CppMetaForge
build.bat
```

#### Linux / Codex 환경
```bash
cd Il2CppMetaForge/Il2CppMetaForge
chmod +x build.sh
./build.sh
```

### ⚙️ 특징
- CMake에서 `PLATFORM_WINDOWS` 또는 `PLATFORM_LINUX` 매크로 자동 정의
- `include/` 및 `src/` 디렉토리 자동 인식
- Visual Studio 프로젝트(.sln)와 완전히 병행 사용 가능
