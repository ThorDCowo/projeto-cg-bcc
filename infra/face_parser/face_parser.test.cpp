#include "../../core/entities/object.h"
#include "../../core/entities/border.h"
#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "face_parser.h"

class FaceParserTest : public TestSuite {
private:
    FaceParser* parser;

public:
     FaceParserTest(FaceParser* parser) : TestSuite() {
        this->parser = parser;
    }

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste de FaceParser" << endl;
        cout << "-----------------------" << endl;  

        this->shouldReturnValidFace();
        this->shouldValidateLine();
        this->shouldInvalidateLineMissingToken();
        this->shouldInvalidateLineWithWrongToken();
        this->shouldInvalidateLineWithWrongFormatToken();
    }

    void shouldReturnValidFace() {
        string line = "f 180/151 181/148 178/150";
        
        int v1 = 180;
        int v2 = 181;
        int v3 = 178;

        Face resultFace = this->parser->parse(line);
        Face expectedFace = Face(v1, v2, v3);

        FrameworkTest::expectToBeEqual(
            "Deve retornar uma face com os valores válidos para v1, v2 e v3",
            resultFace,
            expectedFace
        );
    }

    void shouldValidateLine() {
        string line = "f 180/151 181/148 178/150";
        bool result = this->parser->isParsable(line);

        FrameworkTest::expectToBeTrue(
            "Deve validar linha no fomarto 'f v1/vt1 v2/vt2 v3/vt3'",
            result
        );
    }

    void shouldInvalidateLineMissingToken() {
        string line = "180/151 181/148 178/150";
        bool result = this->parser->isParsable(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha que não começa com 'f'",
            result
        );
    }

    void shouldInvalidateLineWithWrongToken() {
        string line = "vt 180/151 181/148 178/150";
        bool result = this->parser->isParsable(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha que não começa caracter diferente de 'f'",
            result
        );
    }

    void shouldInvalidateLineWithWrongFormatToken() {
        string line = "vt 180-151 181\148 178/150";
        bool result = this->parser->isParsable(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha fora do formato 'f v1/vt1 v2/vt2 v3/vt3'",
            result
        );
    }
};