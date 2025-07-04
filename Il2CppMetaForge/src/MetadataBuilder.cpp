// Fix_MetadataBuilder.cpp
#include "MetadataBuilder.h"
#include <cstring>

MetadataBuilder::MetadataBuilder(const std::string& outputPath) : outputPath(outputPath) {}

void MetadataBuilder::SetTypeDefinitions(const std::vector<Il2CppTypeDefinition>& types) {
    typeDefinitions = types;
}

void MetadataBuilder::SetMethodDefinitions(const std::vector<Il2CppMethodDefinition>& methods) {
    methodDefinitions = methods;
}

void MetadataBuilder::SetFieldDefinitions(const std::vector<Il2CppFieldDefinition>& fields) {
    fieldDefinitions = fields;
}

void MetadataBuilder::SetPropertyDefinitions(const std::vector<Il2CppPropertyDefinition>& properties) {
    propertyDefinitions = properties;
}

void MetadataBuilder::SetParameterDefinitions(const std::vector<Il2CppParameterDefinition>& parameters) {
    parameterDefinitions = parameters;
}

void MetadataBuilder::SetAssemblyDefinitions(const std::vector<Il2CppAssemblyDefinition>& assemblies) {
    assemblyDefinitions = assemblies;
}

void MetadataBuilder::SetImageDefinitions(const std::vector<Il2CppImageDefinition>& images) {
    imageDefinitions = images;
}

void MetadataBuilder::SetMetadataUsages(const std::vector<Il2CppMetadataUsage>& usages) {
    metadataUsages = usages;
}

void MetadataBuilder::SetStringLiterals(const std::vector<Il2CppStringLiteral>& literals, const std::vector<char>& data) {
    stringLiterals = literals;
    stringLiteralData = data;
}

void MetadataBuilder::SetStrings(const std::vector<char>& stringsInput) {
    strings = stringsInput;
}

void MetadataBuilder::SetGenericContainers(const std::vector<Il2CppGenericContainer>& containers) {
    genericContainers = containers;
}

void MetadataBuilder::SetGenericParameters(const std::vector<Il2CppGenericParameter>& parameters) {
    genericParameters = parameters;
}

void MetadataBuilder::Build() {
    std::ofstream output(outputPath, std::ios::binary);
    if (!output.is_open()) return;

    WriteMetadataHeader(output);
    WriteTypeDefinitions(output);
    WriteMethodDefinitions(output);
    WriteFieldDefinitions(output);
    WritePropertyDefinitions(output);
    WriteParameterDefinitions(output);
    WriteAssemblyDefinitions(output);
    WriteImageDefinitions(output);
    WriteMetadataUsages(output);
    WriteStringLiteralTable(output);
    WriteStringLiteralData(output);
    WriteStringTable(output);

    output.close();
}

void MetadataBuilder::WriteMetadataHeader(std::ofstream& output) {
    // 구현 생략 가능
}

void MetadataBuilder::WriteTypeDefinitions(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(typeDefinitions.data()), typeDefinitions.size() * sizeof(Il2CppTypeDefinition));
}

void MetadataBuilder::WriteMethodDefinitions(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(methodDefinitions.data()), methodDefinitions.size() * sizeof(Il2CppMethodDefinition));
}

void MetadataBuilder::WriteFieldDefinitions(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(fieldDefinitions.data()), fieldDefinitions.size() * sizeof(Il2CppFieldDefinition));
}

void MetadataBuilder::WritePropertyDefinitions(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(propertyDefinitions.data()), propertyDefinitions.size() * sizeof(Il2CppPropertyDefinition));
}

void MetadataBuilder::WriteParameterDefinitions(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(parameterDefinitions.data()), parameterDefinitions.size() * sizeof(Il2CppParameterDefinition));
}

void MetadataBuilder::WriteAssemblyDefinitions(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(assemblyDefinitions.data()), assemblyDefinitions.size() * sizeof(Il2CppAssemblyDefinition));
}

void MetadataBuilder::WriteImageDefinitions(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(imageDefinitions.data()), imageDefinitions.size() * sizeof(Il2CppImageDefinition));
}

void MetadataBuilder::WriteMetadataUsages(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(metadataUsages.data()), metadataUsages.size() * sizeof(Il2CppMetadataUsage));
}

void MetadataBuilder::WriteStringLiteralTable(std::ofstream& output) {
    output.write(reinterpret_cast<const char*>(stringLiterals.data()), stringLiterals.size() * sizeof(Il2CppStringLiteral));
}

void MetadataBuilder::WriteStringLiteralData(std::ofstream& output) {
    output.write(stringLiteralData.data(), stringLiteralData.size());
}

void MetadataBuilder::WriteStringTable(std::ofstream& output) {
    output.write(strings.data(), strings.size());
}
