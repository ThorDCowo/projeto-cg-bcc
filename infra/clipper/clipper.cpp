#include "clipper.h"

void Clipper::pointClipping(
    Border border,
    QList<Coordinate>* normalizedPointsList,
    QList<pair<int,int>>* edgesListToDraw,
    QList<Coordinate>* pointsListToDraw
) 
{
    vector<bool> regionCode = generateRegionCode(
        border,
        (*normalizedPointsList)[0]
    );

    if (!isPointInsideWindow(regionCode)) return;

    pair<int,int> edgeToDraw;

    pointsListToDraw->append((*normalizedPointsList)[0]);
    edgeToDraw.first = pointsListToDraw->size() - 1;
    edgeToDraw.second = pointsListToDraw->size() - 1;

    edgesListToDraw->append(edgeToDraw);
}

void Clipper::polygonClipping(
    Border border,
    QList<Coordinate>* normalizedPointsList,
    QList<pair<int,int>>* edgesList,
    QList<pair<int,int>>* edgesListToDraw,
    QList<Coordinate>* pointsListToDraw
) 
{   

    for (qsizetype i = 0; i < edgesList->size(); i++){    
        lineClipping(
            border,
            (*edgesList)[i],
            normalizedPointsList,
            edgesListToDraw,
            pointsListToDraw
        );
        
    }
}

