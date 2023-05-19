#include "../../infra/file_reader/file_reader.h"
#include "../../core/entities/coordinate.h"
#include "read_coordinate_file.use_case.h"

Coordinate ReadCoordinateFileUseCase::execute(string filename)
{
    Coordinate output = Coordinate::zero();
    try {
        this->reader->open(filename);
        if (!this->reader->isOpen())
        {
            throw runtime_error("Não foi possível abrir o arquivo " + filename);
        }
        this->reader->readLinesWithCallback([this, &output](const string &line) {
            output = this->coordinateParser->parse(line);
            cout << "Coordenada lida: " << output.toString() << endl;
        });
    } catch (const exception& e) {
        cout << "Erro ao ler o arquivo: " << e.what() << endl;
        throw;
    }
    this->reader->close();
    return output;
}
