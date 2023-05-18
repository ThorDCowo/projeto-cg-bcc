#include <QList>
#include "../../core/entities/object.h"

#ifndef OBJECT_LIST_FACTORY_H
#define OBJECT_LIST_FACTORY_H

class ObjectListFactory
{
    public:
        static QList<Object*> createObjectList();

};

#endif // OBJECT_LIST_FACTORY_H
