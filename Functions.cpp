#include "Functions.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif


void rout(std::string text)
{
#ifdef _WIN32
    int cp = GetConsoleOutputCP();
    SetConsoleOutputCP(65001);
    std::cout << text;
    SetConsoleOutputCP(cp);
#endif
}



std::string choice(std::string str, std::string choices)
{
    const char *array = choices.c_str();
    std::string choice = " ";
    while (!(choice.length() == 1 && strchr(array, choice[0])))
    {
        rout(str);
        getline(std::cin, choice);
    }
    return choice;
}

bool is_number(const std::string& s) 
{ 
    return !s.empty() && (s.find_first_not_of("0123456789") == s.npos); 
}






