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

void MetadataBuilder::Build()
{
    std::ofstream file(outputPath, std::ios::binary);
    if (!file)
        return;

    WriteMetadataHeader(file);
    WriteTypeDefinitions(file);
    WriteMethodDefinitions(file);
    WriteStringLiteralTable(file);
    WriteMetadataUsages(file);
    WriteImageDefinitions(file);

    file.close();
}

void MetadataBuilder::WriteMetadataHeader(std::ofstream& file)
{
    Il2CppGlobalMetadataHeader header{};
    header.sanity = 0xFAB11BAF;
    header.version = 31;
    header.stringLiteralOffset = sizeof(Il2CppGlobalMetadataHeader);
    header.stringLiteralCount = static_cast<uint32_t>(stringLiterals.size());
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
    // Placeholder for image definitions output
}

