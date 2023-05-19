#include "framework_test.h"
#include "object_test.h"
#include "../core/entities/line.h"
#include "../infra/clipper/clipper.test.cpp"
#include "../infra/coordinate_parser/coordinate_parser.h"
#include "../infra/coordinate_parser/coordinate_parser.test.cpp"
#include "../infra/file_reader/file_reader.h"
#include "../use_cases/read_coordinate_file/read_coordinate_file.use_case.h"
#include "../use_cases/read_coordinate_file/read_coordinate_file.use_case.test.cpp"

void runTests() {
    FrameworkTest frameworkTest;

    Line line("line", QList<Coordinate>{Coordinate(0,0), Coordinate(1,1)});
    ObjectTest objectTest(&line);

    Clipper clipper;
    ClipperTest clipperTest(&clipper);

    CoordinateParser coordinateParser;
    CoordinateParserTest coordinateParserTest(&coordinateParser);

    FileReader fileReader;
    ReadCoordinateFileUseCase readCoordinateFileUseCase(&fileReader, &coordinateParser);
    ReadCoordinateFileUseCaseTest readCoordinateFileUseCaseTest(&readCoordinateFileUseCase);

    frameworkTest.registerTest(&objectTest);
    frameworkTest.registerTest(&clipperTest);
    frameworkTest.registerTest(&coordinateParserTest);
    frameworkTest.registerTest(&readCoordinateFileUseCaseTest);

    frameworkTest.run();
}