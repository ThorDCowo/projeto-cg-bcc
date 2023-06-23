#include "../../data/entities/object.h"
#include "../../data/entities/border.h"
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

        this->shouldReturnValidFaceWithTexture();
        this->shouldValidateLineWithTexture();
        this->shouldInvalidateLineMissingTokenWithTexture();
        this->shouldInvalidateLineWithWrongTokenWithTexture();
        this->shouldInvalidateLineWithWrongFormatTokenWithTexture();

        this->shouldReturnValidFaceWithoutTexture();
        this->shouldValidateLineWithoutTexture();
        this->shouldInvalidateLineMissingTokenWithoutTexture();
        this->shouldInvalidateLineWithWrongTokenWithoutTexture();
        this->shouldInvalidateLineWithWrongFormatTokenWithoutTexture();
    }

    void shouldReturnValidFaceWithTexture() {
        string line = "f 180/151 181/148 178/150";
        
        int v1 = 180;
        int v2 = 181;
        int v3 = 178;

        Face resultFace = this->parser->parseWithTexture(line);
        Face expectedFace = Face(v1, v2, v3);

        FrameworkTest::expectToBeEqual(
            "Deve retornar uma face com os valores válidos para v1, v2 e v3",
            resultFace,
            expectedFace
        );
    }

    void shouldValidateLineWithTexture() {
        string line = "f 180/151 181/148 178/150";
        bool result = this->parser->isParsableWithTexture(line);

        FrameworkTest::expectToBeTrue(
            "Deve validar linha no fomarto 'f v1/vt1 v2/vt2 v3/vt3'",
            result
        );
    }

    void shouldInvalidateLineMissingTokenWithTexture() {
        string line = "180/151 181/148 178/150";
        bool result = this->parser->isParsableWithTexture(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha que não começa com 'f'",
            result
        );
    }

    void shouldInvalidateLineWithWrongTokenWithTexture() {
        string line = "vt 180/151 181/148 178/150";
        bool result = this->parser->isParsableWithTexture(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha que não começa caracter diferente de 'f'",
            result
        );
    }

    void shouldInvalidateLineWithWrongFormatTokenWithTexture() {
        string line = "vt 180-151 181-148 178/150";
        bool result = this->parser->isParsableWithTexture(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha fora do formato 'f v1/vt1 v2/vt2 v3/vt3'",
            result
        );
    }

    void shouldReturnValidFaceWithoutTexture() {
        string line = "f 180 181 178";
        
        int v1 = 180;
        int v2 = 181;
        int v3 = 178;

        Face resultFace = this->parser->parseWithoutTexture(line);
        Face expectedFace = Face(v1, v2, v3);

        FrameworkTest::expectToBeEqual(
            "Deve retornar uma face com os valores válidos para v1, v2 e v3",
            resultFace,
            expectedFace
        );
    }

    void shouldValidateLineWithoutTexture() {
        string line = "f 180 181 178";
        bool result = this->parser->isParsableWithoutTexture(line);

        FrameworkTest::expectToBeTrue(
            "Deve validar linha no formato 'f v1 v2 v3'",
            result
        );
    }

    void shouldInvalidateLineMissingTokenWithoutTexture() {
        string line = "180 181 178";
        bool result = this->parser->isParsableWithoutTexture(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha que não começa com 'f'",
            result
        );
    }

    void shouldInvalidateLineWithWrongTokenWithoutTexture() {
        string line = "vt 180 181 178";
        bool result = this->parser->isParsableWithoutTexture(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha que não começa caracter diferente de 'f'",
            result
        );
    }

    void shouldInvalidateLineWithWrongFormatTokenWithoutTexture() {
        string line = "vt 180 181 178";
        bool result = this->parser->isParsableWithoutTexture(line);

        FrameworkTest::expectToBeFalse(
            "Deve invalidar linha fora do formato 'f v1 v2 v3'",
            result
        );
    }
};