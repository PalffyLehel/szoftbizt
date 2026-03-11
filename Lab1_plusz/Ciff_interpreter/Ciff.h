#pragma once

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include<iomanip>
#include "ciff_exception.h"

class ciff
{
private:
    std::string magic_chars;
    long header_size;
    long content_size;
    long width;
    long height;
    std::string caption_string;
    std::list<std::string> tag_list;
    std::list<std::string> pixel_list;

    static char* to_little_endian(const char* big_endian_string, int string_size);

public:
    ciff();
    ciff(const std::string magic_chars, const long header_size, const long content_size,
        const long width, const long height, const std::string caption_string,
        const std::list<std::string> tag_list, const std::list<std::string> pixel_list);

    static ciff parse_ciff_file(std::string file_path);
};