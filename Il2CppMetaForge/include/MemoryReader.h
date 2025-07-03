#pragma once

#include <cstdint>
#include <fstream>
#include <vector>

class MemoryReader {
public:
    MemoryReader(uintptr_t baseVA = 0, uintptr_t dataVA = 0, uint64_t fileOffset = 0);

    void Initialize(uintptr_t baseVA, uintptr_t dataBaseVA, uint64_t fileOffset);
    uintptr_t RvaToFileOffset(uintptr_t rva);

    void LoadMetadataPointers(std::ifstream& file);

    uintptr_t GetTypeDefinitions() const;
    uintptr_t GetMethodDefinitions() const;
    uintptr_t GetStringLiteralTable() const;
    uint32_t GetStringLiteralTableCount() const;
    uintptr_t GetMetadataUsages() const;
    uint32_t GetMetadataUsagesCount() const;
    uint32_t GetImageDefinitionsCount() const;
    uintptr_t GetFieldDefinitions() const;
    uint32_t GetFieldDefinitionsCount() const;
    uintptr_t GetPropertyDefinitions() const;
    uint32_t GetPropertyDefinitionsCount() const;

    uintptr_t GetParameterDefinitions() const;
    uint32_t GetParameterDefinitionsCount() const;
    uintptr_t GetAssemblyDefinitions() const;
    uint32_t GetAssemblyDefinitionsCount() const;

    uint32_t GetTypeDefinitionsCount() const;
    uint32_t GetMethodDefinitionsCount() const;

    uintptr_t ReadPointer(std::ifstream& file, uint64_t fileOffset);
    template <typename T>
    T ReadStruct(std::ifstream& file, uint64_t fileOffset);

    template <typename T>
    std::vector<T> ReadStructArray(std::ifstream& file, uint64_t fileOffset, size_t count);

    uint32_t ReadUInt32(std::ifstream& file, uintptr_t rva);

private:
    uintptr_t baseVirtualAddress{0};
    uintptr_t dataVirtualAddress{0};
    uint64_t dataSectionOffset{0};

    uintptr_t typeDefinitions{0};
    uintptr_t methodDefinitions{0};
    uintptr_t stringLiteralTable{0};
    uint32_t stringLiteralTableCount{0};
    uintptr_t metadataUsages{0};
    uint32_t metadataUsagesCount{0};
    uint32_t imageDefinitionsCount{0};
    uint32_t typeDefinitionsCount{0};
    uint32_t methodDefinitionsCount{0};

    // 필드와 프로퍼티 정의 데이터 포인터와 개수
    uintptr_t fieldDefinitions{0};
    uint32_t fieldDefinitionsCount{0};
    uintptr_t propertyDefinitions{0};
    uint32_t propertyDefinitionsCount{0};

    // 파라미터와 어셈블리 정의 포인터 및 개수
    uintptr_t parameterDefinitions{0};
    uint32_t parameterDefinitionsCount{0};
    uintptr_t assemblyDefinitions{0};
    uint32_t assemblyDefinitionsCount{0};
};

template <typename T>
T MemoryReader::ReadStruct(std::ifstream& file, uint64_t fileOffset)
{
    T value{};
    file.seekg(fileOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(&value), sizeof(T));
    return value;
}

template <typename T>
std::vector<T> MemoryReader::ReadStructArray(std::ifstream& file, uint64_t fileOffset, size_t count)
{
    std::vector<T> values(count);
    file.seekg(fileOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(values.data()), sizeof(T) * count);
    return values;
}

inline uint32_t MemoryReader::ReadUInt32(std::ifstream& file, uintptr_t rva)
{
    return ReadStruct<uint32_t>(file, RvaToFileOffset(rva));
}

