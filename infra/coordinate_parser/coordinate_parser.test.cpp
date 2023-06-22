#include "../../core/entities/object.h"
#include "../../core/entities/border.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "coordinate_parser.h"

class CoordinateParserTest : public TestSuite {
private:
    CoordinateParser* parser;

public:
    CoordinateParserTest(CoordinateParser* parser) : TestSuite() {
        this->parser = parser;
    }

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste de CoordinateParser" << endl;
        cout << "-----------------------" << endl;  

        this->shouldReturnPointOnXAxis();
        this->shouldReturnPointOnYAxis();
        this->shouldReturnPointOnZAxis();

        this->shouldReturnPointOnPlaneXY();
        this->shouldReturnPointOnPlaneXZ();
        this->shouldReturnPointOnPlaneYZ();

        this->shouldReturnPointOn3DSpace();
    }

    void shouldReturnPointOnXAxis() {
        string line = "v 100.0 0.0 0.0";
        
        Coordinate expectedValue(100.0, 0.0, 0.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "A coordenada criada deve ser (100.0, 0.0, 0.0)",
            result,
            expectedValue
        );
    }

    void shouldReturnPointOnYAxis() {
        string line = "v 0.0 200.0 0.0";
        
        Coordinate expectedValue(0.0, 200.0, 0.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "A coordenada criada deve ser (0.0, 200.0, 0.0)",
            result,
            expectedValue
        );        
    }

    void shouldReturnPointOnZAxis() {
        string line = "v 0.0 0.0 300.0";
        
        Coordinate expectedValue(0.0, 0.0, 300.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "A coordenada criada deve ser (0.0, 0.0, 300.0)",
            result,
            expectedValue
        );
    }

    void shouldReturnPointOnPlaneXY() {
        string line = "v 400.0 500.0 0.0";
        
        Coordinate expectedValue(400.0, 500.0, 0.0);

        Coordinate result = this->parser->parse(line);
        
        FrameworkTest::expectToBeEqual(
            "A coordenada criada deve ser (400.0, 500.0, 0.0)",
            result,
            expectedValue
        );
    }

    void shouldReturnPointOnPlaneXZ() {
        string line = "v 600.0 0.0 700.0";
        
        Coordinate expectedValue(600.0, 0.0, 700.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "A coordenada criada deve ser (600.0, 0.0, 700.0)",
            result,
            expectedValue
        );
    }

    void shouldReturnPointOnPlaneYZ() {
        string line = "v 0.0 800.0 900.0";
        
        Coordinate expectedValue(0.0, 800.0, 900.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "A coordenada criada deve ser (0.0, 800.0, 900.0)",
            result,
            expectedValue
        );
    }

    void shouldReturnPointOn3DSpace() {
        string line = "v 1000.0 2000.0 3000.0";
        
        Coordinate expectedValue(1000.0, 2000.0, 3000.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "A coordenada criada deve ser (1000.0, 2000.0, 3000.0)",
            result,
            expectedValue
        );
    }
};