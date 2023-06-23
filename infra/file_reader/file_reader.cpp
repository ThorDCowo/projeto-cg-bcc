#include "file_reader.h"
using namespace std;

bool FileReader::open(QString filename)
{
    QFile file(filename);
    this->file = &file;
    this->isOpened = file.open(QIODevice::ReadOnly | QIODevice::Text);
    return this->isOpened;
}

bool FileReader::isOpen() const
{
    return this->isOpened;
}

void FileReader::close()
{
    file->close();
    this->isOpened = false;
}

void FileReader::readLinesWithCallback(
    const function<void(
        const string &, 
        const bool isEOF
    )> &callback    
)
{
    QTextStream in(this->file);
    QString line;
    bool isEOF = in.atEnd();    
    do {
        line = in.readLine();
        callback(line.toStdString(), isEOF);
        in.atEnd();
    } while (!isEOF);
}