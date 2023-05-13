#include "clipper.h"

void Clipper::pointClipping(
    Border border,
    QList<pair<float,float>>* pointsList
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
    QList<pair<float, float>>* pointsList
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
    QList<pair<float, float>>* pointsList
) 
{
    qsizetype regionCodeFirstIndex = 0;
    qsizetype regionCodeSecondIndex = 1;

    QList<vector<bool>> regionCodeList = generateRegionCodeList(
        border,
        (*pointsList)[pointOneIndex],
        (*pointsList)[pointTwoIndex]
    );

    cout << "border upper: " << border.getUpper() << endl;
    cout << "border lower: " << border.getLower() << endl;
    cout << "border left: " << border.getLeft() << endl;
    cout << "border right: " << border.getRight() << endl;

    cout << "pointOneIndex: " << pointOneIndex << endl;
    cout << "pointTwoIndex: " << pointTwoIndex << endl;

    debugRegionCodes(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex]);

    if (isLineFullyInsideWindow(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex])) 
        return;

    if (isLineFullyOutsideWindow(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex]))
    {
        cout << "Index: " << pointOneIndex << " " << pointTwoIndex << endl;
        cout << pointsList->size() << endl;
        pointsList->removeAt(pointTwoIndex);
        pointsList->removeAt(pointOneIndex);
        return;
    }

    //Ou aceita (atualiza) ambos os pontos ou nao aceita nada remove ambos
    if(isLineFullyDiagonal(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex])){
        pair <float, float> control = (*pointsList)[pointOneIndex];
        cout << "Fully Diagonal" << endl;
        (*pointsList)[pointOneIndex] = diagonalClipping(
            border,
            (*pointsList)[pointTwoIndex],
            (*pointsList)[pointOneIndex]
        );
        if(control == (*pointsList)[pointOneIndex]){
            cout << "Removendo linha diagonal" << endl;
            pointsList->removeAt(pointTwoIndex);
            pointsList->removeAt(pointOneIndex);
            return;
        }
        cout << "Second Point" << endl;
        (*pointsList)[pointTwoIndex] = diagonalClipping(
            border,
            (*pointsList)[pointOneIndex],
            (*pointsList)[pointTwoIndex]
        );
        return;
    }

    if(hasTwoRegionCodeTruly(regionCodeList[regionCodeFirstIndex])){
        pair <float, float> control = (*pointsList)[pointOneIndex];
        (*pointsList)[pointOneIndex] = diagonalClipping(
            border,
            (*pointsList)[pointTwoIndex],
            (*pointsList)[pointOneIndex]
        );

        if(control == (*pointsList)[pointOneIndex]){
            cout << "Edging 1" << endl;
            pointsList->removeAt(pointOneIndex);
            return;
        }
    }

    if(hasTwoRegionCodeTruly(regionCodeList[regionCodeSecondIndex])){
        pair <float, float> control = (*pointsList)[pointTwoIndex];
        (*pointsList)[pointTwoIndex] = diagonalClipping(
            border,
            (*pointsList)[pointOneIndex],
            (*pointsList)[pointTwoIndex]
        );

        if(control == (*pointsList)[pointTwoIndex]){            
            cout << "Edging 2" << endl;
            pointsList->removeAt(pointTwoIndex);
            return;
        }
    }

    if(hasSomeRegionCodeTruly(regionCodeList[regionCodeFirstIndex])){
        pair <float, float> aux = (*pointsList)[pointOneIndex];
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

    pair <float, float> aux = (*pointsList)[pointTwoIndex];
    (*pointsList)[pointTwoIndex] = parallelToAxisClipping(
        border,
        (*pointsList)[pointOneIndex],
        (*pointsList)[pointTwoIndex]
    );
}

QList<vector<bool>> Clipper::generateRegionCodeList(
    Border border, 
    pair<float, float> pointOne,
    pair<float, float> pointTwo
)
{    
    QList<vector<bool>> regionCodeList;

    regionCodeList.append(generateRegionCode(border, pointOne));
    regionCodeList.append(generateRegionCode(border, pointTwo));

    return regionCodeList;
}

vector<bool> Clipper::generateRegionCode(
    Border border,
    pair<float, float> point
)
{
    vector<bool> regionCode;
    regionCode.assign(4, 0);

    regionCode.at(0) = point.second > border.getUpper();
    regionCode.at(1) = point.second < border.getLower();
    regionCode.at(2) = point.first > border.getRight();
    regionCode.at(3) = point.first < border.getLeft();

    return regionCode;
}

