#pragma once

#include "Il2CppMetadataStructs.h"
#include <string>
#include <vector>
#include <fstream>

class MetadataBuilder {
public:
    explicit MetadataBuilder(const std::string& outputPath);

    void SetTypeDefinitions(const std::vector<Il2CppTypeDefinition>& defs);
    void SetMethodDefinitions(const std::vector<Il2CppMethodDefinition>& defs);
    void SetStringLiterals(const std::vector<Il2CppStringLiteral>& literals,
                           const std::vector<char>& stringData);
    void SetStrings(const std::vector<char>& strings);
    void SetMetadataUsages(const std::vector<Il2CppMetadataUsage>& usages);
    void SetImageDefinitions(const std::vector<Il2CppImageDefinition>& images);

    void Build();

private:
    void WriteMetadataHeader(std::ofstream& file);
    void WriteTypeDefinitions(std::ofstream& file);
    void WriteMethodDefinitions(std::ofstream& file);
    void WriteStringLiteralTable(std::ofstream& file);
    void WriteStringTable(std::ofstream& file);
    void WriteMetadataUsages(std::ofstream& file);
    void WriteImageDefinitions(std::ofstream& file);

    std::string outputPath;
    std::vector<Il2CppTypeDefinition> typeDefinitions;
    std::vector<Il2CppMethodDefinition> methodDefinitions;
    std::vector<Il2CppStringLiteral> stringLiterals;
    std::vector<char> stringLiteralData;
    std::vector<char> strings;
    std::vector<Il2CppMetadataUsage> metadataUsages;
    std::vector<Il2CppImageDefinition> imageDefinitions;
};

