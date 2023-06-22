#include "read_coordinate_file.use_case.h"

QList<Object*> ReadCoordinateFileUseCase::execute(string filename)
{
    QList<Object*> list;
    QList<Coordinate> points;
    QList<pair<int, int>> edges;
    try {
        this->reader->open(filename);

        if (!this->reader->isOpen())
        {
            throw runtime_error("Não foi possível abrir o arquivo " + filename);
        }

        int objectIndex = -1;
        this->reader->readLinesWithCallback(
            [
                this,
                &list,
                &points,
                &objectIndex,
                &edges
            ]
            (string line, bool isEOF) 
            {
                if (sscanf(line.c_str(), "o Object.%d", &objectIndex) && objectIndex > 1)
                {
                    cout << "Um novo objeto: " << objectIndex - 1 << "#" << endl;
                    //cout << line << endl;
                    list.append(
                        new Polygon(
                            QString("Pokemon Part " + objectIndex - 1),
                            QList(points),
                            QList(edges),
                            Qt::white
                        )
                    );
                    points.clear();
                    edges.clear();
                    return;
                }

                if(isEOF)
                {
                    cout << "Fim do arquivo" << endl;
                    list.append(
                        new Polygon(
                            QString("Pokemon Part " + objectIndex),
                            QList(points),
                            QList(edges),
                            Qt::white
                        )
                    );
                    points.clear();
                    edges.clear();
                    return;
                }
                
                if(this->coordinateParser->isParsable(line))
                {
                    cout << "Ponto: " << line << endl;
                    points.append(this->coordinateParser->parse(line));
                }

                if(this->faceParser->isParsable(line))
                {
                    cout << "Face: " << line << endl;
                    Face face = this->faceParser->parse(line);
                    edges.append({face.v1, face.v2});
                    edges.append({face.v2, face.v3});
                    edges.append({face.v3, face.v1});
                }
            }
        );
    } catch (const exception& e) {
        cout << "Erro ao ler o arquivo: " << e.what() << endl;
        throw;
    }

    this->reader->close();
    return list;
}