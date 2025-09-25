#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cctype>
#include <locale>

#include "ConfigReader.h"

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

std::map<std::string, std::string> ConfigReader::getConfig(std::string configPath) {
    std::string content;
    std::ifstream config(configPath);
    bool cont = false;
    bool cont_end = false;
    std::string cont_content;

    std::map<std::string, std::string> configMap;
    while (std::getline(config, content)) {
        cont = false;
        trim(content);

        if (content[0] == '#' || content.empty()) {
            continue;
        }

        if (content[content.size()-1] == '\\' || cont_end) {
            cont = true;
            cont_end = true;

            bool final = false;
            if (content[content.size()-1] != '\\') {
                cont_content += content;
                final = true;
            } else {
                cont_content += content.substr(0, content.size()-1);
            }
            if (!final) {
                continue;
            }
        }

        std::string finalContent;
        if (cont_end) {
            // cont end
            cont_end = false;
            finalContent = cont_content;
            cont_content = "";
        } else if (!cont && !cont_end) {
            finalContent = content;
        };

        std::string key = finalContent.substr(0, finalContent.find("="));
        trim(key);
        std::string value = finalContent.substr(finalContent.find("=")+1, finalContent.size());
        trim(value);
        configMap[key] = value;
    }
    config.close();
    return configMap;
}

void ConfigReader::dump_config(std::map<std::string, std::string> config) {
    for (const auto& [key, value] : config) { 
        std::cout << '[' << key << "] = " << value << "\n";
    }
}

