#ifndef FILE_READER_H
#define FILE_READER_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class FileReader {
public:
    bool open(QString filename);
    bool isOpen() const;
    void close();
    void readLinesWithCallback(
        const function<void(
            const string &, 
            const bool isEOF
        )> &callback    
    );

private:
    QFile* file;
    bool isOpened = false;
};

#endif // FILE_READER_H