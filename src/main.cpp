#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <boost/program_options.hpp>

#include "ConfigReader.h"
#include "Database.h"


int main(int argc, char** argv) { 

    boost::program_options::variables_map vm;
    boost::program_options::options_description desc("Allowed options");

    std::string configPath;

    try{
        desc.add_options()
            ("help", "produce help message")
            ("debug", "start in debug mode")
            ("dump", "Output config file to cli")
            ("raw-statements", "Output raw SQL insert statements for the configs")
            ("raw-start-index", boost::program_options::value<int>(), "Set a start index for the raw SQL statements")
            ("raw-type", boost::program_options::value<std::string>(), "Set a type for the database")
            ("path", boost::program_options::value<std::string>(), "Define the config path");

        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

    } catch(std::exception &e) {
        std::cerr << "error: " << e.what() << "\n" << "For help use ./PAWNY --help \n";
        return 1;
    };

     if (vm.count("help") || !vm.count("path")) {
        std::cout << desc << "\n";
        return 0;
    };

    if (vm.count("path")) {
        configPath = vm["path"].as<std::string>();
    }

    std::map<std::string, std::string> config = ConfigReader::getConfig(configPath);
    
    if (vm.count("dump")) {
        ConfigReader::dump_config(config);
        return 0;
    };

    if (vm.count("raw-statements")) {
        int startIndex = 0;
        std::string type = "GENERAL";
        if (vm.count("raw-start-index")) {
            startIndex = vm["raw-start-index"].as<int>();
        }

        if (vm.count("raw-type")) {
            type = vm["raw-type"].as<std::string>();
        }

        Database::generateInserts(config, startIndex, type);
        return 0;
    }

    std::cout << "Found " << config.size() << " config items" << std::endl;

    return 0;
}


