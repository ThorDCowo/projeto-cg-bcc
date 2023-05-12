#include "framework_test.h"
#include "object_test.h"
#include "../line.h"

void runTests() {
    FrameworkTest frameworkTest;

    Line line("line", QList<pair<float,float>>{pair<float,float>(0,0), pair<float,float>(1,1)});
    ObjectTest objectTest(&line);

    frameworkTest.registerTest(&objectTest);
    frameworkTest.run();
}
