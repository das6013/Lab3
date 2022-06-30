#include "iscanner.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

DataGraph* SqliteScanner::GetData(QString path)
{
    DataGraph* data = new DataGraph ();
    int max=5;
      qDebug()<<data->GetElementsCount();
    data->SenElemenCount(max);
    for (int i=0;i<max;i++)
    {
           int r = rand()%255;
        data->Push (QString::number(r), r+1);
        qDebug()<<2;
    }
    qDebug()<<data->GetElementsCount();
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(path);
    if (dbase.open())
    {
        QSqlQuery query ("SELECT * FROM" + dbase.tables().takeFirst());
        while (query.next()&&max>1)
        {
            data->Push (query.value(0).toString() , query.value(1).toFloat());
            max--;
         }
        data->GotData();
    }
    qDebug()<<data->GetElementsCount();
    return data;
}

DataGraph* JsonScanner::GetData(QString path)
{
    DataGraph* data = new DataGraph ();
    QString val;
    QFile file;
    file.setFileName(path);
    if  (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = doc.object();
        QStringList names (jsonObject.keys());
        foreach (QJsonValueRef x, jsonObject)
        {
            if (x.isDouble())
            {
                data->Push(names.takeFirst(), x.toDouble());
            }
        }
        data->GotData();
       }
       return data;
}

