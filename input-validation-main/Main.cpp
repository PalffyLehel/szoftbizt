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

    std::string path = "D:\\Egyetem\\3\\f2\\kol2\\input-validation-main\\test-vectors";

    try
    {
        ciff new_ciff = ciff::parse_ciff_file(path + "\\" + argv[1]);
        std::cout << "Valid file" << std::endl;
    }
    catch (ciff_exception e)
    {
        std::cout << e.message << std::endl;
    }

    return 0;
}