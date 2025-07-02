#include <iostream>
#include "MemoryReader.h"
#include "MetadataBuilder.h"

int main()
{
    uintptr_t imageBase = 0x140000000;
    uintptr_t dataSectionVA = 0x000000018D461A80;
    uint64_t dataFileOffset = 0x02100000;

    MemoryReader reader(imageBase, dataSectionVA, dataFileOffset);

    const std::string outputPath = "global-metadata.dat";
    MetadataBuilder builder(outputPath);

    std::ifstream gameAssembly("test/mabinogi/GameAssembly.dll", std::ios::binary);
    if (!gameAssembly)
    {
        std::cerr << "GameAssembly.dll open failed" << std::endl;
        return 1;
    }

    reader.LoadMetadataPointers(gameAssembly);
    builder.Build();

    std::cout << "metadata build complete" << std::endl;
    return 0;
}
