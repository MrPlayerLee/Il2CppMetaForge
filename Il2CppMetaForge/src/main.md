# main.md

## 📌 목적
Il2CppMetaForge의 진입점으로서 전체 파이프라인을 제어합니다. `MemoryReader`를 통해 메모리에서 필요한 메타데이터 값을 읽어들이고, `MetadataBuilder`를 통해 이를 기반으로 Unity 호환 `global-metadata.dat` 파일을 생성하는 역할을 합니다.

---

## ⚙️ 동작 방식
1. 사용자 입력 또는 하드코딩된 `.data` 섹션 내 포인터 주소값을 설정합니다.
2. `MemoryReader` 인스턴스를 초기화하고, 지정된 주소로부터 다음 데이터를 로드합니다:
   - `typeDefinitions`
   - `methodDefinitions`
   - `fieldDefinitions`
   - `propertyDefinitions`
   - `stringLiteralTable`
   - `metadataUsages`
   - `metadataUsagesCount`
   - `imageDefinitionsCount`
   - `genericContainers`
   - `genericParameters`
3. `ReadUInt32()` 헬퍼로 카운트를 읽은 뒤 `Il2CppFieldDefinition`과
   `Il2CppPropertyDefinition` 배열을 모두 추출한 뒤
   `MetadataBuilder`의 `SetFieldDefinitions()`와 `SetPropertyDefinitions()`에
   전달합니다. 이때 사용되는 포인터는 `MemoryReader`에서 제공하는
   `GetFieldDefinitions()` / `GetFieldDefinitionsCount()`와
   `GetPropertyDefinitions()` / `GetPropertyDefinitionsCount()`입니다.
4. 이후 다른 테이블과 함께 `MetadataBuilder`에 설정하여
   `Il2CppMetadataHeader`를 작성하고 각 section을 출력합니다.
5. 최종 `global-metadata.dat`를 디스크에 저장합니다.

---

## 🔎 주의점
- 실행 전에 `.data` 섹션의 주소 정보가 정확히 파악되어 있어야 하며, 이는 고정된 오프셋이 아니므로 매번 수작업 또는 자동 분석이 필요합니다.
- 모든 데이터는 정확한 정렬(Alignment)이 필요하므로 구조체 정의와 바이너리 출력을 일치시켜야 합니다.
- 메모리 누수 방지를 위한 리소스 해제 및 예외 처리 루틴이 필요합니다.

