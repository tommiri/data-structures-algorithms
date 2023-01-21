#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

enum Error_code
{
    success,
    fail,
    utility_range_error,
    underflow,
    overflow,
    fatal,
    not_present,
    duplicate_error,
    entry_inserted,
    entry_found,
    internal_error
};

bool user_says_yes();

