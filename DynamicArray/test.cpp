#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include"DynamicArray.h"

TEST_CASE( "creating DynamicArray" ) {
    DynamicArray<int> arr(5);
    REQUIRE( arr.getCapacity() == 5);

}






