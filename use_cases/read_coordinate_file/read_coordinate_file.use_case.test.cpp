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
        string filename = "core/data/example/example.txt";
        
        Coordinate expectedValue(1.0, 20.0, 300.0);

        Coordinate result = this->useCase->execute(filename);

        FrameworkTest::expectToBeEqual(
            "A coordenada criada deve ser (1.0, 20.0, 300.0)",
            result,
            expectedValue
        );
    }
};