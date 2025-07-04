// Fix_MetadataBuilder.h
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include "Il2CppMetadataStructs.h"

class MetadataBuilder {
public:
    explicit MetadataBuilder(const std::string& outputPath);

    void SetTypeDefinitions(const std::vector<Il2CppTypeDefinition>& types);
    void SetMethodDefinitions(const std::vector<Il2CppMethodDefinition>& methods);
    void SetFieldDefinitions(const std::vector<Il2CppFieldDefinition>& fields);
    void SetPropertyDefinitions(const std::vector<Il2CppPropertyDefinition>& properties);
    void SetParameterDefinitions(const std::vector<Il2CppParameterDefinition>& parameters);
    void SetAssemblyDefinitions(const std::vector<Il2CppAssemblyDefinition>& assemblies);
    void SetImageDefinitions(const std::vector<Il2CppImageDefinition>& images);
    void SetMetadataUsages(const std::vector<Il2CppMetadataUsage>& usages);
    void SetStringLiterals(const std::vector<Il2CppStringLiteral>& literals, const std::vector<char>& data);
    void SetStrings(const std::vector<char>& strings);
    void SetGenericContainers(const std::vector<Il2CppGenericContainer>& containers);
    void SetGenericParameters(const std::vector<Il2CppGenericParameter>& parameters);

    void Build();

private:
    void WriteMetadataHeader(std::ofstream& output);
    void WriteTypeDefinitions(std::ofstream& output);
    void WriteMethodDefinitions(std::ofstream& output);
    void WriteFieldDefinitions(std::ofstream& output);
    void WritePropertyDefinitions(std::ofstream& output);
    void WriteParameterDefinitions(std::ofstream& output);
    void WriteAssemblyDefinitions(std::ofstream& output);
    void WriteImageDefinitions(std::ofstream& output);
    void WriteMetadataUsages(std::ofstream& output);
    void WriteStringLiteralTable(std::ofstream& output);
    void WriteStringLiteralData(std::ofstream& output);
    void WriteStringTable(std::ofstream& output);

    std::string outputPath;

    std::vector<Il2CppTypeDefinition> typeDefinitions;
    std::vector<Il2CppMethodDefinition> methodDefinitions;
    std::vector<Il2CppFieldDefinition> fieldDefinitions;
    std::vector<Il2CppPropertyDefinition> propertyDefinitions;
    std::vector<Il2CppParameterDefinition> parameterDefinitions;
    std::vector<Il2CppAssemblyDefinition> assemblyDefinitions;
    std::vector<Il2CppImageDefinition> imageDefinitions;
    std::vector<Il2CppMetadataUsage> metadataUsages;
    std::vector<Il2CppStringLiteral> stringLiterals;
    std::vector<char> stringLiteralData;
    std::vector<char> strings;
    std::vector<Il2CppGenericContainer> genericContainers;
    std::vector<Il2CppGenericParameter> genericParameters;
};
