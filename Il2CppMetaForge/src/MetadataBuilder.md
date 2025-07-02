# MetadataBuilder.md

## 📌 스크립트 설명
`MetadataBuilder.cpp`는 메모리에서 읽어온 Il2Cpp 구조체 데이터를 기반으로 가짜 `global-metadata.dat` 파일을 생성하는 모듈입니다. Unity의 Il2Cpp 런타임이 요구하는 메타데이터 형식에 맞춰 바이너리 출력을 조립합니다. 이 파일은 Unity 디컴파일러(dnSpy 등)에서 분석 가능한 정적 형태의 메타데이터 파일로 사용됩니다.

---

## 🎯 목표
- `.data` 섹션에서 수집한 메모리 기반 포인터들을 활용하여 Unity 호환 `global-metadata.dat` 바이너리를 생성합니다.
- Unity Il2Cpp 런타임 구조체에 맞는 정렬 및 레이아웃을 보장하여 dnSpy 또는 Il2CppInspector로 분석 가능한 수준의 메타데이터 파일을 생성하는 것이 최종 목적입니다.

---

## 🧱 동작 원리
- `MemoryReader`로부터 전달된 `typeDefinitions`, `methodDefinitions`, `stringLiteralTable` 등의 메모리 포인터 데이터를 입력으로 받습니다.
- 각 구조체에 해당하는 데이터를 순차적으로 write 함수(`WriteTypeDefinitions`, `WriteMethodDefinitions`, ...)를 통해 출력 버퍼에 기록합니다.
- 구조체별로 크기 계산, offset 보정, padding 등을 자동 처리하여 Il2Cpp 런타임이 요구하는 16진수 정렬 요건을 만족시킵니다.

---

## ⚠️ 주의점
- Unity 버전에 따라 구조체 레이아웃이 다를 수 있으므로, 본 도구는 **Unity v31 기준**으로 제작되었습니다.
- 출력되는 데이터는 임의 생성된 값이며 정확한 실행을 보장하지 않으며, 분석/리버스 용도로만 사용해야 합니다.
- 데이터 누락이나 잘못된 포인터가 존재하면 dnSpy 로딩 시 오류가 발생하거나 잘못된 디컴파일 결과를 유도할 수 있습니다.

