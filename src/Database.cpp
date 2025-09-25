#include <iostream>

#include "Database.h"

void Database::generateInserts(std::map<std::string, std::string> config) {
    Database::generateInserts(config, 0, "GENERAL");
}

void Database::generateInserts(std::map<std::string, std::string> config, int startIndex, std::string type) {
    std::cout << "insert into PROPERTIES(PROPERTY_ID, PROPERTY_NAME, PROPERTY_VALUE, PROPERTY_TYPE)" << "\n" << "values" << "\n";
    for (const auto& [key, value] : config) {
        std::cout << "(" << "'" << startIndex << "'" << ", '" << key << "', '" << value << "', '" << type << "'), \n";
        startIndex++;
    }
}
