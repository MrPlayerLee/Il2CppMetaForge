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

    // 리더가 제공한 포인터들을 이용하여 메모리 개체를 부팅한다.
    Il2CppTypeDefinition typeDef = reader.ReadStruct<Il2CppTypeDefinition>(gameAssembly,
        reader.RvaToFileOffset(reader.GetTypeDefinitions()));
    std::vector<Il2CppTypeDefinition> types{typeDef};

    Il2CppMethodDefinition methodDef = reader.ReadStruct<Il2CppMethodDefinition>(gameAssembly,
        reader.RvaToFileOffset(reader.GetMethodDefinitions()));
    std::vector<Il2CppMethodDefinition> methods{methodDef};

    Il2CppStringLiteral literal = reader.ReadStruct<Il2CppStringLiteral>(gameAssembly,
        reader.RvaToFileOffset(reader.GetStringLiteralTable()));
    std::vector<Il2CppStringLiteral> literals{literal};

    std::vector<char> literalData(literal.length + 1);
    gameAssembly.seekg(reader.RvaToFileOffset(reader.GetStringLiteralTable()) + sizeof(Il2CppStringLiteral), std::ios::beg);
    gameAssembly.read(literalData.data(), literal.length);
    literalData[literal.length] = '\0';

    uint32_t usageCount = reader.ReadStruct<uint32_t>(gameAssembly,
        reader.RvaToFileOffset(reader.GetMetadataUsagesCount()));
    std::vector<Il2CppMetadataUsage> usages = reader.ReadStructArray<Il2CppMetadataUsage>(
        gameAssembly, reader.RvaToFileOffset(reader.GetMetadataUsages()), usageCount);

    std::vector<char> stringTable;
    auto addString = [&stringTable](const char* str) -> uint32_t
    {
        uint32_t index = static_cast<uint32_t>(stringTable.size());
        size_t len = std::strlen(str);
        stringTable.insert(stringTable.end(), str, str + len + 1);
        return index;
    };

    uint32_t asmNameIndex = addString("Assembly-CSharp");
    uint32_t typeNameIndex = addString("DummyType");
    uint32_t nsNameIndex = addString("DummyNS");
    uint32_t methodNameIndex = addString("DummyMethod");
    uint32_t fieldNameIndex = addString("dummyField");
    uint32_t propertyNameIndex = addString("dummyProperty");

    // 문자열 오프셋을 구조체에 기록
    types[0].nameIndex = typeNameIndex;
    types[0].namespaceIndex = nsNameIndex;
    methods[0].nameIndex = methodNameIndex;
    types[0].fieldStart = 0;
    types[0].field_count = 1;
    types[0].propertyStart = 0;
    types[0].property_count = 1;
    types[0].methodStart = 0;
    types[0].method_count = static_cast<uint32_t>(methods.size());

    std::vector<Il2CppImageDefinition> images(1);
    images[0] = {};
    images[0].nameIndex = asmNameIndex; // "Assembly-CSharp"
    images[0].typeStart = 0;
    images[0].typeCount = static_cast<uint32_t>(types.size());

    Il2CppFieldDefinition field{};
    field.nameIndex = fieldNameIndex;
    field.typeIndex = 0;
    field.customAttributeIndex = 0;
    field.token = 0;
    std::vector<Il2CppFieldDefinition> fields{field};

    Il2CppPropertyDefinition prop{};
    prop.nameIndex = propertyNameIndex;
    prop.getter = 0;
    prop.setter = 0;
    prop.customAttributeIndex = 0;
    prop.token = 0;
    std::vector<Il2CppPropertyDefinition> properties{prop};

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
