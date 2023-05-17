#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>

#include "file_reader.h"
using namespace std;

bool FileReader::open()
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

vector<string> FileReader::readLines()
{
    vector<string> lines;
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

void FileReader::readLinesWithCallback(const function<void(const string &)> &callback)
{
    string line;
    while (getline(file, line))
    {
        callback(line);
    }
}