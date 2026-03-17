#include <iostream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include "ciff.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong call" << std::endl;
    }

    std::string path = "D:\\Egyetem\\3\\f2\\kol2\\Lab1_plusz\\Resources";

    try
    {
        ciff new_ciff = ciff::parse_ciff_file(path + "\\" + argv[1]);
        std::cout << "Valid file" << std::endl;
        std::cout << new_ciff.magic << std::endl;
        std::cout << new_ciff.header_size << std::endl;
        std::cout << new_ciff.content_size << std::endl;
        std::cout << new_ciff.width << std::endl;
        std::cout << new_ciff.height << std::endl;
        std::cout << new_ciff.caption << std::endl;

        std::cout << new_ciff.tag_list.size() << std::endl;
        for (std::string tag : new_ciff.tag_list)
        {
            std::cout << tag << std::endl;
        }

        std::cout << new_ciff.pixel_list.size() << std::endl;
        for (std::string pixel : new_ciff.pixel_list)
        {
            std::cout << pixel << std::endl;
        }

        std::cout << new_ciff.is_valid << std::endl;
        std::cout << new_ciff.error_message << std::endl;
    }
    catch (ciff_exception e)
    {
        std::cout << e.message << std::endl;
    }

    return 0;
}