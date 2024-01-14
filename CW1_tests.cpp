#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

TEST_CASE("Example Test Case", "[example]") {
    // Your test code goes here

    // Example: Check if addition works
    REQUIRE(1 + 1 == 2);
}

TEST_CASE("Another Test Case", "[example]") {
    // Another test code goes here

    // Example: Check if subtraction works
    REQUIRE(3 - 2 == 1);
}
