// MemoryReader.cpp
#include "MemoryReader.h"
#include <windows.h>
#include <iostream>
#include <fstream>

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

// ���� �ּ� ���� ����
void MemoryReader::LoadMetadataPointers(std::ifstream& file)
{
    typeDefinitions = ReadPointer(file, RvaToFileOffset(0x18D461A90));
    methodDefinitions = ReadPointer(file, RvaToFileOffset(0x18D461A98));
    stringLiteralTable = ReadPointer(file, RvaToFileOffset(0x18D461AA0));
    metadataUsages = ReadPointer(file, RvaToFileOffset(0x18D461AC8));
    metadataUsagesCount = ReadPointer(file, RvaToFileOffset(0x18D461AD8));
    imageDefinitionsCount = ReadPointer(file, RvaToFileOffset(0x18D461AC0));
}

uintptr_t MemoryReader::GetTypeDefinitions() const { return typeDefinitions; }
uintptr_t MemoryReader::GetMethodDefinitions() const { return methodDefinitions; }
uintptr_t MemoryReader::GetStringLiteralTable() const { return stringLiteralTable; }
uintptr_t MemoryReader::GetMetadataUsages() const { return metadataUsages; }
uintptr_t MemoryReader::GetMetadataUsagesCount() const { return metadataUsagesCount; }
uintptr_t MemoryReader::GetImageDefinitionsCount() const { return imageDefinitionsCount; }
