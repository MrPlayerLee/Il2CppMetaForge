// ✅ DEBUG04 MemoryReader.h - 완전 보완된 선언부
#pragma once

#include <cstdint>
#include <fstream>
#include <vector>
#include <string>
#include "Il2CppMetadataStructs.h"

class MemoryReader {
public:
    MemoryReader(uintptr_t baseRVA = 0, uintptr_t dataRVA = 0, uint64_t fileOffset = 0);

    void Initialize(uintptr_t baseVA, uintptr_t dataBaseVA, uint64_t fileOffset);
    uintptr_t RvaToFileOffset(uintptr_t rva) const;
    uintptr_t ReadPointer(std::ifstream& file, uintptr_t rva);

    void LoadMetadataPointers(std::ifstream& file);

    // 메타데이터 테이블 반환
    const std::vector<Il2CppTypeDefinition>& GetTypeDefinitions() const;
    const std::vector<Il2CppMethodDefinition>& GetMethodDefinitions() const;
    const std::vector<Il2CppFieldDefinition>& GetFieldDefinitions() const;
    const std::vector<Il2CppPropertyDefinition>& GetPropertyDefinitions() const;
    const std::vector<Il2CppParameterDefinition>& GetParameterDefinitions() const;
    const std::vector<Il2CppAssemblyDefinition>& GetAssemblyDefinitions() const;
    const std::vector<Il2CppImageDefinition>& GetImageDefinitions() const;
    const std::vector<Il2CppMetadataUsage>& GetMetadataUsages() const;
    const std::vector<Il2CppStringLiteral>& GetStringLiterals() const;
    const std::vector<char>& GetStringLiteralData() const;
    const std::vector<char>& GetStringTable() const;
    const std::vector<Il2CppGenericContainer>& GetGenericContainers() const;
    const std::vector<Il2CppGenericParameter>& GetGenericParameters() const;

    std::vector<Il2CppGenericContainer> ReadGenericContainers(std::ifstream& file);
    std::vector<Il2CppGenericParameter> ReadGenericParameters(std::ifstream& file);

    template <typename T>
    T ReadStruct(std::ifstream& file, uint64_t fileOffset)
    {
        T value{};
        file.seekg(fileOffset, std::ios::beg);
        file.read(reinterpret_cast<char*>(&value), sizeof(T));
        return value;
    }

    template <typename T>
    std::vector<T> ReadStructArray(std::ifstream& file, uint64_t fileOffset, size_t count)
    {
        std::vector<T> values(count);
        file.seekg(fileOffset, std::ios::beg);
        file.read(reinterpret_cast<char*>(values.data()), sizeof(T) * count);
        return values;
    }

    uint32_t ReadUInt32(std::ifstream& file, uintptr_t rva);

private:
    uintptr_t baseVirtualAddress{ 0 };
    uintptr_t dataVirtualAddress{ 0 };
    uint64_t dataSectionOffset{ 0 };

    uintptr_t typeDefinitions{ 0 };
    uint32_t typeDefinitionsCount{ 0 };
    uintptr_t methodDefinitions{ 0 };
    uint32_t methodDefinitionsCount{ 0 };
    uintptr_t fieldDefinitions{ 0 };
    uint32_t fieldDefinitionsCount{ 0 };
    uintptr_t propertyDefinitions{ 0 };
    uint32_t propertyDefinitionsCount{ 0 };
    uintptr_t parameterDefinitions{ 0 };
    uint32_t parameterDefinitionsCount{ 0 };
    uintptr_t assemblyDefinitions{ 0 };
    uint32_t assemblyDefinitionsCount{ 0 };
    uintptr_t stringLiteralTable{ 0 };
    uint32_t stringLiteralTableCount{ 0 };
    uintptr_t metadataUsages{ 0 };
    uint32_t metadataUsagesCount{ 0 };
    uint32_t imageDefinitionsCount{ 0 };

    uintptr_t genericContainers{ 0 };
    uint32_t genericContainerCount{ 0 };
    uintptr_t genericParameters{ 0 };
    uint32_t genericParameterCount{ 0 };

    // 실제 구조체 데이터를 보관할 벡터들
    std::vector<Il2CppTypeDefinition> typeDefinitionList;
    std::vector<Il2CppMethodDefinition> methodDefinitionList;
    std::vector<Il2CppFieldDefinition> fieldDefinitionList;
    std::vector<Il2CppPropertyDefinition> propertyDefinitionList;
    std::vector<Il2CppParameterDefinition> parameterDefinitionList;
    std::vector<Il2CppAssemblyDefinition> assemblyDefinitionList;
    std::vector<Il2CppImageDefinition> imageDefinitionList;
    std::vector<Il2CppMetadataUsage> metadataUsageList;
    std::vector<Il2CppStringLiteral> stringLiteralList;
    std::vector<char> stringLiteralDataList;
    std::vector<char> stringTableList;
    std::vector<Il2CppGenericContainer> genericContainerList;
    std::vector<Il2CppGenericParameter> genericParameterList;
};