#include "object.h"

void Object::drawEdges(QPainter &painter)
{
    // cout << "Edges List: " << edgesList.size() << endl;
    // cout << "Points List: " << pointsList.size() << endl;
    // cout << "Projection List: " << projectionPointsList.size() << endl;
    // cout << "Normalize List: " << normalizedPointsList.size() << endl;

    for (qsizetype i = 0; i < edgesList.size(); i++)
    {
        // cout << "Edge First: " << edgesList[i].first << " Edge Second: " << edgesList[i].second << endl;
        painter.drawLine(
            normalizedPointsList[edgesList[i].first].x,
            normalizedPointsList[edgesList[i].first].y,
            normalizedPointsList[edgesList[i].second].x, 
            normalizedPointsList[edgesList[i].second].y
        );
    }

    // cout << "Primeiro Ponto:" << to_string(projectionPointsList[0].x) << "," << to_string(projectionPointsList[0].y) << endl;
    // cout << "Ultimo Ponto:" << to_string(projectionPointsList[projectionPointsList.size() - 1].x) << "," << to_string(projectionPointsList[projectionPointsList.size() - 1].y) << endl;
}

void Object::orthogonalNormalize(
    int windowWidth, 
    int windowHeight,
    Coordinate windowCenter, 
    Coordinate axisToExclude)
{
    orthogonalProjection(axisToExclude);
    normalizeCoordinates(windowWidth, windowHeight, windowCenter);
}

void Object::orthogonalProjection(Coordinate axisToExclude){
    projectionPointsList.erase(projectionPointsList.begin(), projectionPointsList.end());

    if(axisToExclude.x) {
        for (qsizetype i = 0; i < pointsList.size(); i++)
            projectionPointsList.append(Coordinate(pointsList[i].y, pointsList[i].z));
        return;    
    }

    if(axisToExclude.y) {
        for (qsizetype i = 0; i < pointsList.size(); i++)
            projectionPointsList.append(Coordinate(pointsList[i].x, pointsList[i].z));
        return; 
    }

    for (qsizetype i = 0; i < pointsList.size(); i++)
        projectionPointsList.append(Coordinate(pointsList[i].x, pointsList[i].y));
}

void Object::perspectiveNormalize(int windowWidth, int windowHeight, Coordinate windowCenter, float distanceFromProjection)
{    
    planeProjection(distanceFromProjection);
    normalizeCoordinates(windowWidth, windowHeight, windowCenter);
}

void Object::planeProjection(float distanceBetweenCenterOfProjectionandPlane) {
    projectionPointsList.erase(projectionPointsList.begin(), projectionPointsList.end());

    float projectionAxisX = 0.0;
    float projectionAxisY = 0.0;

    for (qsizetype i = 0; i < pointsList.size(); i++) {
        if(pointsList[i].z < 0){
            projectionAxisX = -(pointsList[i].x * distanceBetweenCenterOfProjectionandPlane)/pointsList[i].z;
            projectionAxisY = -(pointsList[i].y * distanceBetweenCenterOfProjectionandPlane)/pointsList[i].z;
        }
        if(pointsList[i].z == 0) {
            projectionAxisX = pointsList[i].x;
            projectionAxisY = pointsList[i].y;
        }
        else {
            projectionAxisX = (pointsList[i].x * distanceBetweenCenterOfProjectionandPlane)/pointsList[i].z;
            projectionAxisY = (pointsList[i].y * distanceBetweenCenterOfProjectionandPlane)/pointsList[i].z;
        }        

        projectionPointsList.append(Coordinate(
            projectionAxisX, 
            projectionAxisY, 
            distanceBetweenCenterOfProjectionandPlane
        ));
    }
}

void Object::normalizeCoordinates(
    int windowWidth, 
    int windowHeight, 
    Coordinate windowCenter
)
{
    
    normalizedPointsList.erase(normalizedPointsList.begin(), normalizedPointsList.end());
    
    float newX = 0.0;
    float newY = 0.0;
    
    float windowXBegin = windowCenter.x - (windowWidth / 2);
    float windowYBegin = windowCenter.y - (windowHeight / 2);

    for (qsizetype i = 0; i < projectionPointsList.size(); i++)
    {
        newX = (projectionPointsList[i].x - windowXBegin) / (windowWidth);
        newX = (projectionPointsList[i].y - windowYBegin) / (windowHeight);
        normalizedPointsList.append(Coordinate(newX, newY));
    }
}

void Object::transformToViewport(Coordinate center, int viewportWidth, int viewportHeight)
{
    float halfViewportWidth = viewportWidth / 2;
    float halfViewportHeight = viewportHeight / 2;

    float newX = 0.0;
    float newY = 0.0;

    for (qsizetype i = 0; i < normalizedPointsList.size(); i++)
    {
        newX = halfViewportWidth + (normalizedPointsList[i].x * viewportWidth);
        newY = halfViewportHeight + (normalizedPointsList[i].y * viewportWidth);

        viewportPointsList.append(Coordinate(newX, newY));
    }
}

void Object::rotateWorld(float radians, Coordinate axis)
{    
    if(axis.x) {
        for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = Coordinate(
                pointsList[i].x,
                pointsList[i].y * cosHelper(radians) - (pointsList[i].z * sinHelper(radians)),
                pointsList[i].y * sinHelper(radians) + (pointsList[i].z * cosHelper(radians))
            );
        }
        return;
    } 
    
    if(axis.y) {
        for(qsizetype i = 0; i < pointsList.size(); i++){
            pointsList[i] = Coordinate(
                pointsList[i].x * cosHelper(radians) + (pointsList[i].z * sinHelper(radians)),
                pointsList[i].y,
                pointsList[i].z * cosHelper(radians) - (pointsList[i].x * sinHelper(radians))
            );
        }
        return;
    }

    for(qsizetype i = 0; i < pointsList.size(); i++){
        pointsList[i] = Coordinate(
            pointsList[i].x * cosHelper(radians) - (pointsList[i].y * sinHelper(radians)),
            pointsList[i].x * sinHelper(radians) + (pointsList[i].y * cosHelper(radians)),
            pointsList[i].z
        );
    }

}

Coordinate Object::barycenter()
{
    Coordinate center(0,0,0);

    for (qsizetype i = 0; i < pointsList.size(); i++)
    {
        center.x += pointsList[i].x;
        center.y += pointsList[i].y;
        center.z += pointsList[i].z;
    }
    center.x = (center.x / pointsList.size());
    center.y = (center.y / pointsList.size());
    center.z = (center.z / pointsList.size());

    return center;
}