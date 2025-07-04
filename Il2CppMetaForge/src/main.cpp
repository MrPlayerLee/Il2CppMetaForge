// Fix_main.cpp
#include <iostream>
#include <fstream>
#include "MemoryReader.h"
#include "MetadataBuilder.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: Il2CppMetaForge <configFile> <GameAssembly.dll>" << std::endl;
        return 1;
    }

    const char* configFile = argv[1];
    const char* dllFile = argv[2];

    uintptr_t imageBase = 0;
    uintptr_t dataVA = 0;
    uint64_t dataOffset = 0;

    std::ifstream config(configFile);
    if (!config.is_open()) {
        std::cerr << "Failed to open config file." << std::endl;
        return 1;
    }
    config >> std::hex >> imageBase >> dataVA >> dataOffset;
    config.close();

    std::ifstream file(dllFile, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open GameAssembly.dll" << std::endl;
        return 1;
    }

    MemoryReader reader;
    reader.Initialize(imageBase, dataVA, dataOffset);
    reader.LoadMetadataPointers(file);

    MetadataBuilder builder("global-metadata.dat");
    builder.SetTypeDefinitions(reader.GetTypeDefinitions());
    builder.SetMethodDefinitions(reader.GetMethodDefinitions());
    builder.SetFieldDefinitions(reader.GetFieldDefinitions());
    builder.SetPropertyDefinitions(reader.GetPropertyDefinitions());
    builder.SetParameterDefinitions(reader.GetParameterDefinitions());
    builder.SetAssemblyDefinitions(reader.GetAssemblyDefinitions());
    builder.SetImageDefinitions(reader.GetImageDefinitions());
    builder.SetMetadataUsages(reader.GetMetadataUsages());
    builder.SetStringLiterals(reader.GetStringLiterals(), reader.GetStringLiteralData());
    builder.SetStrings(reader.GetStringTable());
    builder.SetGenericContainers(reader.GetGenericContainers());
    builder.SetGenericParameters(reader.GetGenericParameters());
    builder.Build();

    std::cout << "global-metadata.dat generated successfully." << std::endl;
    return 0;
}
