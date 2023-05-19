#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class FileReader {
public:
    FileReader(const string& filename) : file(filename) {}
    bool open();
    bool isOpen() const;
    void close();
    vector<string> readLines();
    void readLinesWithCallback(const function<void(const string&)>& callback);

private:
    ifstream file;
    const string filename;
};
