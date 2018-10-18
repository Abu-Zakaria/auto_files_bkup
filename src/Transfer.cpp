#include "Transfer.hpp"
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include "../lib/helpers.hpp"
#include <thread>
#include <time.h>

Transfer::Transfer(std::string current_dir): current_dir(current_dir)
{ }

Transfer::~Transfer()
{ }

std::string Transfer::getCurrentDir() const
{
    return current_dir;
}

std::string Transfer::getTargetDir() const
{
    return target_dir;
}

void Transfer::setTargetDir(std::string path)
{
    target_dir = path;
}

void Transfer::move()
{
    while(true)
    {
        delete_dir(target_dir);

        boost::filesystem::path curr_dir(current_dir);

        helpers::copyDir(curr_dir, boost::filesystem::path(target_dir));

        time_t rawtime;
        struct tm * timeinfo;
        char formatted_time[80];

        time(&rawtime);

        timeinfo = localtime(&rawtime);

        strftime(formatted_time, 80, "%H:%M", timeinfo);

        std::cout << "[" << formatted_time << "] - Backing up files to " << getTargetDir() << std::endl;

        std::this_thread::sleep_for(std::chrono::minutes(delay));
    }
}

int Transfer::delete_dir(std::string dir_path)
{
    boost::filesystem::path path = dir_path;

    return boost::filesystem::remove_all(path);
}

unsigned int Transfer::getDelay() const
{
    return delay;
}

void Transfer::setDelay(unsigned int delay_minute)
{
    delay = delay_minute;
}