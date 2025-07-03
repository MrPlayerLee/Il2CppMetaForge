# 📓 REPORTS.md

이 문서는 Il2CppMetaForge 프로젝트에서 발생한 오류, 누락된 구현, 예정된 기능 중 미완성된 항목 등을 기록하여 후속 작업 시 참고할 수 있도록 정리한 리포트입니다.

---

## ✅ 구현 누락 / 미완성 항목

### 1. MetadataBuilder - WriteImageDefinitions()

- 초기 리포트에서는 미구현으로 표기되었으나 현재 함수 정의와 호출은 존재함.
- 다만 `imageDefinitions`에 실질적인 데이터를 채워 넣지 않아 출력 결과가 의미 없는 값으로 남아 있음.
- `.data` 섹션으로부터 실제 `Il2CppImageDefinition` 구조체 배열을 읽어와 설정할 필요가 있음.


### 2. GameAssembly.dll 기반 전체 메타데이터 재구성 실패

- 현재 빌드된 `global-metadata.dat`에는 헤더와 문자열 관련 정보만 기록되어 약 130바이트 크기에 머무른다.
- `LoadMetadataPointers()`에서 주소값을 하드코딩하고 일부 테이블 포인터만 읽어 오기 때문에 필요한 모든 구조체 데이터를 수집하지 못함.
- 따라서 현재 상태로는 `Assembly-CSharp.dll` 복원을 위한 완전한 메타데이터 생성이 불가능함.

### 3. 필드 및 프로퍼티 섹션 처리 현황

- `FieldDefinitions`와 `PropertyDefinitions` 구조체 정의 및 쓰기 함수는 구현된 상태.
- 메모리에서 배열을 읽어 오도록 `MemoryReader`와 `main.cpp`가 연결돼 있으나 실제 덤프 데이터가 불완전하여 결과 검증이 필요함.

---

## 🧪 향후 기능 제안

- `global-metadata.dat` 출력 전, 구조체 개수/누락 여부를 사전 로그로 출력
- JSON 또는 YAML 기반의 구조체 미리보기 / 외부 설정 대응 기능
- Il2CppDumper와 유사한 symbol-name matching 기능 (선택 사항)
- `ImageDefinitions` 배열을 실데이터로 채우기 위한 파싱 로직 구현
- 필드 및 프로퍼티 섹션 오프셋 자동 탐색과 검증 루틴 추가

