#include "Il2CppMetadataStructs.h"
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>

class MetadataBuilder {
public:
    MetadataBuilder(const std::string& outputPath)
        : outputPath(outputPath) {
    }

    void setTypeDefinitions(const std::vector<Il2CppTypeDefinition>& defs) {
        typeDefinitions = defs;
    }

    void setMethodDefinitions(const std::vector<Il2CppMethodDefinition>& defs) {
        methodDefinitions = defs;
    }

    void setStringLiterals(const std::vector<Il2CppStringLiteral>& literals, const std::vector<char>& stringData) {
        stringLiterals = literals;
        stringLiteralData = stringData;
    }

    void setMetadataUsages(const std::vector<Il2CppMetadataUsage>& usages) {
        metadataUsages = usages;
    }

    void build() {
        std::ofstream file(outputPath, std::ios::binary);
        if (!file) return;

        uint32_t offset = 0;

        // Write type definitions
        for (const auto& def : typeDefinitions) {
            file.write(reinterpret_cast<const char*>(&def), sizeof(def));
        }
        offset += static_cast<uint32_t>(typeDefinitions.size() * sizeof(Il2CppTypeDefinition));

        // Write method definitions
        for (const auto& def : methodDefinitions) {
            file.write(reinterpret_cast<const char*>(&def), sizeof(def));
        }
        offset += static_cast<uint32_t>(methodDefinitions.size() * sizeof(Il2CppMethodDefinition));

        // Write string literals metadata
        for (const auto& lit : stringLiterals) {
            file.write(reinterpret_cast<const char*>(&lit), sizeof(lit));
        }
        offset += static_cast<uint32_t>(stringLiterals.size() * sizeof(Il2CppStringLiteral));

        // Write actual string data
        file.write(stringLiteralData.data(), stringLiteralData.size());
        offset += static_cast<uint32_t>(stringLiteralData.size());

        // Write metadata usages
        for (const auto& usage : metadataUsages) {
            file.write(reinterpret_cast<const char*>(&usage), sizeof(usage));
        }
        offset += static_cast<uint32_t>(metadataUsages.size() * sizeof(Il2CppMetadataUsage));

        file.close();
    }

private:
    std::string outputPath;
    std::vector<Il2CppTypeDefinition> typeDefinitions;
    std::vector<Il2CppMethodDefinition> methodDefinitions;
    std::vector<Il2CppStringLiteral> stringLiterals;
    std::vector<char> stringLiteralData;
    std::vector<Il2CppMetadataUsage> metadataUsages;
};
