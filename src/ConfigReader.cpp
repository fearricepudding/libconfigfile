#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

#include "ConfigReader.h"

std::map<std::string, std::string> ConfigReader::getConfig(std::string configPath) {
    std::string content;
    std::ifstream config(configPath);
    bool cont = false;
    bool cont_end = false;
    std::string cont_content;

    std::map<std::string, std::string> configMap;
    while (std::getline(config, content)) {
        cont = false;
        content.erase(std::remove_if(content.begin(), content.end(), isspace), content.end());

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
        std::string value = finalContent.substr(finalContent.find("=")+1, finalContent.size());
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

