#include "../../core/entities/object.h"
#include "../../core/entities/border.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "../../tests/object_test.h"

class CoordinateParserTest : public TestSuite {
private:
    CoordinateParser* parser;

public:
     CoordinateParserTest(CoordinateParser* parser) : TestSuite() {
        this->parser = parser;
    }

    void run()
    {
        this->shouldReturnPointOnXAxis();
        this->shouldReturnPointOnYAxis();
        this->shouldReturnPointOnZAxis();

        this->shouldReturnPointOnPlaneXY();
        this->shouldReturnPointOnPlaneXZ();
        this->shouldReturnPointOnPlaneYZ();

        this->shouldReturnPointOn3DSpace();
    }

    void shouldReturnPointOnXAxis() {
        string line = "100.0 0.0 0.0";
        
        Coordinate expectedValue(100.0, 0.0, 0.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo X deve ser igual a 100.0",
            result.x
            expectedValue.x,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Y deve ser igual a 0.0",
            result.y
            expectedValue.y,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Z deve ser igual a 0.0",
            result.z
            expectedValue.z,
        );
    }

    void shouldReturnPointOnYAxis() {
        string line = "0.0 200.0 0.0";
        
        Coordinate expectedValue(0.0, 200.0, 0.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo X deve ser igual a 0.0",
            result.x
            expectedValue.x,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Y deve ser igual a 200.0",
            result.y
            expectedValue.y,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Z deve ser igual a 0.0",
            result.z
            expectedValue.z,
        );
    }

    void shouldReturnPointOnZAxis() {
        string line = "0.0 0.0 300.0";
        
        Coordinate expectedValue(0.0, 0.0, 300.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo X deve ser igual a 0.0",
            result.x
            expectedValue.x,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Y deve ser igual a 0.0",
            result.y
            expectedValue.y,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Z deve ser igual a 300.0",
            result.z
            expectedValue.z,
        );
    }

    void shouldReturnPointOnPlaneXY() {
        string line = "400.0 500.0 0.0";
        
        Coordinate expectedValue(400.0, 500.0, 0.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo X deve ser igual a 400.0",
            result.x
            expectedValue.x,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Y deve ser igual a 500.0",
            result.y
            expectedValue.y,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Z deve ser igual a 0.0",
            result.z
            expectedValue.z,
        );
    }

    void shouldReturnPointOnPlaneXZ() {
        string line = "600.0 0.0 700.0";
        
        Coordinate expectedValue(600.0, 0.0, 700.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo X deve ser igual a 600.0",
            result.x
            expectedValue.x,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Y deve ser igual a 0.0",
            result.y
            expectedValue.y,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Z deve ser igual a 700.0",
            result.z
            expectedValue.z,
        );
    }

    void shouldReturnPointOnPlaneYZ() {
        string line = "0.0 800.0 900.0";
        
        Coordinate expectedValue(0.0, 800.0, 900.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo X deve ser igual a 0.0",
            result.x
            expectedValue.x,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Y deve ser igual a 800.0",
            result.y
            expectedValue.y,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Z deve ser igual a 900.0",
            result.z
            expectedValue.z,
        );
    }

    void shouldReturnPointOn3DSpace() {
        string line = "1000.0 2000.0 3000.0";
        
        Coordinate expectedValue(1000.0, 2000.0, 3000.0);

        Coordinate result = this->parser->parse(line);

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo X deve ser igual a 1000.0",
            result.x
            expectedValue.x,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Y deve ser igual a 2000.0",
            result.y
            expectedValue.y,
        );

        FrameworkTest::expectToBeEqual(
            "Valor da coordenada no eixo Z deve ser igual a 3000.0",
            result.z
            expectedValue.z,
        );
    }
}