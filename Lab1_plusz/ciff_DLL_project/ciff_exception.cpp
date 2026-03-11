#include "pch.h"
#include "ciff_exception.h"

ciff_exception::ciff_exception(std::string message)
{
    this->message = message;
}