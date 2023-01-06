#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

class Task
{


public:

    QString taskName;
    QString taskDesc;
    QDate dueDate;
    QString dateCreated;
    int importance;

    Task();

    Task(QString newtaskName, QString newtaskDec, QDate newDueDate, QString newdateCreated, int newImportance) {
        this->taskName = newtaskName;
        this->taskDesc = newtaskDec;
        this->dueDate = newDueDate;
        this->dateCreated = newdateCreated;
        this->importance = newImportance;
    }

    static bool sortDueDate(Task &a, Task &b)
    {
        return a.dueDate < b.dueDate;
    }

    static bool sortName(Task &a, Task &b)
    {
        return a.taskName < b.taskName;
    }

    static bool sortImportance(Task &a, Task &b)
    {
        return a.importance > b.importance;
    }
};



#endif // TASK_H
