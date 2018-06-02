// vcpkg-test.cpp : Defines the entry point for the application.
//

#include "vcpkg-test.h"

unsigned int factorial(const unsigned int number)
{
    return ((number <= 1) ? number : factorial(number - 1) * number);
}

/** Catch test framework sample test case
TEST_CASE("Compute Factorials", "[factorial]")
{
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
}
*/

TEST(TestingConfiguration, BasicTest)
{
    EXPECT_EQ(0, 1);
}


int main(int argc, char *argv[])
{
    // Main function for Catch test framework
    //return Catch::Session().run(argc, argv);
     
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
