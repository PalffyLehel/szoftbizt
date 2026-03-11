#pragma once

#include <string>

extern "C" class ciff_exception
{
public:
    std::string message;
    
    ciff_exception(std::string message);
};