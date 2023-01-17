#ifndef VIIKKO_3_UTILITY_H
#define VIIKKO_3_UTILITY_H

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
void instructions();

#endif //VIIKKO_3_UTILITY_H
