#pragma once

#include <string>

class Transfer
{
private:
    const std::string current_dir;

    std::string target_dir;

    unsigned int delay; // in minute

public:
    Transfer(std::string current_dir);
    ~Transfer();

    std::string getCurrentDir() const;

    std::string getTargetDir() const;

    void setTargetDir(std::string path);

    unsigned int getDelay() const;

    void setDelay(unsigned int delay_minute);

    void move();

    int delete_dir(std::string path);
};