# 📓 REPORTS.md

이 문서는 Il2CppMetaForge 프로젝트에서 발생한 오류, 누락된 구현, 예정된 기능 중 미완성된 항목 등을 기록하여 후속 작업 시 참고할 수 있도록 정리한 리포트입니다.

---

## ✅ 구현 누락 / 미완성 항목

### 1. MetadataBuilder - WriteImageDefinitions()

- 초기 리포트에서는 미구현으로 표기되었으나 현재 함수 정의와 호출은 존재함.
- 다만 `imageDefinitions`에 실질적인 데이터를 채워 넣지 않아 출력 결과가 의미 없는 값으로 남아 있음.
- `.data` 섹션으로부터 실제 `Il2CppImageDefinition` 구조체 배열을 읽어와 설정할 필요가 있음.


### 2. GameAssembly.dll 기반 전체 메타데이터 재구성 실패

- 실제 실행 결과 `global-metadata.dat` 파일 크기가 130바이트에 불과하여 Unity가 요구하는 수십 MB 규모의 메타데이터와 현저히 차이남.
- `LoadMetadataPointers()`에서 주소값을 하드코딩하고 일부 테이블 포인터만 읽어 오기 때문에 필요한 모든 구조체 데이터를 수집하지 못함.
- 따라서 현재 상태로는 `Assembly-CSharp.dll` 복원을 위한 완전한 메타데이터 생성이 불가능함.

---

## 🧪 향후 기능 제안

- `global-metadata.dat` 출력 전, 구조체 개수/누락 여부를 사전 로그로 출력
- JSON 또는 YAML 기반의 구조체 미리보기 / 외부 설정 대응 기능
- Il2CppDumper와 유사한 symbol-name matching 기능 (선택 사항)

