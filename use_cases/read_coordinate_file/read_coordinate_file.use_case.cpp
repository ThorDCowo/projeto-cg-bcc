#include "read_coordinate_file.use_case.h"
#include <QColor>

using namespace std;

QList<Object*> ReadCoordinateFileUseCase::execute(QString filename)
{
    QList<Object*> list;
    QList<Coordinate> points;
    QList<pair<int, int>> edges;
    try {
        this->reader->open(filename);

        if (!this->reader->isOpen())
        {
            throw runtime_error("Não foi possível abrir o arquivo " );
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
                    cout << line << endl;
                    list.append(
                        new Polygon(
                            QString(" pokemon Parte "),
                            QList(points),
                            QList(edges),
                            Qt::red
                        )
                    );
                    points.clear();
                    edges.clear();
                    return;
                }

                if(this->coordinateParser->isParsable(line))
                {
                    // cout << "Ponto: " << line << endl;
                    points.append(this->coordinateParser->parse(line));
                    // return;
                }

                if(this->faceParser->isParsableWithTexture(line))
                {
                    // cout << "Face: " << line << endl;
                    Face face = this->faceParser->parseWithTexture(line);
                    edges.append({face.v1, face.v2});
                    edges.append({face.v2, face.v3});
                    edges.append({face.v3, face.v1});
                    
                    // return;
                }

                if(this->faceParser->isParsableWithoutTexture(line))
                {
                    // cout << "Face: " << line << endl;
                    Face face = this->faceParser->parseWithoutTexture(line);
                    edges.append({face.v1, face.v2});
                    edges.append({face.v2, face.v3});
                    edges.append({face.v3, face.v1});
                    
                    // return;
                }

                if(isEOF)
                {
                    cout << "Fim do arquivo" << endl;
                    cout << "objeto: " << to_string(objectIndex - 1) << "#" << endl;
                    list.append(
                        new Polygon(
                            QString("Pokemon Part"),
                            QList(points),
                            QList(edges),
                            Qt::red
                        )
                    );
                    cout << "PointsSize: " << points.size() << endl;
                    cout << "EdgesSize: " << edges.size() << endl;

                    points.clear();
                    edges.clear();
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