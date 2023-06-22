#include "../../tests/framework_test.h"
#include "../../tests/test_suite.h"
#include "read_coordinate_file.use_case.h"
#include <QList>

class ReadCoordinateFileUseCaseTest : public TestSuite {
private:
    ReadCoordinateFileUseCase* useCase;

public:
     ReadCoordinateFileUseCaseTest(ReadCoordinateFileUseCase* useCase) : TestSuite() {
        this->useCase = useCase;
    }

    void run()
    {
        //cout << "-----------------------" << endl;
        //cout << "Teste de ReadCoordinateFileUseCase" << endl;
        //cout << "-----------------------" << endl;  

        this->shouldReturnOneObjectWithOnePoint();
        this->shouldReturnOneObjectWithThreePoints();
        this->shouldReturnTwoObjectsWithOnePoint();
        this->shouldReturnTwoObjectsWithTwoPoints();
        this->shouldReturnReductedPsyduck();
        // this->shouldReturnObjectListFromFile();
        this->shouldReturnOneObjectWithManyPoints();
    }

    void shouldReturnOneObjectWithOnePoint() {
        string filename = "C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\example\\example_single_point.txt";

        qsizetype expectedValue = 1;

       QList<Object*> result = this->useCase->execute(filename);

        FrameworkTest::expectToBeEqual(
            "Deve retornar 1 objeto",
            result.size(),
            expectedValue
        );
    }

    void shouldReturnOneObjectWithThreePoints() {
        string filename = "C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\example\\example_three_points.txt";

        qsizetype expectedValue = 1;

       QList<Object*> result = this->useCase->execute(filename);

        FrameworkTest::expectToBeEqual(
            "Deve retornar 1 objeto com 3 pontos",
            result.size(),
            expectedValue
        );
    }

    void shouldReturnTwoObjectsWithOnePoint() {
        string filename = "C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\example\\two_objects_single_point.txt";

        qsizetype expectedValue = 2;

        QList<Object*> result = this->useCase->execute(filename);

        FrameworkTest::expectToBeEqual(
            "Deve retornar 2 objetos com um ponto cada um",
            result.size(),
            expectedValue
        );
    }

    void shouldReturnTwoObjectsWithTwoPoints() {
        string filename = "C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\example\\example_two_objects_two_points.txt";

        qsizetype expectedValue = 2;

       QList<Object*> result = this->useCase->execute(filename);

        FrameworkTest::expectToBeEqual(
            "Deve retornar 2 objetos com 2 pontos cada um",
            result.size(),
            expectedValue
        );
    }

    void shouldReturnReductedPsyduck() {
        string filename = "C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\psyduck\\reducted_psyduck.obj";

        qsizetype expectedValue = 1;

       QList<Object*> result = this->useCase->execute(filename);

        FrameworkTest::expectToBeEqual(
            "Deve retornar 1 objeto com psyducky",
            result.size(),
            expectedValue
        );
    }
    
    void shouldReturnObjectListFromFile() {
        string filename = "C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\psyduck\\psyduck.obj";

        qsizetype expectedValue = 10;

       QList<Object*> result = this->useCase->execute(filename);

        FrameworkTest::expectToBeEqual(
            "Deve retornar 10 objetos",
            result.size(),
            expectedValue
        );
    }

    void shouldReturnOneObjectWithManyPoints() {
        string filename = "C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\charizard\\charizard.obj";

        qsizetype expectedValue = 1;

       QList<Object*> result = this->useCase->execute(filename);

        FrameworkTest::expectToBeEqual(
            "Deve retornar 1 objeto com vários pontos",
            result.size(),
            expectedValue
        );
    }
};