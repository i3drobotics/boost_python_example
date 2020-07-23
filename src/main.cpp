#include "testpyhelper.hpp"
#include <cstdlib> // setenv
#include <iostream>

int main( int argc, char ** argv ) {
    TestPyHelper t = TestPyHelper();
    t.testAll();
}