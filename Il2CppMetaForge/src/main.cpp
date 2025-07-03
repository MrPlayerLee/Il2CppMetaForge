#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include "MemoryReader.h"
#include "MetadataBuilder.h"

void PrintUsage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "  Il2CppMetaForge <GameAssembly.dll> <imageBase> <dataSectionVA> <dataFileOffset>" << std::endl;
    std::cout << "  Il2CppMetaForge --config <config.txt> <GameAssembly.dll>" << std::endl;
    std::cout << "  Values can be in hex (0x...) or decimal." << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        PrintUsage();
        return 1;
    }

    const char* dllPath = nullptr;

    uintptr_t imageBase = 0;
    uintptr_t dataSectionVA = 0;
    uint64_t dataFileOffset = 0;

    if ((std::strcmp(argv[1], "--config") == 0 || std::strcmp(argv[1], "-c") == 0))
    {
        if (argc < 4)
        {
            PrintUsage();
            return 1;
        }
        std::ifstream cfg(argv[2]);
        if (!cfg)
        {
            std::cerr << "Config file open failed" << std::endl;
            return 1;
        }
        cfg >> std::hex >> imageBase >> dataSectionVA >> dataFileOffset;
        if (!cfg)
        {
            std::cerr << "Config format invalid" << std::endl;
            return 1;
        }
        dllPath = argv[3];
    }
    else if (argc >= 5)
    {
        dllPath = argv[1];
        imageBase = std::stoull(argv[2], nullptr, 0);
        dataSectionVA = std::stoull(argv[3], nullptr, 0);
        dataFileOffset = std::stoull(argv[4], nullptr, 0);
    }
    else
    {
        PrintUsage();
        return 1;
    }

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

    uint32_t typeCount = reader.GetTypeDefinitionsCount();
    std::vector<Il2CppTypeDefinition> types = reader.ReadStructArray<Il2CppTypeDefinition>(
        gameAssembly,
        reader.RvaToFileOffset(reader.GetTypeDefinitions()),
        typeCount);

    uint32_t methodCount = reader.GetMethodDefinitionsCount();
    std::vector<Il2CppMethodDefinition> methods = reader.ReadStructArray<Il2CppMethodDefinition>(
        gameAssembly,
        reader.RvaToFileOffset(reader.GetMethodDefinitions()),
        methodCount);

    uint32_t fieldCount = reader.GetFieldDefinitionsCount();
    std::vector<Il2CppFieldDefinition> fields = reader.ReadStructArray<Il2CppFieldDefinition>(
        gameAssembly,
        reader.RvaToFileOffset(reader.GetFieldDefinitions()),
        fieldCount);

    uint32_t propertyCount = reader.GetPropertyDefinitionsCount();
    std::vector<Il2CppPropertyDefinition> properties = reader.ReadStructArray<Il2CppPropertyDefinition>(
        gameAssembly,
        reader.RvaToFileOffset(reader.GetPropertyDefinitions()),
        propertyCount);

    uint32_t literalCount = reader.GetStringLiteralTableCount();
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

    uint32_t usageCount = reader.GetMetadataUsagesCount();
    std::vector<Il2CppMetadataUsage> usages = reader.ReadStructArray<Il2CppMetadataUsage>(
        gameAssembly,
        reader.RvaToFileOffset(reader.GetMetadataUsages()),
        usageCount);

    std::vector<Il2CppImageDefinition> images(1);
    images[0] = {};
    images[0].nameIndex = 0;
    images[0].typeStart = 0;
    images[0].typeCount = static_cast<uint32_t>(types.size());

    builder.SetTypeDefinitions(types);
    builder.SetMethodDefinitions(methods);
    builder.SetFieldDefinitions(fields);
    builder.SetPropertyDefinitions(properties);
    builder.SetStringLiterals(literals, literalData);
    builder.SetStrings(stringTable);
    builder.SetMetadataUsages(usages);
    builder.SetImageDefinitions(images);

    builder.Build();

    std::cout << "metadata build complete" << std::endl;
    return 0;
}
