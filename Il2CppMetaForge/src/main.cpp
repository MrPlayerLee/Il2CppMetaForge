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

    // \uAE30\uBCF8 \uAD6C\uC870\uCCB4 \uC124\uC815
    std::vector<char> stringTable;
    const char* names[] = {"Assembly-CSharp", "MyClass", "Utils", "Foo"};
    for (const char* n : names)
    {
        size_t len = std::strlen(n);
        stringTable.insert(stringTable.end(), n, n + len + 1);
    }

    std::vector<Il2CppImageDefinition> images(1);
    images[0] = {};
    images[0].nameIndex = 0;      // "Assembly-CSharp"
    images[0].typeStart = 0;
    images[0].typeCount = 1;

    std::vector<Il2CppTypeDefinition> types(1);
    types[0] = {};
    types[0].nameIndex = 1;        // "MyClass"
    types[0].namespaceIndex = 2;   // "Utils"
    types[0].methodStart = 0;
    types[0].method_count = 1;

    std::vector<Il2CppMethodDefinition> methods(1);
    methods[0] = {};
    methods[0].nameIndex = 3;      // "Foo"
    methods[0].declaringType = 0;
    methods[0].returnType = 0;
    methods[0].parameterCount = 0;

    std::vector<Il2CppStringLiteral> literals(1);
    literals[0].length = 4;
    literals[0].dataIndex = 0;

    std::vector<char> literalData = {'T', 'e', 's', 't', '\0'};

    std::vector<Il2CppMetadataUsage> usages(1);

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
