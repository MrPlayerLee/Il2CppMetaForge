#include <iostream>
#include "MemoryReader.h"
#include "MetadataBuilder.h"

int main()
{
    // MemoryReader 초기화: .data 섹션 시작 주소를 넣어야 함
    uintptr_t dataSectionVA = 0x000000018D461A80; // 예시 주소, 실 사용 시 정확한 값 필요
    MemoryReader reader(dataSectionVA);

    // MetadataBuilder 초기화
    MetadataBuilder builder(reader);

    // global-metadata.dat 파일 생성
    const std::string outputPath = "global-metadata.dat";
    if (builder.Build(outputPath))
    {
        std::cout << "global-metadata.dat 파일 생성 완료." << std::endl;
    }
    else
    {
        std::cerr << "파일 생성 실패." << std::endl;
        return 1;
    }

    return 0;
}
