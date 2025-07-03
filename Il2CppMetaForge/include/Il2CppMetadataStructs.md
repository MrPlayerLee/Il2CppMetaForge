# Il2CppMetadataStructs.md

## 📌 파일 위치

```
include/Il2CppMetadataStructs.h
```

## 🧭 역할

이 헤더 파일은 Unity Il2Cpp 메타데이터 구조체들의 정의를 담고 있습니다. 주로 Unity 2021+ / Il2Cpp v31 기준으로 작성되며, `global-metadata.dat` 를 생성하기 위한 구조 기반을 제공합니다.

Il2Cpp의 구조체는 `typeDefinitions`, `methodDefinitions`, `stringLiteralTable`, `metadataUsages` 및 `imageDefinitions` 등의 테이블을 통해 Unity 런타임과 상호작용합니다. 각 테이블의 오프셋과 개수는 `Il2CppGlobalMetadataHeader`에 기록되어 빌더가 생성하는 metadata 파일의 정합성을 확보합니다.


## 🛠️ 포함된 구조체들

- `Il2CppGlobalMetadataHeader`
  - metadata 파일의 헤더이며, 각 테이블의 오프셋과 개수를 기록합니다. 예를 들어 `metadataUsageOffset`, `metadataUsageCount`, `imageDefinitionOffset`, `imageDefinitionCount` 등이 포함됩니다.
- `Il2CppTypeDefinition`
  - 클래스와 인터페이스에 대한 정의입니다.
- `Il2CppMethodDefinition`
  - 각 함수에 대한 메타 정보를 담고 있습니다.
- `Il2CppStringLiteral`
  - 문자열 테이블의 엔트리를 나타냅니다.
- `Il2CppMetadataUsage`
  - 런타임 리플렉션, 메서드 바인딩 등에 사용됩니다.
- `Il2CppImageDefinition`
  - DLL 단위의 정보를 담으며, 주로 `Assembly-CSharp.dll` 하나만을 대상으로 사용됩니다.


## ⚠️ 주의점

- 구조체의 필드 정렬과 크기는 Unity 버전에 따라 다를 수 있으므로 Il2Cpp v31 기준임을 명확히 합니다.
- 모든 구조체는 `#pragma pack(push, 1)` 등의 패킹 옵션 없이 자연 정렬 기준으로 설계되어야 합니다.
- 이 헤더는 다른 빌더 또는 리더 컴포넌트와 강결합되므로 필드 순서 변경 시 전체 프로젝트에 영향을 줄 수 있습니다.

