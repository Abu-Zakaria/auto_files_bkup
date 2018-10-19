#include "ConfigReader.hpp"
#include <fstream>
#include "helpers.hpp"
#include <vector>

ConfigReader::ConfigReader(std::string file_path)
{
    file.open(file_path, std::fstream::in | std::fstream::out | std::fstream::app);
}

ConfigReader::~ConfigReader()
{
    file.close();
}

bool ConfigReader::loaded()
{
    return file.is_open();
}

bool ConfigReader::exists(std::string key)
{
    return !(get(key) == "");
}

std::string ConfigReader::get(std::string key)
{
    std::string line;
    while(std::getline(file, line))
    {
        std::vector<std::string> line_items = helpers::explode('=', line);
        if(line_items[0] == key)
        {
            return line_items[1];
        }
    }
    return "";
}

void ConfigReader::add(std::string key, std::string value)
{
    std::string line = "\n" + key + "=" + value;

    file << line;
}

void ConfigReader::set(std::string key, std::string val)
{ }

void ConfigReader::remove(std::string key)
{ }