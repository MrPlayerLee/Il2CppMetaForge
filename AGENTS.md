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

