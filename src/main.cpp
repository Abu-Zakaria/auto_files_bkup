#include <iostream>
#include "helpers.hpp"
#include "Transfer.hpp"
#include "ConfigReader.hpp"

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        ConfigReader config("./auto_bkup_configs.txt");

        config.open();

        if(!config.loaded())
        {
            helpers::printl("+----------------------------------------------------------+");
            helpers::printl("| No configuration file found for backup!                  |");
            helpers::printl("| Run the command again with --gen or -g flag to           |");
            helpers::printl("| generate a configuration file.                           |");
            helpers::printl("+----------------------------------------------------------+");

            return 0;
        }

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

    Transfer transfer(path);

    transfer.setTargetDir(target_dir);

    transfer.setDelay(delay_time);

    transfer.move();

    return 0;
}