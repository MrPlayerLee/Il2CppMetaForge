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

void MetadataBuilder::SetStrings(const std::vector<char>& strs)
{
    strings = strs;
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
    WriteStringLiteralData(file);
    WriteStringTable(file);
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
    offset += static_cast<uint32_t>(stringLiterals.size() * sizeof(Il2CppStringLiteral));

    header.stringLiteralDataOffset = offset;
    header.stringLiteralDataCount = static_cast<uint32_t>(stringLiteralData.size());
    offset += static_cast<uint32_t>(stringLiteralData.size());

    header.stringOffset = offset;
    header.stringCount = static_cast<uint32_t>(strings.size());
    offset += static_cast<uint32_t>(strings.size());

    header.methodDefinitionOffset = offset;
    header.methodDefinitionCount = static_cast<uint32_t>(methodDefinitions.size());
    offset += static_cast<uint32_t>(methodDefinitions.size() * sizeof(Il2CppMethodDefinition));

    header.typeDefinitionOffset = offset;
    header.typeDefinitionCount = static_cast<uint32_t>(typeDefinitions.size());
    offset += static_cast<uint32_t>(typeDefinitions.size() * sizeof(Il2CppTypeDefinition));

    header.imageDefinitionOffset = offset;
    header.imageDefinitionCount = static_cast<uint32_t>(imageDefinitions.size());
    offset += static_cast<uint32_t>(imageDefinitions.size() * sizeof(Il2CppImageDefinition));

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
}

void MetadataBuilder::WriteStringLiteralData(std::ofstream& file)
{
    file.write(stringLiteralData.data(), stringLiteralData.size());
}

void MetadataBuilder::WriteStringTable(std::ofstream& file)
{
    file.write(strings.data(), strings.size());
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

