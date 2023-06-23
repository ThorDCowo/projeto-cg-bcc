#include <QList>
#include <string.h>
#include "../../data/entities/object.h"
#include "../../data/entities/point.h"
#include "../../data/entities/line.h"
#include "../../data/entities/polygon.h"


#ifndef OBJECT_LIST_FACTORY_H
#define OBJECT_LIST_FACTORY_H

class ObjectListFactory
{
    public:
        static QList<Object*> createObjectList();

};

#endif // OBJECT_LIST_FACTORY_H
