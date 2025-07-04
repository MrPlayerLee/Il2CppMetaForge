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

void MemoryReader::LoadMetadataPointers(std::ifstream& file)
{
    // 실제 메타데이터 파싱 로직이 없으므로 벡터를 초기화만 수행한다.
    typeDefinitionList.clear();
    methodDefinitionList.clear();
    fieldDefinitionList.clear();
    propertyDefinitionList.clear();
    parameterDefinitionList.clear();
    assemblyDefinitionList.clear();
    imageDefinitionList.clear();
    metadataUsageList.clear();
    stringLiteralList.clear();
    stringLiteralDataList.clear();
    stringTableList.clear();
    genericContainerList.clear();
    genericParameterList.clear();
}

// Getter implementations
const std::vector<Il2CppTypeDefinition>& MemoryReader::GetTypeDefinitions() const { return typeDefinitionList; }
const std::vector<Il2CppMethodDefinition>& MemoryReader::GetMethodDefinitions() const { return methodDefinitionList; }
const std::vector<Il2CppFieldDefinition>& MemoryReader::GetFieldDefinitions() const { return fieldDefinitionList; }
const std::vector<Il2CppPropertyDefinition>& MemoryReader::GetPropertyDefinitions() const { return propertyDefinitionList; }
const std::vector<Il2CppParameterDefinition>& MemoryReader::GetParameterDefinitions() const { return parameterDefinitionList; }
const std::vector<Il2CppAssemblyDefinition>& MemoryReader::GetAssemblyDefinitions() const { return assemblyDefinitionList; }
const std::vector<Il2CppImageDefinition>& MemoryReader::GetImageDefinitions() const { return imageDefinitionList; }
const std::vector<Il2CppMetadataUsage>& MemoryReader::GetMetadataUsages() const { return metadataUsageList; }
const std::vector<Il2CppStringLiteral>& MemoryReader::GetStringLiterals() const { return stringLiteralList; }
const std::vector<char>& MemoryReader::GetStringLiteralData() const { return stringLiteralDataList; }
const std::vector<char>& MemoryReader::GetStringTable() const { return stringTableList; }
const std::vector<Il2CppGenericContainer>& MemoryReader::GetGenericContainers() const { return genericContainerList; }
const std::vector<Il2CppGenericParameter>& MemoryReader::GetGenericParameters() const { return genericParameterList; }

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
