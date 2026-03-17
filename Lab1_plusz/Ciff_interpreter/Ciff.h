#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include "ciff_exception.h"

class ciff
{
private:
    static long get_long_from_little_endian(const char*);

public:
    std::string magic;
    long header_size;
    long content_size;
    long width;
    long height;
    std::string caption;
    std::list<std::string> tag_list;
    std::list<std::string> pixel_list;
    bool is_valid;
    std::string error_message;

    ciff();
    ciff(const std::string magic, const long header_size, const long content_size,
        const long width, const long height, const std::string caption,
        const std::list<std::string> tag_list, const std::list<std::string> pixel_list);

    static ciff parse_ciff_file(std::string file_path);
};