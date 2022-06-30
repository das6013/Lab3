#ifndef DATAGRAPHS_H
#define DATAGRAPHS_H
#include <QString>
#include <QList>
#include "Dictionary.h"

class DataGraph
{
private:
    QList <Dictonary> data;//data graph
    int elementCounter;//elemet count
    bool  isEmpty = 1;//check empthy
public:
    void GotData() {isEmpty = 0; };//set isEmpty=0
    bool ChechEmpthy() {return isEmpty;};//check isEmpty
    void Push(QString header, float val) {data.push_back(Dictonary(header, val));};//push data in list
    QList <Dictonary> GetData() {return data; };//get data list
    int GetElementsCount () {return elementCounter;}//get element count
    void SenElemenCount(int count) {elementCounter=count;}//set element count
};

#endif // DATAGRAPHS_H
