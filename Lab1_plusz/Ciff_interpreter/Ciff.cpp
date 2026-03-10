#include "Ciff.h"

Ciff::Ciff()
{
    magic_chars = "CIFF";
    header_size = 0;
    content_size = 0;
    width = 0;
    height = 0;
    caption_string = "";
}

Ciff::Ciff(const std::string magic_chars, const long header_size, const long content_size,
    const long width, const long height, const std::string caption_string,
    const std::list<std::string> tag_list, const std::list<std::string> pixel_list)
{
    this->magic_chars = magic_chars;
    this->header_size = header_size;
    this->content_size = content_size;
    this->width = width;
    this->height = height;
    this->caption_string = caption_string;
    this->tag_list = tag_list;
    this->pixel_list = pixel_list;
}

Ciff Ciff::parse_ciff_file(std::string file_path)
{
    std::cout << file_path << std::endl;

    return Ciff();
}