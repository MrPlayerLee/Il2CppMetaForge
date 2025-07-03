#pragma once

#include <cstdint>
#include <vector>
#include <string>

// ±âº» Il2Cpp ±¸Á¶Ã¼ Á¤ÀÇ

struct Il2CppTypeDefinition
{
    uint32_t nameIndex;
    uint32_t namespaceIndex;
    uint32_t customAttributeIndex;
    uint32_t byvalTypeIndex;
    uint32_t byrefTypeIndex;
    uint32_t declaringTypeIndex;
    uint32_t parentIndex;
    uint32_t elementTypeIndex;
    uint32_t rgctxStartIndex;
    uint32_t rgctxCount;
    uint32_t genericContainerIndex;
    uint32_t flags;
    uint32_t fieldStart;
    uint32_t methodStart;
    uint32_t eventStart;
    uint32_t propertyStart;
    uint32_t nestedTypesStart;
    uint32_t interfacesStart;
    uint32_t interfaceOffsetsStart;
    uint32_t method_count;
    uint32_t property_count;
    uint32_t field_count;
    uint32_t event_count;
};

struct Il2CppMethodDefinition
{
    uint32_t nameIndex;
    uint32_t declaringType;
    uint32_t returnType;
    uint32_t parameterStart;
    int32_t  genericContainerIndex;
    uint32_t customAttributeIndex;
    uint32_t token;
    uint16_t flags;
    uint16_t iflags;
    uint16_t slot;
    uint16_t parameterCount;
};

struct Il2CppFieldDefinition
{
    uint32_t nameIndex;
    uint32_t typeIndex;
    uint32_t customAttributeIndex;
    uint32_t token;
};

struct Il2CppPropertyDefinition
{
    uint32_t nameIndex;
    uint32_t getter;
    uint32_t setter;
    uint32_t customAttributeIndex;
    uint32_t token;
};

struct Il2CppStringLiteral
{
    uint32_t length;
    uint32_t dataIndex;
};

struct Il2CppGlobalMetadataHeader
{
    uint32_t sanity;
    int32_t  version;

    uint32_t stringLiteralOffset;
    int32_t  stringLiteralSize;
    uint32_t stringLiteralDataOffset;
    int32_t  stringLiteralDataSize;

    uint32_t stringOffset;
    int32_t  stringSize;

    uint32_t eventsOffset;
    int32_t  eventsSize;
    uint32_t propertiesOffset;
    int32_t  propertiesSize;
    uint32_t methodsOffset;
    int32_t  methodsSize;

    uint32_t parameterDefaultValuesOffset;
    int32_t  parameterDefaultValuesSize;
    uint32_t fieldDefaultValuesOffset;
    int32_t  fieldDefaultValuesSize;
    uint32_t fieldAndParameterDefaultValueDataOffset;
    int32_t  fieldAndParameterDefaultValueDataSize;
    int32_t  fieldMarshaledSizesOffset;
    int32_t  fieldMarshaledSizesSize;

    uint32_t parametersOffset;
    int32_t  parametersSize;
    uint32_t fieldsOffset;
    int32_t  fieldsSize;
    uint32_t genericParametersOffset;
    int32_t  genericParametersSize;
    uint32_t genericParameterConstraintsOffset;
    int32_t  genericParameterConstraintsSize;
    uint32_t genericContainersOffset;
    int32_t  genericContainersSize;
    uint32_t nestedTypesOffset;
    int32_t  nestedTypesSize;
    uint32_t interfacesOffset;
    int32_t  interfacesSize;
    uint32_t vtableMethodsOffset;
    int32_t  vtableMethodsSize;
    int32_t  interfaceOffsetsOffset;
    int32_t  interfaceOffsetsSize;
    uint32_t typeDefinitionsOffset;
    int32_t  typeDefinitionsSize;
    uint32_t rgctxEntriesOffset;
    int32_t  rgctxEntriesCount;
    uint32_t imagesOffset;
    int32_t  imagesSize;
    uint32_t imageDefinitionOffset;
    int32_t  imageDefinitionCount;
    uint32_t assembliesOffset;
    int32_t  assembliesSize;
    uint32_t metadataUsageListsOffset;
    int32_t  metadataUsageListsCount;
    uint32_t metadataUsagePairsOffset;
    int32_t  metadataUsagePairsCount;
    uint32_t metadataUsageOffset;
    int32_t  metadataUsageCount;
    uint32_t fieldRefsOffset;
    int32_t  fieldRefsSize;
    int32_t  referencedAssembliesOffset;
    int32_t  referencedAssembliesSize;
    uint32_t attributesInfoOffset;
    int32_t  attributesInfoCount;
    uint32_t attributeTypesOffset;
    int32_t  attributeTypesCount;
    uint32_t attributeDataOffset;
    int32_t  attributeDataSize;
    uint32_t attributeDataRangeOffset;
    int32_t  attributeDataRangeSize;
    int32_t  unresolvedVirtualCallParameterTypesOffset;
    int32_t  unresolvedVirtualCallParameterTypesSize;
    int32_t  unresolvedVirtualCallParameterRangesOffset;
    int32_t  unresolvedVirtualCallParameterRangesSize;
    int32_t  windowsRuntimeTypeNamesOffset;
    int32_t  windowsRuntimeTypeNamesSize;
    int32_t  windowsRuntimeStringsOffset;
    int32_t  windowsRuntimeStringsSize;
    int32_t  exportedTypeDefinitionsOffset;
    int32_t  exportedTypeDefinitionsSize;
};

struct Il2CppMetadataUsage
{
    uint32_t destinationIndex;
    uint32_t encodedSourceIndex;
};

struct Il2CppImageDefinition
{
    uint32_t nameIndex;
    uint32_t assemblyIndex;
    uint32_t typeStart;
    uint32_t typeCount;
    uint32_t entryPointIndex;
    uint32_t token;
};
