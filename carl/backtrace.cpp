#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
    /* data */
    char a;
    char b;
    int i;
    char c;
    char d;
};

struct C {
    char a;
    A b;
    char c;
};

TEST(backtrace, leetcode344) {
    cout << sizeof(C) << endl;
}