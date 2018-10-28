#include <iostream>
#include "helpers.hpp"
#include "Transfer.hpp"
#include "ConfigReader.hpp"
#include <thread>

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        ConfigReader config("./auto_bkup_configs.txt");

        config.open("in");

        if(!config.loaded())
        {
            helpers::printl("+----------------------------------------------------------+");
            helpers::printl("| No configuration file found for backup!                  |");
            helpers::printl("| Run the command again with --gen or -g flag to           |");
            helpers::printl("| generate a configuration file.                           |");
            helpers::printl("+----------------------------------------------------------+");

            return 0;
        }
        config.close();

        helpers::printl("+----------------------------------------------------------+");
        helpers::printl("| Using ./auto_bkup_configs.txt file for configuration...  |");
        helpers::printl("+----------------------------------------------------------+");

        try
        {
            if(config.get("path") == "" | stoi(config.get("delay")) < 1)
            {
                helpers::printl("");

                helpers::printl("+--------------------------------------------+");
                helpers::printl("| failed: The configuration file is invalid! |");
                helpers::printl("+--------------------------------------------+");

                return 0;
            }
        }
        catch(std::exception& e)
        {
            const char* stoi_error = "stoi";

            if(strcmp(e.what(), stoi_error) == 0)
            {
                helpers::printl("");
                helpers::printl("+------------------------------------------------------------------------+");
                helpers::printl("| failed: Provide an integer value at 'delay' key in configuration file! |");
                helpers::printl("+------------------------------------------------------------------------+");
            }
            else
            {
                helpers::printl("");
                helpers::printl("+------------------------------------------------------------------------+");
                helpers::printl(e.what());
                helpers::printl("+------------------------------------------------------------------------+");
            }

            return 0;
        }

    }

    if(argc == 2)
    {
        if(std::strcmp(*(argv + 1), "--gen") == 0 || std::strcmp(*(argv + 1), "-g") == 0)
        {
            ConfigReader config("./auto_bkup_configs.txt");

            if(!config.exists("path") || !config.exists("delay"))
            {
                if(!config.exists("path"))
                    config.add("path", "~/your/destination");
                if(!config.exists("delay"))
                    config.add("delay", "MINUTE");
            }

            helpers::printl("+--------------------------------------------------------------------------+");
            helpers::printl("| Generated a configuration file for auto backup! (auto_bkup_configs.txt)  |");
            helpers::printl("| Edit that file and run `auto_files_bkup` for auto backups.               |");
            helpers::printl("+--------------------------------------------------------------------------+");

            return 0;
        }
        helpers::printl("");

        helpers::printl("+----------------------------------------------+");
        helpers::printl("| DELAY TIME was not found!                    |");
        helpers::printl("| Please, provide a delay time of your backup! |");
        helpers::printl("+----------------------------------------------+");

        return 0;
    }

    std::string target_dir;

    unsigned int delay_time;

    std::string current_dir_name = helpers::current_dir();

    ConfigReader config("./auto_bkup_configs.txt");

    if(argc == 3)
    {
        target_dir = *(argv + 1);

        delay_time = (unsigned int)std::atoi(*(argv + 2));
    }
    else
    {
        target_dir = config.get("path");

        delay_time = (unsigned int)std::stoi(config.get("delay"));
    }


    if(delay_time < 1)
    {
        helpers::printl("+----------------------------------------------+");
        std::cerr <<    "| process failed: Invalid delay time!          |" << std::endl;
        helpers::printl("+----------------------------------------------+");

        return 0;
    }

    target_dir = target_dir + "/" + current_dir_name;

    std::string home_dir = std::getenv("HOME");

    std::regex target_dir_regex("~");

    target_dir = std::regex_replace(target_dir, target_dir_regex, home_dir);

    boost::filesystem::path full_path(boost::filesystem::current_path());

    std::string path = full_path.string();

    std::vector<std::string> target_path_elements = helpers::explode('/', target_dir);
    target_path_elements.pop_back();
    std::string where_to_backup = helpers::implode('/', target_path_elements);

    boost::filesystem::path where_to_backup_path(where_to_backup);

    if(!boost::filesystem::exists(where_to_backup_path))
    {
        helpers::printl("+--------------------------------------------------------------------------------------------+");
        helpers::printl("| The destination path doesn't exists. Edit your configuration file. (auto_bkup_configs.txt) |");
        helpers::printl("+--------------------------------------------------------------------------------------------+");

        return 0;
    }

    Transfer transfer(path);

    transfer.setTargetDir(target_dir);

    transfer.setDelay(delay_time);

    helpers::printl("+-----------------------------------+");
    helpers::printl("| Starting auto-backup...           |");
    helpers::printl("| --------------------------------- |");
    helpers::print("| Delay : " + std::to_string(transfer.getDelay()) + " minute(s)");

    for(int i = 0; i < 16 - std::to_string(transfer.getDelay()).length(); i++)
    {
        helpers::print(" ");
    }
    helpers::print("|\n");
    helpers::printl("+-----------------------------------+");

    while(true)
    {
        try
        {
            transfer.move();

            std::this_thread::sleep_for(std::chrono::minutes(delay));
        }
        catch(const char * message)
        {
            helpers::printl("+---------+");
            helpers::printl("| Failed! |");
            helpers::printl("+---------+");

            helpers::printl("");
            helpers::printl(message);

            break;
        }
    }

    return 0;
}