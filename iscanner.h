#ifndef ISCANNER_H
#define ISCANNER_H
#include <QString>

#include "DataGraphs.h"

class IScanner
{
public:
    virtual DataGraph* GetData(QString path)  = 0;
};

class SqliteScanner :public IScanner
{
    DataGraph* GetData(QString path);
};

class JsonScanner :public IScanner
{
    DataGraph* GetData(QString path);
};
#endif // ISCANNER_H
