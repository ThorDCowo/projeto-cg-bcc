#include "clipper.h"

void Clipper::pointClipping(
    Border border,
    QList<Coordinate>* pointsList
) 
{
    vector<bool> regionCode = generateRegionCode(
        border,
        (*pointsList)[0]
    );

    if (isPointInsideWindow(regionCode)) return;

    pointsList->removeAt(0);
}

void Clipper::polygonClipping(
    Border border,
    QList<Coordinate>* pointsList
) 
{    
    for (qsizetype i = 0; i < pointsList->size(); i++)
    {        
        if (i == pointsList->size() - 1)
        {
            lineClipping(border, i, 0, pointsList);
            break;           
        }

        lineClipping(border, i, i + 1, pointsList);
    }
}

void Clipper::lineClipping(
    Border border,
    qsizetype pointOneIndex,
    qsizetype pointTwoIndex,
    QList<Coordinate>* pointsList
) 
{
    qsizetype regionCodeFirstIndex = 0;
    qsizetype regionCodeSecondIndex = 1;

    QList<vector<bool>> regionCodeList = generateRegionCodeList(
        border,
        (*pointsList)[pointOneIndex],
        (*pointsList)[pointTwoIndex]
    );

    // //cout << "border upper: " << border.getUpper() << endl;
    // //cout << "border lower: " << border.getLower() << endl;
    // //cout << "border left: " << border.getLeft() << endl;
    // //cout << "border right: " << border.getRight() << endl;

    // //cout << "pointOneIndex: " << pointOneIndex << endl;
    // //cout << "pointTwoIndex: " << pointTwoIndex << endl;

    // debugRegionCodes(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex]);

    if (isLineFullyInsideWindow(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex])) 
        return;

    if (isLineFullyOutsideWindow(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex]))
    {
        //cout << "Index: " << pointOneIndex << " " << pointTwoIndex << endl;
        //cout << pointsList->size() << endl;
        pointsList->removeAt(pointTwoIndex);
        pointsList->removeAt(pointOneIndex);
        return;
    }

    //Ou aceita (atualiza) ambos os pontos ou nao aceita nada remove ambos
    if(isLineFullyDiagonal(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex])){
        Coordinate control = (*pointsList)[pointOneIndex];
        //cout << "Fully Diagonal" << endl;
        (*pointsList)[pointOneIndex] = diagonalClipping(
            border,
            (*pointsList)[pointTwoIndex],
            (*pointsList)[pointOneIndex]
        );
        if(control == (*pointsList)[pointOneIndex]){
            //cout << "Removendo linha diagonal" << endl;
            pointsList->removeAt(pointTwoIndex);
            pointsList->removeAt(pointOneIndex);
            return;
        }
        //cout << "Second Point" << endl;
        (*pointsList)[pointTwoIndex] = diagonalClipping(
            border,
            (*pointsList)[pointOneIndex],
            (*pointsList)[pointTwoIndex]
        );
        return;
    }

    if(hasTwoRegionCodeTruly(regionCodeList[regionCodeFirstIndex])){
        Coordinate control = (*pointsList)[pointOneIndex];
        (*pointsList)[pointOneIndex] = diagonalClipping(
            border,
            (*pointsList)[pointTwoIndex],
            (*pointsList)[pointOneIndex]
        );

        if(control == (*pointsList)[pointOneIndex]){
            //cout << "Edging 1" << endl;
            pointsList->removeAt(pointOneIndex);
            return;
        }
    }

    if(hasTwoRegionCodeTruly(regionCodeList[regionCodeSecondIndex])){
        Coordinate control = (*pointsList)[pointTwoIndex];
        (*pointsList)[pointTwoIndex] = diagonalClipping(
            border,
            (*pointsList)[pointOneIndex],
            (*pointsList)[pointTwoIndex]
        );

        if(control == (*pointsList)[pointTwoIndex]){            
            //cout << "Edging 2" << endl;
            pointsList->removeAt(pointTwoIndex);
            return;
        }
    }

    if(hasSomeRegionCodeTruly(regionCodeList[regionCodeFirstIndex])){
        Coordinate aux = (*pointsList)[pointOneIndex];
        (*pointsList)[pointOneIndex] = parallelToAxisClipping(
            border,
            (*pointsList)[pointTwoIndex],
            (*pointsList)[pointOneIndex]
        );
        if(aux == (*pointsList)[pointOneIndex]){
            pointsList->removeAt(pointTwoIndex);
            pointsList->removeAt(pointOneIndex);
            return;
        }
    }

    (*pointsList)[pointTwoIndex] = parallelToAxisClipping(
        border,
        (*pointsList)[pointOneIndex],
        (*pointsList)[pointTwoIndex]
    );
}

