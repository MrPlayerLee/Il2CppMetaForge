#include <iostream>
#include <vector>
#include "MemoryReader.h"
#include "MetadataBuilder.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: Il2CppMetaForge <GameAssembly.dll path>" << std::endl;
        return 1;
    }

    const char* dllPath = argv[1];

    uintptr_t imageBase = 0x140000000;
    uintptr_t dataSectionVA = 0x000000018D461A80;
    uint64_t dataFileOffset = 0x02100000;

    MemoryReader reader(imageBase, dataSectionVA, dataFileOffset);

    const std::string outputPath = "global-metadata.dat";
    MetadataBuilder builder(outputPath);

    std::ifstream gameAssembly(dllPath, std::ios::binary);
    if (!gameAssembly)
    {
        std::cerr << "GameAssembly.dll open failed" << std::endl;
        return 1;
    }

    reader.LoadMetadataPointers(gameAssembly);

    // 더미 데이터 주입
    std::vector<Il2CppTypeDefinition> types(1);
    std::vector<Il2CppMethodDefinition> methods(1);
    std::vector<Il2CppStringLiteral> literals(1);
    std::vector<char> literalData(4, '\0');
    std::vector<Il2CppMetadataUsage> usages(1);
    std::vector<Il2CppImageDefinition> images(1);

    builder.SetTypeDefinitions(types);
    builder.SetMethodDefinitions(methods);
    builder.SetStringLiterals(literals, literalData);
    builder.SetMetadataUsages(usages);
    builder.SetImageDefinitions(images);

    builder.Build();

    std::cout << "metadata build complete" << std::endl;
    return 0;
}
