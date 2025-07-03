#include <iostream>
#include <vector>
#include <cstring>
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

    // \uC2A4\uD305 \uB370\uC774\uD130\uB97C \uBAA8\uB450 \uC2DC\uC791 \uB9CC\uD07C \uD55C \uAC1C\uC529 \uC77D\uC5B4\uC624\uAE30
    std::vector<char> stringTable;
    const char* names[] = {"Assembly-CSharp", "MyClass", "Utils", "Foo"};
    for (const char* n : names)
    {
        size_t len = std::strlen(n);
        stringTable.insert(stringTable.end(), n, n + len + 1);
    }

    uint32_t typeCount = reader.ReadStruct<uint32_t>(gameAssembly,
        reader.RvaToFileOffset(reader.GetTypeDefinitionsCount()));
    std::vector<Il2CppTypeDefinition> types = reader.ReadStructArray<Il2CppTypeDefinition>(
        gameAssembly,
        reader.RvaToFileOffset(reader.GetTypeDefinitions()),
        typeCount);

    uint32_t methodCount = reader.ReadStruct<uint32_t>(gameAssembly,
        reader.RvaToFileOffset(reader.GetMethodDefinitionsCount()));
    std::vector<Il2CppMethodDefinition> methods = reader.ReadStructArray<Il2CppMethodDefinition>(
        gameAssembly,
        reader.RvaToFileOffset(reader.GetMethodDefinitions()),
        methodCount);

    uint32_t literalCount = reader.ReadStruct<uint32_t>(gameAssembly,
        reader.RvaToFileOffset(reader.GetStringLiteralTableCount()));
    std::vector<Il2CppStringLiteral> literals = reader.ReadStructArray<Il2CppStringLiteral>(
        gameAssembly,
        reader.RvaToFileOffset(reader.GetStringLiteralTable()),
        literalCount);
    size_t literalDataSize = 0;
    for (const auto& lit : literals)
        if (lit.dataIndex + lit.length > literalDataSize)
            literalDataSize = lit.dataIndex + lit.length;
    std::vector<char> literalData(literalDataSize);
    uint64_t literalDataOffset = reader.RvaToFileOffset(reader.GetStringLiteralTable() + sizeof(Il2CppStringLiteral) * literalCount);
    gameAssembly.seekg(literalDataOffset, std::ios::beg);
    gameAssembly.read(literalData.data(), literalDataSize);

    std::vector<Il2CppMetadataUsage> usages;
    uint32_t usageCount = reader.ReadStruct<uint32_t>(gameAssembly,
        reader.RvaToFileOffset(reader.GetMetadataUsagesCount()));
    uintptr_t usagePtr = reader.GetMetadataUsages();
    if (usageCount > 0)
    {
        Il2CppMetadataUsage usage = reader.ReadStruct<Il2CppMetadataUsage>(gameAssembly,
            reader.RvaToFileOffset(usagePtr));
        usages.push_back(usage);
    }

    std::vector<Il2CppImageDefinition> images(1);
    images[0] = {};
    images[0].nameIndex = 0;
    images[0].typeStart = 0;
    images[0].typeCount = static_cast<uint32_t>(types.size());

    builder.SetTypeDefinitions(types);
    builder.SetMethodDefinitions(methods);
    builder.SetStringLiterals(literals, literalData);
    builder.SetStrings(stringTable);
    builder.SetMetadataUsages(usages);
    builder.SetImageDefinitions(images);

    builder.Build();

    std::cout << "metadata build complete" << std::endl;
    return 0;
}
