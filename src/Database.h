#pragma once

#include <iostream>
#include <map>

class Database {
public: 
    static void generateInserts(std::map<std::string, std::string>);
    static void generateInserts(std::map<std::string, std::string>, int, std::string);
};
