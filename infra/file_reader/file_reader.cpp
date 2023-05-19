#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>

#include "file_reader.h"
using namespace std;

bool FileReader::open(string filename)
{
    file.open(filename);
    return file.is_open();
}

bool FileReader::isOpen() const
{
    return file.is_open();
}

void FileReader::close()
{
    file.close();
}

void FileReader::readLinesWithCallback(
    const function<void(
        const string &, 
        const bool isEOF
    )> &callback    
)
{
    string line;
    while (getline(file, line))
    {
        callback(line, file.eof());
    }
}