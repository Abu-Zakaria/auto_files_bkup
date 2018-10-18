#include "ConfigReader.hpp"
#include <fstream>
#include <helpers.hpp>
#include <vector>

ConfigReader::ConfigReader(std::string file_path)
{
    file.open(file_path, std::fstream::in | std::fstream::out);
}

ConfigReader::~ConfigReader()
{
    file.close();
}

bool ConfigReader::exists(std::string key)
{
    std::string line;
    while(std::getline(file, line))
    {
        std::vector<std::string> line_items = helpers::explode('=', line);
        if(line_items[0] == key)
        {
            return true;
        }
    }
    return false;
}

std::string ConfigReader::get(std::string key)
{ }

void ConfigReader::add(std::string key, std::string value)
{ }

void ConfigReader::set(std::string key, std::string val)
{ }

void ConfigReader::remove(std::string key)
{ }