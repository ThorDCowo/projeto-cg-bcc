#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class FileReader {
public:
    bool open(string filename);
    bool isOpen() const;
    void close();
    vector<string> readLines();
    void readLinesWithCallback(const function<void(const string&)>& callback);

private:
    ifstream file;
};

#endif // FILE_READER_H