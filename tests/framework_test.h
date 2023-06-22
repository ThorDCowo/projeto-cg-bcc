#ifndef FRAMEWORK_TEST_H
#define FRAMEWORK_TEST_H

#include <list>
#include <iostream>
#include <QList>
#include <string>
#include "test_suite.h"
#include "../core/interfaces/comparable.h"


using namespace std;

class FrameworkTest 
{

public:
    bool static expectToBeEqual(string testMessage, float value, float expectedValue);
    bool static expectToBeEqual(string testMessage, qsizetype value, qsizetype expectedValue);
    bool static expectToBeEqual(
        string testMessage,
        pair<qsizetype, qsizetype> value,
        pair<qsizetype, qsizetype> expectedValue
    );
    bool static expectToBeEqual(
        string testMessage,
        Comparable& value,
        Comparable& expectedValue
    );

    bool static expectToBeTrue(string testMessage, bool value);
    bool static expectToBeFalse(string testMessage, bool value);

    void run();
    void registerTest(TestSuite* testSuite);

private:
    list<TestSuite*> testSuites;
};

#endif // FRAMEWORK_TEST_H
