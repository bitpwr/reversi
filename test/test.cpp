#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iostream>

int calc()
{
    std::cout << "Testing, testing..." << std::endl;

    return 15;
}

TEST_CASE("Case One")
{
    REQUIRE(calc() == 15);
}
