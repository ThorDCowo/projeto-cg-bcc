#include <QList>
#include <string.h>
#include "../../core/entities/object.h"
#include "../../core/entities/point.h"
#include "../../core/entities/line.h"
#include "../../core/entities/polygon.h"


#ifndef OBJECT_LIST_FACTORY_H
#define OBJECT_LIST_FACTORY_H

class ObjectListFactory
{
    public:
        static QList<Object*> createObjectList();

};

#endif // OBJECT_LIST_FACTORY_H
