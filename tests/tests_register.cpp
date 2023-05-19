#include "framework_test.h"
#include "object_test.h"
#include "../core/entities/line.h"
#include "../infra/clipper/clipper.test.cpp"
#include "../infra/coordinate_parser/coordinate_parser.h"
#include "../infra/coordinate_parser/coordinate_parser.test.cpp"

void runTests() {
    FrameworkTest frameworkTest;

    Line line("line", QList<Coordinate>{Coordinate(0,0), Coordinate(1,1)});
    ObjectTest objectTest(&line);

    Clipper clipper;
    ClipperTest clipperTest(&clipper);

    CoordinateParser coordinateParser;
    CoordinateParserTest coordinateParserTest(&coordinateParser);

    frameworkTest.registerTest(&objectTest);
    frameworkTest.registerTest(&clipperTest);
    frameworkTest.registerTest(&coordinateParserTest);
    frameworkTest.run();
}
