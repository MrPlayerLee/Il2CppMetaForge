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
최근 업데이트로 `ParameterDefinitions`, `AssemblyDefinitions`는 물론 `GenericContainers`와 `GenericParameters` 테이블까지 GameAssembly.dll에서 읽어 들입니다.
또한 빌드 전 각 구조체 포인터와 개수를 출력하는 `LogStructStatus()` 루틴을 추가해 유효성을 쉽게 확인할 수 있습니다.
`WriteImageDefinitions()`는 여전히 실제 `Il2CppImageDefinition` 데이터를 사용하지 못해 출력 결과가 불완전합니다.

업데이트된 로직 덕분에 더 많은 메타데이터가 채워지지만, 일부 테이블이 비어 있어 완전한 메타데이터와는 거리가 있습니다.

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
