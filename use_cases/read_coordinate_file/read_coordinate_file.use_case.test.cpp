#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "read_coordinate_file.use_case.h"

class ReadCoordinateFileUseCaseTest : public TestSuite {
private:
    ReadCoordinateFileUseCase* useCase;

public:
     ReadCoordinateFileUseCaseTest(ReadCoordinateFileUseCase* useCase) : TestSuite() {
        this->useCase = useCase;
    }

    void run()
    {
        cout << "-----------------------" << endl;
        cout << "Teste de ReadCoordinateFileUseCase" << endl;
         cout << "-----------------------" << endl;  

        this->shouldReturnPointOnXAxis();
    }

    void shouldReturnPointOnXAxis() {
        // string filename = "C:\\Users\\fotos\\OneDrive\\Documentos\\Costas\\projeto-cg-bcc\\data\\example\\example.txt";
        string filename = "C:\\Users\\fotos\\OneDrive\\Documentos\\Costas\\projeto-cg-bcc\\data\\psyduck\\psyduck.obj";

        Coordinate expectedValue(1.0, 20.0, 300.0);

        QList<Object*> result = this->useCase->execute(filename);

        // FrameworkTest::expectToBeEqual(
        //     "A coordenada criada deve ser (1.0, 20.0, 300.0)",
        //     result,
        //     expectedValue
        // );
    }
};