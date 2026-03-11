#pragma once

#include <string>

class ciff_exception
{
public:
    std::string message;
    
    ciff_exception(std::string message);
};