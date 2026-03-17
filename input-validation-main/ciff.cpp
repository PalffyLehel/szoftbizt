#include "ciff.h"

ciff::ciff()
{
    magic = "CIFF";
    header_size = 0;
    content_size = 0;
    width = 0;
    height = 0;
    caption = "";
}

ciff::ciff(const std::string magic, const long header_size, const long content_size,
    const long width, const long height, const std::string caption,
    const std::list<std::string> tag_list, const std::list<std::string> pixel_list)
{
    this->magic = magic;
    this->header_size = header_size;
    this->content_size = content_size;
    this->width = width;
    this->height = height;
    this->caption = caption;
    this->tag_list = tag_list;
    this->pixel_list = pixel_list;
}

ciff ciff::parse_ciff_file(std::string file_path)
{
    ciff new_ciff = ciff();
    long bytes_read = 0;

    std::ifstream ciff_input(file_path, std::ios::binary);

    if (!ciff_input.is_open())
    {
        throw ciff_exception("Could not open file " + file_path);
    }

    char* input_buffer = new char[20];
    std::fill_n(input_buffer, 20, '\0');
    std::string magic;
 
    ciff_input.read(input_buffer, 4);
    bytes_read += 4;
    input_buffer[4] = '\0';
    magic = std::string(input_buffer);

    if (magic.size() != 4)
    {
        throw ciff_exception("Magic bites must be 4 bytes");
    }
    if (magic != "CIFF")
    {
        throw ciff_exception("The magic is not CIFF");
    }
    new_ciff.magic = magic;


    ciff_input.read(input_buffer, 8);
    if (ciff_input.peek() == EOF)
    {
        throw ciff_exception("Incorrect file format");
    }
    bytes_read += 8;
    input_buffer[8] = '\0';
    long header_size;
    try
    {
        header_size = get_long_from_little_endian(input_buffer);
    }
    catch (std::out_of_range e)
    {
        throw ciff_exception("Header size not in the proper range");

    }
    catch (ciff_exception e2)
    {
        throw ciff_exception("Header size not in the proper range");
    }
    new_ciff.header_size = header_size;

    ciff_input.read(input_buffer, 8);
    if (ciff_input.peek() == EOF)
    {
        throw ciff_exception("Incorrect file format");
    }
    bytes_read += 8;
    input_buffer[8] = '\0';
    long content_size;
    try
    {
        content_size = get_long_from_little_endian(input_buffer);
    }
    catch (std::out_of_range e)
    {
        throw ciff_exception("Content size not in the proper range");

    }
    catch (ciff_exception e2)
    {
        throw ciff_exception("Content is empty");
    }
    new_ciff.content_size = content_size;

    ciff_input.read(input_buffer, 8);
    if (ciff_input.peek() == EOF)
    {
        throw ciff_exception("Incorrect file format");
    }
    bytes_read += 8;
    input_buffer[8] = '\0';
    long width;
    try
    {
        width = get_long_from_little_endian(input_buffer);
    }
    catch (std::out_of_range e)
    {
        throw ciff_exception("Width not in the proper range");

    }
    catch (ciff_exception e2)
    {
        throw ciff_exception("Width is 0");
    }
    new_ciff.width = width;

    ciff_input.read(input_buffer, 8);
    if (ciff_input.peek() == EOF)
    {
        throw ciff_exception("Incorrect file format");
    }
    bytes_read += 8;
    input_buffer[8] = '\0';
    long height;
    try
    {
        height = get_long_from_little_endian(input_buffer);
    }
    catch (std::out_of_range e)
    {
        throw ciff_exception("Height not in the proper range");

    }
    catch (ciff_exception e2)
    {
        throw ciff_exception("Height is 0");
    }
    new_ciff.height = height;

    if (content_size != width * height * 3)
    {
        throw ciff_exception("Content size is not equal to width * height * 3");
    }

    std::string caption = "";
    do
    {
        ciff_input.read(input_buffer, 1);
        if (ciff_input.peek() == EOF)
        {
            throw ciff_exception("Incorrect file format");
        }
        bytes_read++;
        
        if (input_buffer[0] == '\0')
        {
            throw ciff_exception("Error while reading caption");
        }
        caption += input_buffer[0];
    } while (input_buffer[0] != '\n');
    new_ciff.caption = caption;

    std::list<std::string> tags;
    std::string tag = "";
    for (bytes_read; bytes_read < header_size;)
    {
        ciff_input.read(input_buffer, 1);
        if (ciff_input.peek() == EOF)
        {
            throw ciff_exception("Incorrect file format");
        }
        bytes_read++;
        
        if (input_buffer[0] == '\n')
        {
            throw ciff_exception("Character must not be \\n");
        }

        tag += input_buffer[0];
        if (input_buffer[0] == '\0')
        {
            tags.push_back(tag);
            tag = "";
        }

        if (bytes_read == header_size && input_buffer[0] != '\0')
        {
            throw ciff_exception("The last character is not \\0");
        }
    }

    for (std::string tag : tags)
    {
        if (tag[tag.size() - 1] != '\0')
        {
            throw ciff_exception("The last character of a tag is not \\0");
        }
    }
    new_ciff.tag_list = tags;

    std::list<std::string> pixels;
    std::string pixel;
    input_buffer[3] = '\0';
    for (bytes_read; bytes_read < header_size + content_size;)
    {
        ciff_input.read(input_buffer, 3);
        bytes_read += 3;
        if (ciff_input.peek() == EOF && bytes_read != header_size + content_size)
        {
            throw ciff_exception("Incorrect file format");
        }
        pixel = input_buffer;
        pixels.push_back(pixel);
    }
    new_ciff.pixel_list = pixels;

    if (ciff_input.peek() != EOF)
    {
        throw ciff_exception("Did not reach the end of file");
    }

    ciff_input.close();
    return new_ciff;
}

long ciff::get_long_from_little_endian(const char* input_buffer)
{
    std::string size_string = std::string(input_buffer);
    std::reverse(size_string.begin(), size_string.end());
    std::stringstream hex_converter;

    unsigned char* proper_buffer = new unsigned char[size_string.size() + 1];
    if (size_string.empty())
    {
        throw ciff_exception("empty");
    }
    for (int i = 0; i < size_string.size(); i++)
    {
        proper_buffer[i] = size_string[i];
    }

    for (int i = 0; i < size_string.size(); i++)
    {
        hex_converter << std::hex << (int)proper_buffer[i];
    }
    std::string header_size_hex = hex_converter.str();
    return std::stol(header_size_hex, nullptr, 16);
}
