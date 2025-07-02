#include "MetadataBuilder.h"
#include <cstring>

MetadataBuilder::MetadataBuilder(const std::string& path)
    : outputPath(path) {}

void MetadataBuilder::SetTypeDefinitions(const std::vector<Il2CppTypeDefinition>& defs)
{
    typeDefinitions = defs;
}

void MetadataBuilder::SetMethodDefinitions(const std::vector<Il2CppMethodDefinition>& defs)
{
    methodDefinitions = defs;
}

void MetadataBuilder::SetStringLiterals(const std::vector<Il2CppStringLiteral>& literals,
                                        const std::vector<char>& stringData)
{
    stringLiterals = literals;
    stringLiteralData = stringData;
}

void MetadataBuilder::SetMetadataUsages(const std::vector<Il2CppMetadataUsage>& usages)
{
    metadataUsages = usages;
}

void MetadataBuilder::SetImageDefinitions(const std::vector<Il2CppImageDefinition>& images)
{
    imageDefinitions = images;
}

void MetadataBuilder::Build()
{
    std::ofstream file(outputPath, std::ios::binary);
    if (!file)
        return;

    WriteMetadataHeader(file);
    WriteStringLiteralTable(file);
    WriteMethodDefinitions(file);
    WriteTypeDefinitions(file);
    WriteMetadataUsages(file);
    WriteImageDefinitions(file);

    file.close();
}

void MetadataBuilder::WriteMetadataHeader(std::ofstream& file)
{
    Il2CppGlobalMetadataHeader header{};
    header.sanity = 0xFAB11BAF;
    header.version = 31;

    uint32_t offset = sizeof(Il2CppGlobalMetadataHeader);
    header.stringLiteralOffset = offset;
    header.stringLiteralCount = static_cast<uint32_t>(stringLiterals.size());
    offset += static_cast<uint32_t>(stringLiterals.size() * sizeof(Il2CppStringLiteral) +
                                   stringLiteralData.size());

    header.stringOffset = offset;
    header.stringCount = 0; // \uBCC0\uACBD\uB41C \uBB38\uC790 \uD14C\uC774\uBE14\uC740 \uC5C6\uC74C

    header.methodDefinitionOffset = offset;
    header.methodDefinitionCount = static_cast<uint32_t>(methodDefinitions.size());
    offset += static_cast<uint32_t>(methodDefinitions.size() * sizeof(Il2CppMethodDefinition));

    header.typeDefinitionOffset = offset;
    header.typeDefinitionCount = static_cast<uint32_t>(typeDefinitions.size());
    offset += static_cast<uint32_t>(typeDefinitions.size() * sizeof(Il2CppTypeDefinition));

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
}

void MetadataBuilder::WriteTypeDefinitions(std::ofstream& file)
{
    for (const auto& def : typeDefinitions)
        file.write(reinterpret_cast<const char*>(&def), sizeof(def));
}

void MetadataBuilder::WriteMethodDefinitions(std::ofstream& file)
{
    for (const auto& def : methodDefinitions)
        file.write(reinterpret_cast<const char*>(&def), sizeof(def));
}

void MetadataBuilder::WriteStringLiteralTable(std::ofstream& file)
{
    for (const auto& lit : stringLiterals)
        file.write(reinterpret_cast<const char*>(&lit), sizeof(lit));

    file.write(stringLiteralData.data(), stringLiteralData.size());
}

void MetadataBuilder::WriteMetadataUsages(std::ofstream& file)
{
    for (const auto& usage : metadataUsages)
        file.write(reinterpret_cast<const char*>(&usage), sizeof(usage));
}

void MetadataBuilder::WriteImageDefinitions(std::ofstream& file)
{
    for (const auto& img : imageDefinitions)
        file.write(reinterpret_cast<const char*>(&img), sizeof(img));
}

