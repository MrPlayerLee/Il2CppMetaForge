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
