#pragma once
#include <string>

class Reader
{
public:
    Reader(){};
    virtual ~Reader(){};

    virtual bool open() = 0;

    virtual void close() = 0;

    virtual bool loaded() = 0;

    virtual bool exists(std::string key) = 0;

    virtual std::string get(std::string key) = 0;

    virtual void add(std::string key, std::string value) = 0;

    virtual void set(std::string key, std::string val) = 0;

    virtual void remove(std::string key) = 0;
};