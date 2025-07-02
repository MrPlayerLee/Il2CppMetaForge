# MemoryReader.md

## 📌 스크립트 설명
`MemoryReader.cpp`는 게임의 `.data` 세션에서 후킹 또는 덤프를 통해 수집된 메모리 값을 바탕으로 Il2Cpp 관련 핵심 포인터들을 읽어오는 역할을 합니다. 이 모듈은 `Il2CppMetadataRebuilder`의 초기 입력 데이터 생성 담당입니다.

---

## 🎯 목표
- `GameAssembly.dll` 내 `.data` 섹션에 위치한 다음과 같은 Il2Cpp 메타데이터 포인터들을 안전하게 읽어오는 것:
  - `ptr_CodeRegistration`
  - `ptr_MetadataRegistration`
  - `typeDefinitions`
  - `methodDefinitions`
  - `stringLiteralTable`
  - `metadataUsages`
  - `metadataUsagesCount`
  - `imageDefinitionsCount`

이들 값을 기반으로 이후 metadata 파일 조립에 필요한 원천 정보를 제공합니다.

추가로 임의 구조체를 손쉽게 읽어들이기 위한 템플릿 함수 `ReadStruct<T>`를 제공합니다.

---

## 🧱 동작 원리
- 미리 정의된 `.data` 섹션 시작 주소를 기준으로 오프셋을 탐색합니다.
- 각 포인터 주소에 대해 메모리에서 데이터를 읽어오며, 구조체 형식에 맞춰 역직렬화합니다.
- 포인터 유효성 검사를 통해 널 포인터 또는 잘못된 오프셋으로 인한 오류를 방지합니다.

---

## ⚠️ 주의점
- 본 모듈은 **GameAssembly.dll**에서 `.data` 섹션 메모리가 반드시 정상적으로 덤프되어 있어야 작동합니다.
- Unity 버전에 따라 오프셋 구조가 다르기 때문에, 필드 순서가 다를 경우 잘못된 값을 읽어올 수 있습니다.
- 메모리 오염 또는 보호된 환경에서는 읽기 동작 자체가 실패할 수 있으며, 이를 대비한 오류 처리가 필요합니다.

