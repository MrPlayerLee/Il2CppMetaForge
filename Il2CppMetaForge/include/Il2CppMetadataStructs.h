#pragma once

#include <cstdint>
#include <vector>
#include <string>

// 기본 Il2Cpp 구조체 정의

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
    uint32_t stringLiteralCount;

    uint32_t stringLiteralDataOffset;
    uint32_t stringLiteralDataCount;

    uint32_t stringOffset;
    uint32_t stringCount;

    uint32_t methodDefinitionOffset;
    uint32_t methodDefinitionCount;

    uint32_t fieldDefinitionOffset;
    uint32_t fieldDefinitionCount;

    uint32_t propertyDefinitionOffset;
    uint32_t propertyDefinitionCount;

    uint32_t typeDefinitionOffset;
    uint32_t typeDefinitionCount;

    uint32_t imageDefinitionOffset;
    uint32_t imageDefinitionCount;
    // reserved
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
