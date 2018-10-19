#include <catch2/catch.hpp>
#include "../src/ConfigReader.hpp"
#include <iostream>

TEST_CASE("file is loaded", "[config_reader]")
{
    ConfigReader config("../auto_bkup_configs.txt");

    config.open();

    REQUIRE(config.loaded());
}

TEST_CASE("'path' key exists", "[config_reader]")
{
    ConfigReader config("../auto_bkup_configs.txt");

    REQUIRE(config.exists("path"));
}

TEST_CASE("'xyz' key doesn't exists", "[config_reader]")
{
    ConfigReader config("../auto_bkup_configs.txt");

    REQUIRE(!config.exists("xyz"));
}

TEST_CASE("'path' key have '~/destination' value", "[config_reader]")
{
    ConfigReader config("../auto_bkup_configs.txt");

    REQUIRE(config.get("path") == "~/destination");
}

TEST_CASE("successfully adds a new configuration to config file", "[config_reader]")
{
    ConfigReader config("../auto_bkup_configs.txt");

    std::string key = "testing",
                value = "it works";
    config.add(key, value);

    REQUIRE(config.get(key) == value);
}

TEST_CASE("updates a existing key's value", "[config_reader]")
{
    ConfigReader config("../auto_bkup_configs.txt");

    std::string key = "test_set",
                old_val = "old_val",
                new_val = "new_val";

    if(!config.exists(key))
        config.add(key, old_val);
    config.set(key, new_val);
    REQUIRE(config.get(key) == new_val);
}