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

void MetadataBuilder::SetFieldDefinitions(const std::vector<Il2CppFieldDefinition>& defs)
{
    fieldDefinitions = defs;
}

void MetadataBuilder::SetPropertyDefinitions(const std::vector<Il2CppPropertyDefinition>& defs)
{
    propertyDefinitions = defs;
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

void MetadataBuilder::SetParameterDefinitions(const std::vector<Il2CppParameterDefinition>& defs)
{
    parameterDefinitions = defs;
}

void MetadataBuilder::SetAssemblyDefinitions(const std::vector<Il2CppAssemblyDefinition>& defs)
{
    assemblyDefinitions = defs;
}

void MetadataBuilder::SetGenericContainers(const std::vector<Il2CppGenericContainer>& defs)
{
    genericContainers = defs;
}

void MetadataBuilder::SetGenericParameters(const std::vector<Il2CppGenericParameter>& defs)
{
    genericParameters = defs;
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
    WriteParameterDefinitions(file);
    WriteFieldDefinitions(file);
    WritePropertyDefinitions(file);
    WriteTypeDefinitions(file);
    WriteMetadataUsages(file);
    WriteImageDefinitions(file);
    WriteAssemblyDefinitions(file);
    WriteGenericContainers(file);
    WriteGenericParameters(file);

    file.close();
}

void MetadataBuilder::WriteMetadataHeader(std::ofstream& file)
{
    Il2CppGlobalMetadataHeader header{};
    header.sanity  = 0xFAB11BAF;
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

    header.parameterDefinitionOffset = offset;
    header.parameterDefinitionCount = static_cast<uint32_t>(parameterDefinitions.size());
    offset += static_cast<uint32_t>(parameterDefinitions.size() * sizeof(Il2CppParameterDefinition));

    header.fieldDefinitionOffset = offset;
    header.fieldDefinitionCount = static_cast<uint32_t>(fieldDefinitions.size());
    offset += static_cast<uint32_t>(fieldDefinitions.size() * sizeof(Il2CppFieldDefinition));

    header.propertyDefinitionOffset = offset;
    header.propertyDefinitionCount = static_cast<uint32_t>(propertyDefinitions.size());
    offset += static_cast<uint32_t>(propertyDefinitions.size() * sizeof(Il2CppPropertyDefinition));

    header.typeDefinitionOffset = offset;
    header.typeDefinitionCount = static_cast<uint32_t>(typeDefinitions.size());
    offset += static_cast<uint32_t>(typeDefinitions.size() * sizeof(Il2CppTypeDefinition));

    // 메타데이터 사용 정보 테이블의 크기를 오프셋 계산에 포함한다
    offset += static_cast<uint32_t>(metadataUsages.size() * sizeof(Il2CppMetadataUsage));

    header.imageDefinitionOffset = offset;
    header.imageDefinitionCount = static_cast<uint32_t>(imageDefinitions.size());
    offset += static_cast<uint32_t>(imageDefinitions.size() * sizeof(Il2CppImageDefinition));

    header.assemblyDefinitionOffset = offset;
    header.assemblyDefinitionCount = static_cast<uint32_t>(assemblyDefinitions.size());
    offset += static_cast<uint32_t>(assemblyDefinitions.size() * sizeof(Il2CppAssemblyDefinition));

    header.genericContainerOffset = offset;
    header.genericContainerCount = static_cast<uint32_t>(genericContainers.size());
    offset += static_cast<uint32_t>(genericContainers.size() * sizeof(Il2CppGenericContainer));

    header.genericParameterOffset = offset;
    header.genericParameterCount = static_cast<uint32_t>(genericParameters.size());
    offset += static_cast<uint32_t>(genericParameters.size() * sizeof(Il2CppGenericParameter));

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

void MetadataBuilder::WriteFieldDefinitions(std::ofstream& file)
{
    for (const auto& def : fieldDefinitions)
        file.write(reinterpret_cast<const char*>(&def), sizeof(def));
}

void MetadataBuilder::WritePropertyDefinitions(std::ofstream& file)
{
    for (const auto& def : propertyDefinitions)
        file.write(reinterpret_cast<const char*>(&def), sizeof(def));
}

void MetadataBuilder::WriteParameterDefinitions(std::ofstream& file)
{
    for (const auto& def : parameterDefinitions)
        file.write(reinterpret_cast<const char*>(&def), sizeof(def));
}

void MetadataBuilder::WriteAssemblyDefinitions(std::ofstream& file)
{
    for (const auto& def : assemblyDefinitions)
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

void MetadataBuilder::WriteGenericContainers(std::ofstream& file)
{
    for (const auto& c : genericContainers)
        file.write(reinterpret_cast<const char*>(&c), sizeof(c));
}

void MetadataBuilder::WriteGenericParameters(std::ofstream& file)
{
    for (const auto& p : genericParameters)
        file.write(reinterpret_cast<const char*>(&p), sizeof(p));
}

