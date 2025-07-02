#include <iostream>
#include "MemoryReader.h"
#include "MetadataBuilder.h"

int main()
{
    // MemoryReader �ʱ�ȭ: .data ���� ���� �ּҸ� �־�� ��
    uintptr_t dataSectionVA = 0x000000018D461A80; // ���� �ּ�, �� ��� �� ��Ȯ�� �� �ʿ�
    MemoryReader reader(dataSectionVA);

    // MetadataBuilder �ʱ�ȭ
    MetadataBuilder builder(reader);

    // global-metadata.dat ���� ����
    const std::string outputPath = "global-metadata.dat";
    if (builder.Build(outputPath))
    {
        std::cout << "global-metadata.dat ���� ���� �Ϸ�." << std::endl;
    }
    else
    {
        std::cerr << "���� ���� ����." << std::endl;
        return 1;
    }

    return 0;
}
