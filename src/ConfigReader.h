#pragma once 

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

class ConfigReader {
    public: 
        static std::map<std::string, std::string> getConfig(std::string);
        static void dump_config(std::map<std::string, std::string>);
};