QList<vector<bool>> Clipper::generateRegionCodeList(
    Border border, 
    Coordinate pointOne,
    Coordinate pointTwo
)
{    
    QList<vector<bool>> regionCodeList;

    regionCodeList.append(generateRegionCode(border, pointOne));
    regionCodeList.append(generateRegionCode(border, pointTwo));

    return regionCodeList;
}

vector<bool> Clipper::generateRegionCode(
    Border border,
    Coordinate point
)
{
    vector<bool> regionCode;
    regionCode.assign(4, 0);
    // cout << "point: " << point.x << " " << point.y << endl;

    regionCode.at(0) = point.y > border.getUpper();
    regionCode.at(1) = point.y < border.getLower();
    regionCode.at(2) = point.x > border.getRight();
    regionCode.at(3) = point.x < border.getLeft();

    // //cout << "regioncodes: " << endl;
    // //cout << regionCode.at(0) << endl;
    // //cout << regionCode.at(1) << endl;
    // //cout << regionCode.at(2) << endl;
    // //cout << regionCode.at(3) << endl;
    return regionCode;
}

void Clipper::debugRegionCodes(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    //cout << " \n Analise do RC" << endl; 
    //cout << "P1: " << pointOneRegionCode[0] << " " << pointOneRegionCode[1] << " " << pointOneRegionCode[2] << " " << pointOneRegionCode[3] << endl;
    //cout << "P2: " << pointTwoRegionCode[0] << " " << pointTwoRegionCode[1] << " " << pointTwoRegionCode[2] << " " << pointTwoRegionCode[3] << endl;
}

// Totalmente dentro da window RC de pi & p2 == 0 0 0 0
bool Clipper::isLineFullyInsideWindow(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    return (
        isPointInsideWindow(pointOneRegionCode) &&
        isPointInsideWindow(pointTwoRegionCode)
    );
}

bool Clipper::isPointInsideWindow(vector<bool> pointRegionCode) {
    return (
        !pointRegionCode[0] &&
        !pointRegionCode[1] &&
        !pointRegionCode[2] &&
        !pointRegionCode[3]
    );
}

// Totalmente fora da window RC de p1 & p2 != 0 0 0 0
bool Clipper::isLineFullyOutsideWindow(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    return (
        (pointOneRegionCode[0] && pointTwoRegionCode[0]) ||
        (pointOneRegionCode[1] && pointTwoRegionCode[1]) ||
        (pointOneRegionCode[2] && pointTwoRegionCode[2]) ||
        (pointOneRegionCode[3] && pointTwoRegionCode[3])
    );
}

// Corta a Window Diagonalmente
bool Clipper::isLineFullyDiagonal(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    return (
        (pointOneRegionCode[0] || pointTwoRegionCode[0]) &&
        (pointOneRegionCode[1] || pointTwoRegionCode[1]) &&
        (pointOneRegionCode[2] || pointTwoRegionCode[2]) &&
        (pointOneRegionCode[3] || pointTwoRegionCode[3])
    );
}

bool Clipper::hasTwoRegionCodeTruly(vector<bool> regionCode) {
    return (
        (regionCode[0] || regionCode[1] ) &&
        (regionCode[2] || regionCode[3] )
    );
}

bool Clipper::hasSomeRegionCodeTruly(vector<bool> regionCode) {
    return (
        regionCode[0] ||
        regionCode[1] ||
        regionCode[2] ||
        regionCode[3]
    );
}