void Clipper::debugRegionCodes(
    vector<bool> pointOneRegionCode, 
    vector<bool> pointTwoRegionCode
) {
    cout << " \n Analise do RC" << endl; 
    cout << "P1: " << pointOneRegionCode[0] << " " << pointOneRegionCode[1] << " " << pointOneRegionCode[2] << " " << pointOneRegionCode[3] << endl;
    cout << "P2: " << pointTwoRegionCode[0] << " " << pointTwoRegionCode[1] << " " << pointTwoRegionCode[2] << " " << pointTwoRegionCode[3] << endl;
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


pair<float, float> Clipper::parallelToAxisClipping(
    Border border, 
    pair<float, float> insidePoint, 
    pair<float, float> outsidePoint
)
{
    cout << "Vertical or Horizontal Clipping " << endl;
    float angularCoefficient = (
        (insidePoint.second - outsidePoint.second) /
        (insidePoint.first - outsidePoint.first)
    );

    if (outsidePoint.second > border.getUpper())
        return clippingAbove(border,  outsidePoint, angularCoefficient);

    if (outsidePoint.second < border.getLower())
        return clippingBelow(border, outsidePoint, angularCoefficient);

    if (outsidePoint.first > border.getRight())
        return clippingRight(border, outsidePoint, angularCoefficient);

    
    return clippingLeft(border, outsidePoint, angularCoefficient);
};

pair<float, float> Clipper:: diagonalClipping(   
    Border border, 
    pair<float, float> insidePoint, 
    pair<float, float> outsidePoint
)
{
    cout << "Diagonal Clipping " << endl;
    pair <float, float> control = outsidePoint;

    float angularCoefficient = (
        (insidePoint.second - outsidePoint.second) /
        (insidePoint.first - outsidePoint.first)
    );

    if (outsidePoint.second > border.getUpper()){
        outsidePoint = clippingAbove(border, outsidePoint, angularCoefficient);
        
        if(control != outsidePoint) return outsidePoint;
    }

    if (outsidePoint.second < border.getLower()){
        outsidePoint = clippingBelow(border, outsidePoint, angularCoefficient);

        if(control != outsidePoint) return outsidePoint;
    }

    if (outsidePoint.first > border.getRight()){
        outsidePoint = clippingRight(border, outsidePoint, angularCoefficient);

        if(control != outsidePoint) return outsidePoint;
    }

    if (outsidePoint.first < border.getLeft())
        return clippingLeft(border, outsidePoint, angularCoefficient);

};

pair<float, float> Clipper::clippingAbove(
    Border border, 
    pair<float, float> outsidePoint,
    float angularCoefficient
)
{
    cout << "Above" << endl;
    float newX = outsidePoint.first + (border.getUpper() - outsidePoint.second) / angularCoefficient;
    pair<float,float> newPoint;

    if (newX >= border.getLeft() && newX <= border.getRight()) {
        cout << "Accepted !" << endl;
        newPoint.first = newX;
        newPoint.second = border.getUpper();
        return newPoint;
    }

    cout << "Not Accepted" << endl;
    return outsidePoint;
}

pair<float, float> Clipper::clippingBelow(
    Border border, 
    pair<float, float> outsidePoint,
    float angularCoefficient
)
{    
    cout << "Below" << endl;
    float newX = outsidePoint.first + (1  / angularCoefficient) * (border.getLower() - outsidePoint.second);
    pair<float,float> newPoint;

    if (newX >= border.getLeft() && newX <= border.getRight()) {
        cout << "Accepted !" << endl;
        newPoint.first = newX;
        newPoint.second = border.getLower();
        return newPoint;
    }

    cout << "Not Accepted" << endl;
    return outsidePoint;
}

pair<float, float> Clipper::clippingRight(
    Border border,  
    pair<float, float> outsidePoint,
    float angularCoefficient
)
{   
    cout << "Right" << endl;
    float newY = angularCoefficient * (border.getRight() - outsidePoint.first) 
        + outsidePoint.second;
    pair<float,float> newPoint;

    if (newY >= border.getLower() && newY <= border.getUpper()) {
        cout << "Accepted !" << endl;
        newPoint.first = border.getRight();
        newPoint.second = newY;
        return newPoint;
    }

    cout << "Not Accepted" << endl;
    return outsidePoint;
}

pair<float, float> Clipper::clippingLeft(
    Border border,  
    pair<float, float> outsidePoint,
    float angularCoefficient
)
{
    cout << "Left" << endl;
    float newY = angularCoefficient * (border.getLeft() - outsidePoint.first) 
        + outsidePoint.second;
    pair<float,float> newPoint;

    if (newY >= border.getLower() && newY <= border.getUpper()) {
        cout << "Accepted !" << endl;
        newPoint.first = border.getLeft();
        newPoint.second = newY;
        return newPoint;
    }

    cout << "Not Accepted" << endl;
    return outsidePoint;
}
