#include <QList>
#include <iostream>


#include "read_coordinate_file.use_case.h"

QList<Object*> ReadCoordinateFileUseCase::execute(string filename)
{
    QList<Object*> list;
    QList<Coordinate> points;
    try {
        this->reader->open(filename);

        if (!this->reader->isOpen())
        {
            throw runtime_error("Não foi possível abrir o arquivo " + filename);
        }

        int objectIndex;
        this->reader->readLinesWithCallback(
            [
                this,
                &list,
                &points,
                &objectIndex
            ]
            (string line, bool isEOF) 
            {
                if (sscanf(line.c_str(), "o Object.%d", &objectIndex) && objectIndex > 1)
                {
                    list.append(
                        new Polygon(
                            QString("Pokemon Part " + objectIndex - 1),
                            QList(points),
                            Qt::white
                        )
                    );
                    points.clear();
                    return;
                }

                if(isEOF)
                {
                    list.append(
                        new Polygon(
                            QString("Pokemon Part " + objectIndex),
                            QList(points),
                            Qt::white
                        )
                    );
                    points.clear();
                    return;
                }
                
                if(this->coordinateParser->isParsable(line))
                {
                    Coordinate point = this->coordinateParser->parse(line);
                    points.append(point);
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
