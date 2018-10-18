#pragma once
#include <string>
#include <Reader.hpp>
#include <fstream>

class ConfigReader : Reader
{
private:
    std::fstream file;

public:
    ConfigReader(std::string file_path);
    ~ConfigReader();

    bool exists(std::string key);

    std::string get(std::string key);

    void add(std::string key, std::string value);

    void set(std::string key, std::string val);

    void remove(std::string key);
};