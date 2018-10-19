#include <catch2/catch.hpp>
#include "../src/ConfigReader.hpp"

ConfigReader config("../auto_bkup_configs.txt");

TEST_CASE("file is loaded", "[config_reader]")
{
    REQUIRE(config.loaded());
}

TEST_CASE("'path' key exists", "[config_reader]")
{
    REQUIRE(config.exists("path"));
}

TEST_CASE("'xyz' key doesn't exists", "[config_reader]")
{
    REQUIRE(!config.exists("xyz"));
}

TEST_CASE("'path' key have '~/destination' value", "[config_reader]")
{
    REQUIRE(config.get("path") == "~/destination");
}

