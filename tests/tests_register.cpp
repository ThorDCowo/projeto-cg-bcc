#include "framework_test.h"
#include "object_test.h"
#include "../line.h"
#include "../infra/clipper/clipper.test.cpp"

void runTests() {
    FrameworkTest frameworkTest;

    Line line("line", QList<pair<float,float>>{pair<float,float>(0,0), pair<float,float>(1,1)});
    ObjectTest objectTest(&line);

    Clipper clipper;
    ClipperTest clipperTest(&clipper);

    frameworkTest.registerTest(&clipperTest);
    frameworkTest.registerTest(&objectTest);
    frameworkTest.run();
}
