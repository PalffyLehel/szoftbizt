#pragma once

#include <iostream>
#include <string>
#include <list>

class Ciff
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

public:
    Ciff();
    Ciff(const std::string magic_chars, const long header_size, const long content_size,
        const long width, const long height, const std::string caption_string,
        const std::list<std::string> tag_list, const std::list<std::string> pixel_list);

    static Ciff parse_ciff_file(std::string file_path);
};