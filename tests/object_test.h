#ifndef OBJECT_TEST_H
#define OBJECT_TEST_H

#include "../object.h"
#include "test_suite.h"

class ObjectTest : public TestSuite
{    
    
private:
    Object* objectForTest;
        
public: 
    ObjectTest(Object* _objectForTest) : TestSuite() {
        this->objectForTest = _objectForTest;
    }
    

    void linearInterpolationTest(
        const char* testMessage,
        float expectedValue,
        float x,
        float x0,
        float x1,
        float y0,
        float y1
    );

    void interpolateTest1();
    void interpolateTest2();
    void interpolateTest3();
    void run();
      
    
};

#endif // OBJECT_TEST_H