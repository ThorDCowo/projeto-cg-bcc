#include "framework_test.h"
#include "../data/entities/object.test.cpp"
#include "../infra/clipper/clipper.test.cpp"
#include "../infra/coordinate_parser/coordinate_parser.h"
#include "../infra/coordinate_parser/coordinate_parser.test.cpp"
#include "../infra/face_parser/face_parser.h"
#include "../infra/face_parser/face_parser.test.cpp"
#include "../infra/file_reader/file_reader.h"
#include "../use_cases/read_coordinate_file/read_coordinate_file.use_case.h"
#include "../use_cases/read_coordinate_file/read_coordinate_file.use_case.test.cpp"

void runTests() {
    FrameworkTest frameworkTest;

    Clipper clipper;
    ClipperTest clipperTest(&clipper);

    CoordinateParser coordinateParser;
    CoordinateParserTest coordinateParserTest(&coordinateParser);

    FaceParser faceParser;
    FaceParserTest faceParserTest(&faceParser);
    
    FileReader fileReader;
    ReadCoordinateFileUseCase readCoordinateFileUseCase(
        &fileReader,
        &coordinateParser,
        &faceParser
    );
    ReadCoordinateFileUseCaseTest readCoordinateFileUseCaseTest(&readCoordinateFileUseCase);

    ObjectTest objectTest;


    frameworkTest.registerTest(&clipperTest);
    frameworkTest.registerTest(&coordinateParserTest);
    frameworkTest.registerTest(&readCoordinateFileUseCaseTest);
    frameworkTest.registerTest(&objectTest);
    frameworkTest.registerTest(&faceParserTest);

    frameworkTest.run();
}