#pragma once
#include <string>
#include "Reader.hpp"
#include <fstream>

class ConfigReader : Reader
{
private:
    std::string file_path;
    std::fstream file;

    void update(std::string type, std::string key, std::string val);

public:
    ConfigReader(std::string file_path);
    ~ConfigReader();

    bool open();

    bool open(std::string type);

    void close();

    bool loaded();

    bool exists(std::string key);

    std::string get(std::string key);

    void add(std::string key, std::string value);

    void set(std::string key, std::string val);

    void remove(std::string key);

    void clear();
};