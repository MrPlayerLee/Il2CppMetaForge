// MemoryReader.cpp
#include "MemoryReader.h"
#include <iostream>
#include <fstream>

MemoryReader::MemoryReader(uintptr_t baseVA, uintptr_t dataVA, uint64_t fileOffset)
{
    Initialize(baseVA, dataVA, fileOffset);
}

uintptr_t MemoryReader::ReadPointer(std::ifstream& file, uint64_t fileOffset)
{
    file.seekg(fileOffset, std::ios::beg);
    uintptr_t value = 0;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

void MemoryReader::Initialize(uintptr_t baseVA, uintptr_t dataBaseVA, uint64_t fileOffset)
{
    baseVirtualAddress = baseVA;
    dataVirtualAddress = dataBaseVA;
    dataSectionOffset = fileOffset;
}

uintptr_t MemoryReader::RvaToFileOffset(uintptr_t rva)
{
    return rva - dataVirtualAddress + dataSectionOffset;
}

// 메타데이터 포인터 수동 설정
void MemoryReader::LoadMetadataPointers(std::ifstream& file)
{
    typeDefinitions = ReadPointer(file, RvaToFileOffset(0x18D461A90));
    methodDefinitions = ReadPointer(file, RvaToFileOffset(0x18D461A98));
    stringLiteralTable = ReadPointer(file, RvaToFileOffset(0x18D461AA0));
    stringLiteralTableCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AA8));
    typeDefinitionsCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AB0));
    methodDefinitionsCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AB8));
    fieldDefinitions = ReadPointer(file, RvaToFileOffset(0x18D461AC0));
    fieldDefinitionsCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AC8));
    propertyDefinitions = ReadPointer(file, RvaToFileOffset(0x18D461AD0));
    propertyDefinitionsCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AD8));
    metadataUsages = ReadPointer(file, RvaToFileOffset(0x18D461AE0));
    metadataUsagesCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AE8));
    imageDefinitionsCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461AF0));

    parameterDefinitions = ReadPointer(file, RvaToFileOffset(0x18D461AF8));
    parameterDefinitionsCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461B00));
    assemblyDefinitions = ReadPointer(file, RvaToFileOffset(0x18D461B08));
    assemblyDefinitionsCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461B10));

    genericContainers = ReadPointer(file, RvaToFileOffset(0x18D461B18));
    genericContainersCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461B20));
    genericParameters = ReadPointer(file, RvaToFileOffset(0x18D461B28));
    genericParametersCount = ReadStruct<uint32_t>(file, RvaToFileOffset(0x18D461B30));
}

uintptr_t MemoryReader::GetTypeDefinitions() const { return typeDefinitions; }
uintptr_t MemoryReader::GetMethodDefinitions() const { return methodDefinitions; }
uintptr_t MemoryReader::GetStringLiteralTable() const { return stringLiteralTable; }
uint32_t MemoryReader::GetStringLiteralTableCount() const { return stringLiteralTableCount; }
uintptr_t MemoryReader::GetMetadataUsages() const { return metadataUsages; }
uint32_t MemoryReader::GetMetadataUsagesCount() const { return metadataUsagesCount; }
uint32_t MemoryReader::GetImageDefinitionsCount() const { return imageDefinitionsCount; }
uintptr_t MemoryReader::GetFieldDefinitions() const { return fieldDefinitions; }
uint32_t MemoryReader::GetFieldDefinitionsCount() const { return fieldDefinitionsCount; }
uintptr_t MemoryReader::GetPropertyDefinitions() const { return propertyDefinitions; }
uint32_t MemoryReader::GetPropertyDefinitionsCount() const { return propertyDefinitionsCount; }
uintptr_t MemoryReader::GetParameterDefinitions() const { return parameterDefinitions; }
uint32_t MemoryReader::GetParameterDefinitionsCount() const { return parameterDefinitionsCount; }
uintptr_t MemoryReader::GetAssemblyDefinitions() const { return assemblyDefinitions; }
uint32_t MemoryReader::GetAssemblyDefinitionsCount() const { return assemblyDefinitionsCount; }
uintptr_t MemoryReader::GetGenericContainers() const { return genericContainers; }
uint32_t MemoryReader::GetGenericContainersCount() const { return genericContainersCount; }
uintptr_t MemoryReader::GetGenericParameters() const { return genericParameters; }
uint32_t MemoryReader::GetGenericParametersCount() const { return genericParametersCount; }
uint32_t MemoryReader::GetTypeDefinitionsCount() const { return typeDefinitionsCount; }
uint32_t MemoryReader::GetMethodDefinitionsCount() const { return methodDefinitionsCount; }
