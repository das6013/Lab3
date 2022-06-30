#include "iscanner.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

DataGraph* SqliteScanner::GetData(QString path)
{
    DataGraph* data = new DataGraph ();//cteare data 
    int max=5;//limit
      qDebug()<<data->GetElementsCount();//check count
    data->SenElemenCount(max);
    for (int i=0;i<max;i++)//костыль для проверки вывода 
    {
           int r = rand()%255;
        data->Push (QString::number(r), r+1);
        qDebug()<<2;
    }
    qDebug()<<data->GetElementsCount();
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");// add database
    dbase.setDatabaseName(path);//path to base
    if (dbase.open())
    {
        QSqlQuery query ("SELECT * FROM" + dbase.tables().takeFirst());//query
        while (query.next()&&max>1)//iter from base
        {
            data->Push (query.value(0).toString() , query.value(1).toFloat());
            max--;
         }
        data->GotData();//isEmpthy=0
    }
    qDebug()<<data->GetElementsCount();//check count base
    return data;
}

DataGraph* JsonScanner::GetData(QString path)
{
    DataGraph* data = new DataGraph ();
    QString val;//key
    QFile file;//file
    file.setFileName(path);
    if  (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject jsonObject = doc.object();//create json object 
        QStringList names (jsonObject.keys());//name 
        foreach (QJsonValueRef x, jsonObject)//iter
        {
            if (x.isDouble())
            {
                data->Push(names.takeFirst(), x.toDouble());//push data
            }
        }
        data->GotData();//isEmpthy=0
       }
       return data;
}

