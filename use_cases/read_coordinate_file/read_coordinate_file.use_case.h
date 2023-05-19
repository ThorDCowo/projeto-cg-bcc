#ifndef READ_COORDINATE_FILE_USE_CASE_H
#define READ_COORDINATE_FILE_USE_CASE_H

#include "../../core/entities/coordinate.h"
#include "../../infra/coordinate_parser/coordinate_parser.h"
#include "../../infra/file_reader/file_reader.h"
#include "../../infra/file_writer/file_writer.h"
#include "../../core/entities/polygon.h"

class ReadCoordinateFileUseCase {
private:
    CoordinateParser* coordinateParser;
    FileReader* reader;
public:
    ReadCoordinateFileUseCase(FileReader* reader, CoordinateParser* coordinateParser) {
        this->reader = reader;
        this->coordinateParser = coordinateParser;
    }

    
QList<Object*> execute(string filename);

};

#endif // READ_COORDINATE_FILE_USE_CASE_H