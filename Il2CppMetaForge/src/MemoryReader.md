# MemoryReader.md

## 📌 스크립트 설명
`MemoryReader.cpp`는 게임의 `.data` 세션에서 후킹 또는 덤프를 통해 수집된 메모리 값을 바탕으로 Il2Cpp 관련 핵심 포인터들을 읽어오는 역할을 합니다. 이 모듈은 `Il2CppMetadataRebuilder`의 초기 입력 데이터 생성 담당입니다.

---

## 📌 `.data` 섹션 포인터 오프셋 대응표 (MemoryReader.cpp 기준)

```cpp
// MemoryReader::LoadMetadataPointers() 내부
typeDefinitions         = ReadPointer(file, RvaToFileOffset(0x18D461A90));  // -> typeDefinitions
methodDefinitions       = ReadPointer(file, RvaToFileOffset(0x18D461A98));  // -> methodDefinitions
stringLiteralTable      = ReadPointer(file, RvaToFileOffset(0x18D461AA0));  // -> stringLiteralTable
stringLiteralTableCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AA8));  // -> stringLiteralTableCount
typeDefinitionsCount    = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AB0));  // -> typeDefinitionsCount
methodDefinitionsCount  = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AB8));  // -> methodDefinitionsCount
fieldDefinitions        = ReadPointer(file, RvaToFileOffset(0x18D461AC0));  // -> fieldDefinitions
fieldDefinitionsCount   = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AC8));  // -> fieldDefinitionsCount
propertyDefinitions     = ReadPointer(file, RvaToFileOffset(0x18D461AD0));  // -> propertyDefinitions
propertyDefinitionsCount= ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AD8));  // -> propertyDefinitionsCount
metadataUsages          = ReadPointer(file, RvaToFileOffset(0x18D461AE0));  // -> metadataUsages
metadataUsagesCount     = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AE8));  // -> metadataUsagesCount
imageDefinitionsCount   = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AF0));  // -> imageDefinitionsCount
```

> 위 오프셋 값은 MabinogiMobile 전용으로 하드코딩되어 있으며, Unity Il2Cpp v31 기준 `.data` 섹션에 위치한 메타데이터 포인터입니다.

이들 값을 기반으로 이후 metadata 파일 조립에 필요한 원천 정보를 제공합니다.

`fieldDefinitions` / `propertyDefinitions`와 각 카운트 값은
`LoadMetadataPointers()` 호출 시 함께 읽어 들이며,
`GetFieldDefinitions()`, `GetFieldDefinitionsCount()`,
`GetPropertyDefinitions()`, `GetPropertyDefinitionsCount()`
함수로 접근할 수 있습니다.

이 포인터들은 `main.cpp`에서 배열 전체를 추출하는 데 사용되어
`MetadataBuilder`의 `SetFieldDefinitions()`와
`SetPropertyDefinitions()`로 전달됩니다.

추가로 임의 구조체를 손쉽게 읽어들이기 위한 템플릿 함수 `ReadStruct<T>`와
카운트 값을 간단히 얻기 위한 `ReadUInt32()` 헬퍼를 제공합니다.

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

