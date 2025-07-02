# 📓 REPORTS.md

이 문서는 Il2CppMetaForge 프로젝트에서 발생한 오류, 누락된 구현, 예정된 기능 중 미완성된 항목 등을 기록하여 후속 작업 시 참고할 수 있도록 정리한 리포트입니다.

---

## ✅ 구현 누락 / 미완성 항목

### 1. MetadataBuilder - WriteImageDefinitions()

- 현재 해당 함수는 선언만 되어 있으며, `Il2CppImageDefinition` 데이터를 전혀 출력하지 않음.
- `SetImageDefinitions()`와 관련 벡터가 존재하지 않음.
- `.data` 섹션에서 추출된 `imageDefinitionsCount`를 통해 적절한 구조체 수만큼 dummy 또는 placeholder 출력이 필요함.

### 2. main.cpp - 데이터 설정 누락

- `MetadataBuilder::SetTypeDefinitions(...)` 등 실제 데이터를 주입하는 함수들이 호출되지 않음.
- 그로 인해 `Build()` 호출 시 출력되는 global-metadata.dat는 오직 헤더 40바이트만 포함되어 있음.
- 최소한 테스트 목적으로 dummy vector라도 주입 필요함.

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