Coordinate Clipper::parallelToAxisClipping(
    Border border, 
    Coordinate insidePoint, 
    Coordinate outsidePoint
)
{
    // //cout << "Vertical or Horizontal Clipping " << endl;
    float angularCoefficient = (
        (insidePoint.y - outsidePoint.y) /
        (insidePoint.x - outsidePoint.x)
    );

    if (outsidePoint.y > border.getUpper())
        return clippingAbove(border,  outsidePoint, angularCoefficient);

    if (outsidePoint.y < border.getLower())
        return clippingBelow(border, outsidePoint, angularCoefficient);

    if (outsidePoint.x > border.getRight())
        return clippingRight(border, outsidePoint, angularCoefficient);

    
    return clippingLeft(border, outsidePoint, angularCoefficient);
};

Coordinate Clipper:: diagonalClipping(   
    Border border, 
    Coordinate insidePoint, 
    Coordinate outsidePoint
)
{
    // //cout << "Diagonal Clipping " << endl;
    Coordinate control = outsidePoint;

    float angularCoefficient = (
        (insidePoint.y - outsidePoint.y) /
        (insidePoint.x - outsidePoint.x)
    );

    if (outsidePoint.y > border.getUpper()){
        outsidePoint = clippingAbove(border, outsidePoint, angularCoefficient);
        
        if(control != outsidePoint) return outsidePoint;
    }

    if (outsidePoint.y < border.getLower()){
        outsidePoint = clippingBelow(border, outsidePoint, angularCoefficient);

        if(control != outsidePoint) return outsidePoint;
    }

    if (outsidePoint.x > border.getRight()){
        outsidePoint = clippingRight(border, outsidePoint, angularCoefficient);

        if(control != outsidePoint) return outsidePoint;
    }

    return clippingLeft(border, outsidePoint, angularCoefficient);

};

Coordinate Clipper::clippingAbove(
    Border border, 
    Coordinate outsidePoint,
    float angularCoefficient
)
{
    //cout << "Above" << endl;
    float newX = outsidePoint.x + (border.getUpper() - outsidePoint.y) / angularCoefficient;
    Coordinate newPoint = outsidePoint;

    if (newX >= border.getLeft() && newX <= border.getRight()) {
        //cout << "Accepted !" << endl;
        newPoint.x = newX;
        newPoint.y = border.getUpper();
        newPoint.z = outsidePoint.z;
        return newPoint;
    }

    //cout << "Not Accepted" << endl;
    return outsidePoint;
}

Coordinate Clipper::clippingBelow(
    Border border, 
    Coordinate outsidePoint,
    float angularCoefficient
)
{    
    //cout << "Below" << endl;
    float newX = outsidePoint.x + (1  / angularCoefficient) * (border.getLower() - outsidePoint.y);
    Coordinate newPoint = outsidePoint;

    if (newX >= border.getLeft() && newX <= border.getRight()) {
        //cout << "Accepted !" << endl;
        newPoint.x = newX;
        newPoint.y = border.getLower();
        newPoint.z = outsidePoint.z;
        return newPoint;
    }

    //cout << "Not Accepted" << endl;
    return outsidePoint;
}

Coordinate Clipper::clippingRight(
    Border border,  
    Coordinate outsidePoint,
    float angularCoefficient
)
{   
    //cout << "Right" << endl;
    float newY = angularCoefficient * (border.getRight() - outsidePoint.x) 
        + outsidePoint.y;
    Coordinate newPoint = outsidePoint;

    if (newY >= border.getLower() && newY <= border.getUpper()) {
        //cout << "Accepted !" << endl;
        newPoint.x = border.getRight();
        newPoint.y = newY;
        newPoint.z = outsidePoint.z;
        return newPoint;
    }

    //cout << "Not Accepted" << endl;
    return outsidePoint;
}

Coordinate Clipper::clippingLeft(
    Border border,  
    Coordinate outsidePoint,
    float angularCoefficient
)
{
    //cout << "Left" << endl;
    float newY = angularCoefficient * (border.getLeft() - outsidePoint.x) 
        + outsidePoint.y;
    Coordinate newPoint = outsidePoint;

    if (newY >= border.getLower() && newY <= border.getUpper()) {
        //cout << "Accepted !" << endl;
        newPoint.x = border.getLeft();
        newPoint.y = newY;
        newPoint.z = outsidePoint.z;
        return newPoint;
    }

    //cout << "Not Accepted" << endl;
    return outsidePoint;
}
