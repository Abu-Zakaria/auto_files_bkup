#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "helpers.h"
#include "Transfer.h"
#include <sstream>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        helpers::printl("DESTINATION was not found!");
        helpers::printl("Please, provide a destination path where your current directory will be backed up!");

        return 0;
    }
    else if(argc < 3)
    {
        helpers::printl("DELAY TIME was not found!");
        helpers::printl("Please, provide a delay time of your backup!");

        return 0;
    }

    std::string target_dir;

    std::string current_dir_name = helpers::current_dir();

    target_dir = *(argv + 1);
    int delay_time = std::atoi(*(argv + 2));

    target_dir = target_dir + "/" + current_dir_name;

    boost::filesystem::path full_path(boost::filesystem::current_path());

    std::string path = full_path.string();

    Transfer transfer(path);

    transfer.setTargetDir(target_dir);

    transfer.setDelay(delay_time);

    transfer.move();

    return 0;
}