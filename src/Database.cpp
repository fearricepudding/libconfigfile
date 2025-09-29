#include <iostream>

#include "Database.h"

inline void replace(std::string &str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void Database::generateInserts(std::map<std::string, std::string> config) {
    Database::generateInserts(config, 0, "GENERAL");
}

void Database::generateInserts(std::map<std::string, std::string> config, int startIndex, std::string type) {
    std::cout << "insert into PROPERTIES(PROPERTY_ID, PROPERTY_NAME, PROPERTY_VALUE, PROPERTY_TYPE)" << "\n" << "values" << "\n";
    for (const auto& [key, value] : config) {
        std::string val(value);
        replace(val, std::string("'"), std::string("\\'"));
        std::cout << "(" << "'" << startIndex << "'" << ", '" << key << "', '" << val << "', '" << type << "'), \n";
        startIndex++;
    }
}
