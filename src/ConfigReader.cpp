#include "ConfigReader.hpp"
#include <fstream>
#include "helpers.hpp"
#include <vector>

ConfigReader::ConfigReader(std::string file_path) : file_path(file_path)
{}

ConfigReader::~ConfigReader()
{
    if(loaded())
        close();
}

bool ConfigReader::open()
{
    file.open(file_path, std::fstream::in | std::fstream::out | std::fstream::app);
    return file.is_open();
}

bool ConfigReader::open(std::string type)
{
    if(type == "in")
        file.open(file_path, std::fstream::in);
    else if(type == "out")
        file.open(file_path, std::fstream::out);
    else if(type == "app")
        file.open(file_path, std::fstream::app);

    return file.is_open();
}

void ConfigReader::close()
{
    if(file.is_open())
        file.close();
}

bool ConfigReader::loaded()
{
    return file.is_open();
}

bool ConfigReader::exists(std::string key)
{
    bool exists = get(key) != "";

    return exists;
}

std::string ConfigReader::get(std::string key)
{
    open();

    std::string value = "";
    std::string line;

    while(std::getline(file, line))
    {
        std::vector<std::string> line_items = helpers::explode('=', line);
        if(line_items[0] == key)
        {
            value = line_items[1];
            break;
        }
    }

    close();

    return value;
}

void ConfigReader::add(std::string key, std::string value)
{
    open();
    std::string line = "\n" + key + "=" + value;

    file << line;

    close();
}

void ConfigReader::set(std::string key, std::string val)
{
    if(exists(key))
    {
        open("in");
        std::vector<std::string> lines;
        std::string line;

        while(std::getline(file, line))
        {
            lines.push_back(line);
        }
        close();

        clear();

        open("app");

        for(std::string line : lines)
        {
            if(line == "")
            {
                file << "\n";

                continue;
            }

            std::vector<std::string> items = helpers::explode('=', line);

            if(items.at(0) == key)
            {
                items[1] = val;
                std::cout << "setting" << std::endl;
            }

            file << items.at(0) << "=" << items.at(1) << "\n";
        }

        close();
    }
}

void ConfigReader::remove(std::string key)
{ }

void ConfigReader::clear()
{
    open("out");

    file << "";

    close();
}