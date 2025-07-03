# Il2CppMetaForge

Il2CppMetaForge는 Unity 게임(마비노기 모바일)의 `.data` 섹션에서 추출한 메타데이터 포인터를 이용해
`global-metadata.dat`을 정적으로 재구성하는 도구입니다. 기존 Il2CppDumper를 사용하기
어려운 환경에서도 메모리 덤프만으로 `Assembly-CSharp.dll`을 분석할 수 있도록 돕는 것을
목표.

## 사용 방법

빌드 후 아래와 같이 실행합니다.

```bash
./Il2CppMetaForge <GameAssembly.dll> <imageBase> <dataSectionVA> <dataFileOffset>
./Il2CppMetaForge --config config.txt <GameAssembly.dll>
```

`config.txt` 예시:

```text
0x140000000
0x000000018D461A80
0x02100000
```

## 구현 현황과 한계

현재 `MemoryReader`와 `MetadataBuilder`는 기본적인 구조체 정의와 각 섹션 쓰기 함수를 포함합니다.
`FieldDefinitions`, `PropertyDefinitions`, `ParameterDefinitions`, `AssemblyDefinitions` 섹션까지 함수 형태는 갖추었으나 실제 GameAssembly.dll에서 읽어 올 데이터가 제한적입니다.
`WriteImageDefinitions()` 또한 호출은 이루어지지만, 실질적인 `Il2CppImageDefinition` 값이 없으므로 출력되는 데이터가 의미가 없습니다.

이로 인해 생성된 `global-metadata.dat` 파일은 약 150바이트 수준의 헤더와 문자열 영역만을 포함하며, 필드·메서드 등 핵심 테이블 정보가 빈 상태로 남습니다.

## Il2CppDumper 실행 가능 여부

`REPORTS.md`에 명시된 바와 같이 모든 메타데이터 테이블을 완전히 채우지 못하기 때문에
현재 빌드된 `global-metadata.dat`만으로는 Il2CppDumper를 정상적으로 실행할 수 없습니다.

## 간단한 빌드 및 테스트 예시

```bash
cd Il2CppMetaForge/Il2CppMetaForge
chmod +x build.sh
./build.sh
cd ..
# 더미 파일을 입력하여 실행 예시
./build/Il2CppMetaForge /tmp/dummy.bin 0x140000000 0x000000018D461A80 0x02100000
```

위 테스트 결과 생성된 파일 크기는 약 146바이트로, 실제 게임 메타데이터를 반영하기에는 매우 부족합니다.
