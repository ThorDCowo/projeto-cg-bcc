#ifndef READ_COORDINATE_FILE_USE_CASE_H
#define READ_COORDINATE_FILE_USE_CASE_H

#include "../../core/entities/coordinate.h"
#include "../../infra/coordinate_parser/coordinate_parser.h"
#include "../../infra/face_parser/face_parser.h"
#include "../../infra/file_reader/file_reader.h"
#include "../../core/entities/polygon.h"
#include <QList>
#include <iostream>

class ReadCoordinateFileUseCase {
private:
    CoordinateParser* coordinateParser;
    FileReader* reader;
    FaceParser* faceParser;
public:
    ReadCoordinateFileUseCase(
        FileReader* reader, 
        CoordinateParser* coordinateParser,
        FaceParser* faceParser
    ) {
        this->reader = reader;
        this->coordinateParser = coordinateParser;
        this->faceParser = faceParser;
    }

    
QList<Object*> execute(string filename);

};

#endif // READ_COORDINATE_FILE_USE_CASE_H
