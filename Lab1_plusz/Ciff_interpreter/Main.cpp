#include <iostream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include "ciff.h"

namespace fs = std::filesystem;

int main() 
{
    std::string path = "D:\\Egyetem\\3\\f2\\kol2\\Lab1_plusz\\Resources";

    for (const auto& entry : fs::directory_iterator(path))
    {
        try 
        {
            ciff::parse_ciff_file(entry.path().string());
            std::cout << entry.path().string() << " | " << "Valid file" << std::endl;
        } 
        catch(ciff_exception e) 
        {
            std::cout << entry.path().string() << " | " << e.message << std::endl;
        }

    }

    return 0;
}