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

void MetadataBuilder::Build()
{
    std::ofstream file(outputPath, std::ios::binary);
    if (!file)
        return;

    WriteMetadataHeader(file);
    WriteStringLiteralTable(file);
    WriteStringTable(file);
    WritePropertyDefinitions(file);
    WriteMethodDefinitions(file);
    WriteFieldDefinitions(file);
    WriteTypeDefinitions(file);
    WriteMetadataUsages(file);
    WriteImageDefinitions(file);

    file.close();
}

void MetadataBuilder::WriteMetadataHeader(std::ofstream& file)
{
    Il2CppGlobalMetadataHeader header{};
    header.sanity  = 0xFAB11BAF;
    header.version = 31;

    uint32_t offset = sizeof(Il2CppGlobalMetadataHeader);
    header.stringLiteralOffset = offset;
    header.stringLiteralSize   = static_cast<int32_t>(stringLiterals.size() * sizeof(Il2CppStringLiteral));
    offset += header.stringLiteralSize;

    header.stringLiteralDataOffset = offset;
    header.stringLiteralDataSize   = static_cast<int32_t>(stringLiteralData.size());
    offset += header.stringLiteralDataSize;

    header.stringOffset = offset;
    header.stringSize   = static_cast<int32_t>(strings.size());
    offset += header.stringSize;

    header.eventsOffset    = 0;
    header.eventsSize      = 0;

    header.propertiesOffset = offset;
    header.propertiesSize   = static_cast<int32_t>(propertyDefinitions.size() * sizeof(Il2CppPropertyDefinition));
    offset += header.propertiesSize;

    header.methodsOffset = offset;
    header.methodsSize   = static_cast<int32_t>(methodDefinitions.size() * sizeof(Il2CppMethodDefinition));
    offset += header.methodsSize;

    header.parameterDefaultValuesOffset        = 0;
    header.parameterDefaultValuesSize          = 0;
    header.fieldDefaultValuesOffset            = 0;
    header.fieldDefaultValuesSize              = 0;
    header.fieldAndParameterDefaultValueDataOffset = 0;
    header.fieldAndParameterDefaultValueDataSize   = 0;
    header.fieldMarshaledSizesOffset           = 0;
    header.fieldMarshaledSizesSize             = 0;

    header.parametersOffset                   = 0;
    header.parametersSize                     = 0;

    header.fieldsOffset = offset;
    header.fieldsSize   = static_cast<int32_t>(fieldDefinitions.size() * sizeof(Il2CppFieldDefinition));
    offset += header.fieldsSize;
    header.genericParametersOffset            = 0;
    header.genericParametersSize              = 0;
    header.genericParameterConstraintsOffset  = 0;
    header.genericParameterConstraintsSize    = 0;
    header.genericContainersOffset            = 0;
    header.genericContainersSize              = 0;
    header.nestedTypesOffset                  = 0;
    header.nestedTypesSize                    = 0;
    header.interfacesOffset                   = 0;
    header.interfacesSize                     = 0;
    header.vtableMethodsOffset                = 0;
    header.vtableMethodsSize                  = 0;
    header.interfaceOffsetsOffset             = 0;
    header.interfaceOffsetsSize               = 0;

    header.typeDefinitionsOffset = offset;
    header.typeDefinitionsSize   = static_cast<int32_t>(typeDefinitions.size() * sizeof(Il2CppTypeDefinition));
    offset += header.typeDefinitionsSize;

    header.rgctxEntriesOffset = 0;
    header.rgctxEntriesCount  = 0;

    header.imagesOffset = 0; // temporary, actual value set later
    header.imagesSize   = 0;
    header.imageDefinitionOffset = 0;
    header.imageDefinitionCount  = 0;

    header.assembliesOffset = 0;
    header.assembliesSize   = 0;

    header.metadataUsageListsOffset = 0;
    header.metadataUsageListsCount  = 0;
    header.metadataUsagePairsOffset = offset;
    header.metadataUsagePairsCount  = static_cast<int32_t>(metadataUsages.size());
    offset += static_cast<uint32_t>(metadataUsages.size() * sizeof(Il2CppMetadataUsage));
    header.metadataUsageOffset = header.metadataUsagePairsOffset;
    header.metadataUsageCount  = header.metadataUsagePairsCount;

    header.fieldRefsOffset           = 0;
    header.fieldRefsSize             = 0;
    header.referencedAssembliesOffset = 0;
    header.referencedAssembliesSize   = 0;
    header.attributesInfoOffset       = 0;
    header.attributesInfoCount        = 0;
    header.attributeTypesOffset       = 0;
    header.attributeTypesCount        = 0;
    header.attributeDataOffset        = 0;
    header.attributeDataSize          = 0;
    header.attributeDataRangeOffset   = 0;
    header.attributeDataRangeSize     = 0;
    header.unresolvedVirtualCallParameterTypesOffset  = 0;
    header.unresolvedVirtualCallParameterTypesSize    = 0;
    header.unresolvedVirtualCallParameterRangesOffset = 0;
    header.unresolvedVirtualCallParameterRangesSize   = 0;
    header.windowsRuntimeTypeNamesOffset  = 0;
    header.windowsRuntimeTypeNamesSize    = 0;
    header.windowsRuntimeStringsOffset    = 0;
    header.windowsRuntimeStringsSize      = 0;
    header.exportedTypeDefinitionsOffset  = 0;
    header.exportedTypeDefinitionsSize    = 0;

    header.imagesOffset = offset;
    header.imagesSize   = static_cast<int32_t>(imageDefinitions.size() * sizeof(Il2CppImageDefinition));
    header.imageDefinitionOffset = header.imagesOffset;
    header.imageDefinitionCount  = static_cast<int32_t>(imageDefinitions.size());
    offset += header.imagesSize;

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

void MetadataBuilder::WriteStringLiteralTable(std::ofstream& file)
{
    for (const auto& lit : stringLiterals)
        file.write(reinterpret_cast<const char*>(&lit), sizeof(lit));

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

