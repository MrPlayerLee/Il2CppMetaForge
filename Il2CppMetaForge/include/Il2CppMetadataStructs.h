// ✅ Il2CppMetadataStructs.h (DEBUG02)
#pragma once

#include <cstdint>

struct Il2CppTypeDefinition
{
    uint32_t nameIndex;
    uint32_t namespaceIndex;
    uint32_t byvalTypeIndex;
    uint32_t byrefTypeIndex;
    uint32_t declaringTypeIndex;
    uint32_t parentIndex;
    int32_t elementTypeIndex;
    int32_t rgctxStartIndex;
    int32_t rgctxCount;
    uint32_t flags;
    uint32_t fieldStart;
    uint32_t methodStart;
    uint32_t eventStart;
    uint32_t propertyStart;
    uint32_t nestedTypesStart;
    uint32_t interfacesStart;
    uint32_t interfaceOffsetsStart;
    int32_t interfaceCount;
    int32_t interfaceOffsetCount;
    uint32_t bitfield;
    uint32_t token;
};

struct Il2CppGlobalMetadataHeader {
    uint32_t sanity;
    int32_t version;

    uint32_t stringLiteralOffset;
    uint32_t stringLiteralCount;

    uint32_t stringLiteralDataOffset;
    uint32_t stringLiteralDataCount;

    uint32_t stringOffset;
    uint32_t stringCount;

    uint32_t methodDefinitionOffset;
    uint32_t methodDefinitionCount;

    uint32_t typeDefinitionOffset;
    uint32_t typeDefinitionCount;

    uint32_t fieldDefinitionOffset;
    uint32_t fieldDefinitionCount;

    uint32_t propertyDefinitionOffset;
    uint32_t propertyDefinitionCount;

    uint32_t metadataUsageOffset;
    uint32_t metadataUsageCount;

    uint32_t imageDefinitionOffset;
    uint32_t imageDefinitionCount;

    uint32_t parameterDefinitionOffset;
    uint32_t parameterDefinitionCount;

    uint32_t assemblyDefinitionOffset;
    uint32_t assemblyDefinitionCount;

    // ✅ Generic Container
    uint32_t genericContainerOffset;
    uint32_t genericContainerCount;

    uint32_t genericParameterOffset;
    uint32_t genericParameterCount;
};

// ✅ 기타 구조체 (단순 정의)
struct Il2CppStringLiteral { uint32_t length; uint32_t dataIndex; };
struct Il2CppMethodDefinition { uint32_t nameIndex; uint32_t typeIndex; };
struct Il2CppFieldDefinition { uint32_t nameIndex; uint32_t typeIndex; };
struct Il2CppPropertyDefinition { uint32_t nameIndex; uint32_t typeIndex; };
struct Il2CppMetadataUsage { uint32_t destIndex; uint32_t encodedSourceIndex; };
struct Il2CppImageDefinition { uint32_t nameIndex; uint32_t typeStart; uint32_t typeCount; };
struct Il2CppParameterDefinition { uint32_t nameIndex; uint32_t typeIndex; };
struct Il2CppAssemblyDefinition { uint32_t nameIndex; uint32_t imageIndex; };

struct Il2CppGenericContainer {
    int32_t ownerIndex;
    int32_t type_argc;
    int32_t is_method;
    int32_t genericParameterStart;
};

struct Il2CppGenericParameter {
    int32_t ownerIndex;
    int32_t nameIndex;
    int32_t constraintsStart;
    int16_t numConstraints;
    uint16_t flags;
};
