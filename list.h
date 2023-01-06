#ifndef LIST_H
#define LIST_H

#include <QVector>
#include <QString>
#include "task.h"


class List
{

public:
    QVector<Task> myList;
    QString listName;

    List();

    List(QString newListName) {
        this->listName = newListName;
    }
};

#endif // LIST_H
