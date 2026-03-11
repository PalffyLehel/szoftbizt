#include "ciff.h"

#include <vector>
#include <sstream>

ciff::ciff()
{
    magic_chars = "CIFF";
    header_size = 0;
    content_size = 0;
    width = 0;
    height = 0;
    caption_string = "";
}

ciff::ciff(const std::string magic_chars, const long header_size, const long content_size,
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

ciff ciff::parse_ciff_file(std::string file_path)
{
    std::ifstream ciff_input(file_path, std::ios::binary);

    if (!ciff_input.is_open())
    {
        throw ciff_exception("Could not open file " + file_path);
    }
    ciff_input.seekg(0, std::ios::end);
    int file_size = ciff_input.tellg();
    ciff_input.seekg(0, std::ios::beg);


    std::vector<unsigned char> fileData(file_size);
    ciff_input.read((char*)&fileData[0], file_size);
    ciff_input.close();

    ciff new_ciff = ciff();
    std::vector<unsigned char> magic_chars(fileData.begin(), fileData.begin() + 4);
    std::string magic(magic_chars.begin(), magic_chars.end());
    int offset = 20;

    std::vector<unsigned char> header_size_chars(fileData.begin() + offset, fileData.begin() + offset + 8);
    std::reverse(header_size_chars.begin(), header_size_chars.end());
    
    std::stringstream ss;
    for (int i = 0; i < header_size_chars.size(); ++i)
        ss << std::hex << (int)header_size_chars[i];
    std::string asd = ss.str();
    long header_size = std::stol(asd, nullptr, 16);

    return ciff();
}

char* ciff::to_little_endian(const char* little_endian_string, int string_size) 
{
    char* big_endian_string = new char[string_size + 1];

    for (int i = 0; i < string_size; i++)
    {
        big_endian_string[i] = little_endian_string[string_size - 1 - i];
    }

    return big_endian_string;
}