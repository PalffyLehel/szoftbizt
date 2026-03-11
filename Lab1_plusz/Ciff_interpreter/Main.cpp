#include <iostream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include "ciff.h"

namespace fs = std::filesystem;

int main() 
{
    std::string path = "D:\\Egyetem\\3\\f2\\kol2\\Lab1_plusz\\Resources";

    long proba = std::stol("3e8", nullptr, 16);

    for (const auto& entry : fs::directory_iterator(path))
    {
        try 
        {
            ciff::parse_ciff_file(entry.path().string());

        } 
        catch(ciff_exception e) 
        {
            std::cout << e.message << std::endl;
        }

        break;
    }

    return 0;
}