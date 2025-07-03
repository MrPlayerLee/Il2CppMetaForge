# 📓 REPORTS.md

이 문서는 Il2CppMetaForge 프로젝트에서 발생한 오류, 누락된 구현, 예정된 기능 중 미완성된 항목 등을 기록하여 후속 작업 시 참고할 수 있도록 정리한 리포트입니다.

---

## ✅ 구현 누락 / 미완성 항목

### 1. MetadataBuilder - WriteImageDefinitions()

- 초기 리포트에서는 미구현으로 표기되었으나 현재 함수 정의와 호출은 존재함.
- 다만 `imageDefinitions`에 실질적인 데이터를 채워 넣지 않아 출력 결과가 의미 없는 값으로 남아 있음.
- `.data` 섹션으로부터 실제 `Il2CppImageDefinition` 구조체 배열을 읽어와 설정할 필요가 있음.

### 2. main.cpp - 데이터 설정 누락

- `MetadataBuilder::SetTypeDefinitions(...)` 등 실제 데이터를 주입하는 함수들이 호출되지 않음.
- 그로 인해 `Build()` 호출 시 출력되는 global-metadata.dat는 오직 헤더 40바이트만 포함되어 있음.
- 최소한 테스트 목적으로 dummy vector라도 주입 필요함.

### 3. GameAssembly.dll 기반 전체 메타데이터 재구성 실패

- 실제 실행 결과 `global-metadata.dat` 파일 크기가 130바이트에 불과하여 Unity가 요구하는 수십 MB 규모의 메타데이터와 현저히 차이남.
- `LoadMetadataPointers()`에서 주소값을 하드코딩하고 일부 테이블 포인터만 읽어 오기 때문에 필요한 모든 구조체 데이터를 수집하지 못함.
- 따라서 현재 상태로는 `Assembly-CSharp.dll` 복원을 위한 완전한 메타데이터 생성이 불가능함.

---

## ⚠️ 경고 / 개선 사항

### 1. GameAssembly.dll 경로 하드코딩

- 현재 `main.cpp`은 `test/mabinogi/GameAssembly.dll`로 경로를 특정하고 결정적으로 `ifstream` 연결을 시도합니다:

```cpp
    std::ifstream gameAssembly("test/mabinogi/GameAssembly.dll", std::ios::binary);
```

- 이 경로는 다른 경로에서 실행 시 모두 시도 실패하기 때문에, CLI 인자에서 경로 입력되는 것이 가장 적절합니다.
- (예: `Il2CppMetaForge.exe GameAssembly.dll`)

### 2. CLI 사용자 편의성 부족

- 현재 실행 인자를 입력하지 않으면 "GameAssembly.dll open failed" 라는 메시지만 출력되고 종료됨.
- 사용법 안내 (`Usage: Il2CppMetaForge <GameAssembly.dll path>`) 혹은 도움말 출력 기능 필요함.

---

## 🧪 향후 기능 제안

- `global-metadata.dat` 출력 전, 구조체 개수/누락 여부를 사전 로그로 출력
- JSON 또는 YAML 기반의 구조체 미리보기 / 외부 설정 대응 기능
- Il2CppDumper와 유사한 symbol-name matching 기능 (선택 사항)

