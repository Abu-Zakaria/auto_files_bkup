#pragma once

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <regex>

namespace helpers
{
    template <typename T>
    void print(T shit)
    {
        std::cout << shit;
    }

    template <typename T>
    void printl(T shit)
    {
        std::cout << shit << std::endl;
    }

    inline std::vector<std::string> explode(char delim, const std::string& s)
    {
        std::vector<std::string> result;

        if(s == "")
        {
            result.push_back("");
            return result;
        }
        std::istringstream iss(s);

        std::string token;

        for(token; std::getline(iss, token, delim);)
        {
            result.push_back(token);
        }

        return result;
    }

    inline std::string current_dir()
    {
        char CurrentPath[FILENAME_MAX];

        std::string path = getcwd(CurrentPath, sizeof(CurrentPath));

//        return path;
        return helpers::explode('/', path).back();
    }

    inline bool copyDir(
            boost::filesystem::path const & source,
            boost::filesystem::path const & destination
    )
    {
        namespace fs = boost::filesystem;
        try
        {
            // Check whether the function call is valid
            if(
                    !fs::exists(source) ||
                    !fs::is_directory(source)
                    )
            {
                std::cerr << "Source directory " << source.string()
                << " does not exist or is not a directory." << '\n'
                        ;
                return false;
            }
            if(fs::exists(destination))
            {
                std::cerr << "Destination directory " << destination.string()
                << " already exists." << '\n'
                        ;
                return false;
            }
            // Create the destination directory
            if(!fs::create_directory(destination))
            {
                std::cerr << "Unable to create destination directory"
                << destination.string() << '\n'
                        ;
                return false;
            }
        }
        catch(fs::filesystem_error const & e)
        {
            const char * error_message = "boost::filesystem::create_directory: No such file or directory:";
            if(strcmp(e.what(), error_message))
            {
                printl("+--------------------------------------------------------------------------------------------+");
                printl("| The destination path doesn't exists. Edit your configuration file. (auto_bkup_configs.txt) |");
                printl("+--------------------------------------------------------------------------------------------+");
            }
            else
            {
                std::cerr << e.what() << '\n';
            }

            return false;
        }
        // Iterate through the source directory
        for(
                fs::directory_iterator file(source);
                file != fs::directory_iterator(); ++file
                )
        {
            try
            {
                fs::path current(file->path());
                if(fs::is_directory(current))
                {
                    // Found directory: Recursion
                    if(
                            !copyDir(
                                    current,
                                    destination / current.filename()
                            )
                            )
                    {
                        return false;
                    }
                }
                else
                {
                    // Found file: Copy
                    fs::copy_file(
                            current,
                            destination / current.filename()
                    );
                }
            }
            catch(fs::filesystem_error const & e)
            {
                std:: cerr << e.what() << '\n';
            }
        }
        return true;
    }
}