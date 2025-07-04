// ✅ DEBUG04 MemoryReader.cpp - 누락 구현 보완
#include "MemoryReader.h"

MemoryReader::MemoryReader(uintptr_t baseRVA, uintptr_t dataRVA, uint64_t fileOffset)
    : baseVirtualAddress(baseRVA), dataVirtualAddress(dataRVA), dataSectionOffset(fileOffset) {
}

void MemoryReader::Initialize(uintptr_t baseVA, uintptr_t dataVA, uint64_t fileOffset)
{
    baseVirtualAddress = baseVA;
    dataVirtualAddress = dataVA;
    dataSectionOffset = fileOffset;
}

uintptr_t MemoryReader::RvaToFileOffset(uintptr_t rva) const
{
    return rva - dataVirtualAddress + dataSectionOffset;
}

uintptr_t MemoryReader::ReadPointer(std::ifstream& file, uintptr_t rva)
{
    uintptr_t result{};
    file.seekg(RvaToFileOffset(rva), std::ios::beg);
    file.read(reinterpret_cast<char*>(&result), sizeof(result));
    return result;
}

// Getter implementations
uintptr_t MemoryReader::GetTypeDefinitions() const { return typeDefinitions; }
uint32_t MemoryReader::GetTypeDefinitionsCount() const { return typeDefinitionsCount; }
uintptr_t MemoryReader::GetMethodDefinitions() const { return methodDefinitions; }
uint32_t MemoryReader::GetMethodDefinitionsCount() const { return methodDefinitionsCount; }
uintptr_t MemoryReader::GetFieldDefinitions() const { return fieldDefinitions; }
uint32_t MemoryReader::GetFieldDefinitionsCount() const { return fieldDefinitionsCount; }
uintptr_t MemoryReader::GetPropertyDefinitions() const { return propertyDefinitions; }
uint32_t MemoryReader::GetPropertyDefinitionsCount() const { return propertyDefinitionsCount; }
uintptr_t MemoryReader::GetParameterDefinitions() const { return parameterDefinitions; }
uint32_t MemoryReader::GetParameterDefinitionsCount() const { return parameterDefinitionsCount; }
uintptr_t MemoryReader::GetAssemblyDefinitions() const { return assemblyDefinitions; }
uint32_t MemoryReader::GetAssemblyDefinitionsCount() const { return assemblyDefinitionsCount; }
uintptr_t MemoryReader::GetStringLiteralTable() const { return stringLiteralTable; }
uint32_t MemoryReader::GetStringLiteralTableCount() const { return stringLiteralTableCount; }
uintptr_t MemoryReader::GetMetadataUsages() const { return metadataUsages; }
uint32_t MemoryReader::GetMetadataUsagesCount() const { return metadataUsagesCount; }

std::vector<Il2CppGenericContainer> MemoryReader::ReadGenericContainers(std::ifstream& file)
{
    return ReadStructArray<Il2CppGenericContainer>(file, RvaToFileOffset(genericContainers), genericContainerCount);
}

std::vector<Il2CppGenericParameter> MemoryReader::ReadGenericParameters(std::ifstream& file)
{
    return ReadStructArray<Il2CppGenericParameter>(file, RvaToFileOffset(genericParameters), genericParameterCount);
}

uint32_t MemoryReader::ReadUInt32(std::ifstream& file, uintptr_t rva)
{
    return ReadStruct<uint32_t>(file, RvaToFileOffset(rva));
}