void Clipper::lineClipping(
    Border border, 
    pair<int,int> edge,
    QList<Coordinate>* normalizedPointsList,
    QList<pair<int,int>>* edgesListToDraw,
    QList<Coordinate>* pointsListToDraw
) 
{
    int regionCodeFirstIndex = 0;
    int regionCodeSecondIndex = 1;

    QList<vector<bool>> regionCodeList = generateRegionCodeList(
        border,
        (*normalizedPointsList)[edge.first],
        (*normalizedPointsList)[edge.second]
    );

    // //cout << "border upper: " << border.getUpper() << endl;
    // //cout << "border lower: " << border.getLower() << endl;
    // //cout << "border left: " << border.getLeft() << endl;
    // //cout << "border right: " << border.getRight() << endl;

    // //cout << "edge.first: " << edge.first << endl;
    // //cout << "edge.second: " << edge.second << endl;

    // debugRegionCodes(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex]);

    if (isLineFullyInsideWindow(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex])) {        
        appendToNewLists(
            (*normalizedPointsList)[edge.first],
            (*normalizedPointsList)[edge.second],
            edgesListToDraw,
            pointsListToDraw
        );
        return;
    }

    if (isLineFullyOutsideWindow(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex]))
    {
        //cout << "Index: " << edge.first << " " << edge.second << endl;
        //cout << normalizedPointsList->size() << endl;
        //Remover a Aresta
        // normalizedPointsList->removeAt(edge.second);
        // normalizedPointsList->removeAt(edge.first);
        return;
    }

    
    if(isLineFullyDiagonal(regionCodeList[regionCodeFirstIndex], regionCodeList[regionCodeSecondIndex])){
        //(atualiza) ambos os pontos e adiciona na 
        Coordinate control = (*normalizedPointsList)[edge.first];
        //cout << "Fully Diagonal" << endl;
        Coordinate pointOne = diagonalClipping(
            border,
            (*normalizedPointsList)[edge.second],
            (*normalizedPointsList)[edge.first]
        );
        if(control == pointOne){
            //cout << "Removendo linha diagonal" << endl;
            // pointsList->removeAt(pointTwoIndex);
            // pointsList->removeAt(pointOneIndex);
            return;
        }
        //cout << "Second Point" << endl;
        Coordinate pointTwo = diagonalClipping(
            border,
            (*normalizedPointsList)[edge.first],
            (*normalizedPointsList)[edge.second]
        );

        appendToNewLists(
            pointOne,
            pointTwo,
            edgesListToDraw,
            pointsListToDraw
        );
        return;
    }

    if(hasTwoRegionCodeTruly(regionCodeList[regionCodeFirstIndex])){
        Coordinate control = (*normalizedPointsList)[edge.first];
        Coordinate pointOne = diagonalClipping(
            border,
            (*normalizedPointsList)[edge.second],
            (*normalizedPointsList)[edge.first]
        );

        if(control == pointOne){
            //cout << "Edging 1" << endl;
            // normalizedPointsList->removeAt(edge.first);
            return;
        }

        Coordinate pointTwo = (*normalizedPointsList)[edge.second];
        if(hasSomeRegionCodeTruly(regionCodeList[regionCodeSecondIndex])) {
            pointTwo = parallelToAxisClipping(
                border,
                (*normalizedPointsList)[edge.first],
                (*normalizedPointsList)[edge.second]
            );
        }

        appendToNewLists(
            pointOne,
            pointTwo,
            edgesListToDraw,
            pointsListToDraw
        );
    }

    if(hasTwoRegionCodeTruly(regionCodeList[regionCodeSecondIndex])){
        Coordinate control = (*normalizedPointsList)[edge.second];
        Coordinate pointTwo = diagonalClipping(
            border,
            (*normalizedPointsList)[edge.first],
            (*normalizedPointsList)[edge.second]
        );

        if(control == pointTwo){            
            //cout << "Edging 2" << endl;
            // normalizedPointsList->removeAt(edge.second);
            return;
        }

        Coordinate pointOne = (*normalizedPointsList)[edge.first];
        if(hasSomeRegionCodeTruly(regionCodeList[regionCodeFirstIndex])) {
            pointOne = parallelToAxisClipping(
                border,
                (*normalizedPointsList)[edge.second],
                (*normalizedPointsList)[edge.first]
            );
        }

        appendToNewLists(
            pointOne,
            pointTwo,
            edgesListToDraw,
            pointsListToDraw
        );
    }

    if(hasSomeRegionCodeTruly(regionCodeList[regionCodeFirstIndex])){
        Coordinate aux = (*normalizedPointsList)[edge.first];
        Coordinate pointOne = parallelToAxisClipping(
            border,
            (*normalizedPointsList)[edge.second],
            (*normalizedPointsList)[edge.first]
        );
        if(aux == pointOne){
            // normalizedPointsList->removeAt(edge.second);
            // normalizedPointsList->removeAt(edge.first);
            return;
        }

        Coordinate pointTwo = (*normalizedPointsList)[edge.second];
        if(hasSomeRegionCodeTruly(regionCodeList[regionCodeSecondIndex])) {
            pointTwo = parallelToAxisClipping(
                border,
                (*normalizedPointsList)[edge.first],
                (*normalizedPointsList)[edge.second]
            );
        }

        appendToNewLists(
            pointOne,
            pointTwo,
            edgesListToDraw,
            pointsListToDraw
        );

        return;
    }

    Coordinate pointOne = (*normalizedPointsList)[edge.first];
    Coordinate pointTwo = (*normalizedPointsList)[edge.second];
    if(hasSomeRegionCodeTruly(regionCodeList[regionCodeSecondIndex])) {
        pointTwo = parallelToAxisClipping(
            border,
            (*normalizedPointsList)[edge.first],
            (*normalizedPointsList)[edge.second]
        );
    }

    appendToNewLists(
        pointOne,
        pointTwo,
        edgesListToDraw,
        pointsListToDraw
    );
}

void Clipper::appendToNewLists(
    Coordinate pointOne,
    Coordinate pointTwo,
    QList<pair<int,int>>* edgesListToDraw,
    QList<Coordinate>* pointsListToDraw
) { 
    pair<int,int> edgeToDraw;

    pointsListToDraw->append(pointOne);
    edgeToDraw.first = pointsListToDraw->size() - 1;

    pointsListToDraw->append(pointTwo);
    edgeToDraw.second = pointsListToDraw->size() - 1;

    edgesListToDraw->append(edgeToDraw);

    // cout << "PointsListToDraw: " << pointsListToDraw->size() << endl;
    // cout << "edgesListToDraw: " << edgesListToDraw->size() << endl;
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
