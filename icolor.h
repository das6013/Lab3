#ifndef ICOLOR_H
#define ICOLOR_H
#include <QColor>

class IColor// color product
{
public:
    virtual QList <QColor>* GetColors(int colorCont) = 0;//get data colorCont - count color
};

class Colored : public IColor//colored color 
{
public:
    QList <QColor>* GetColors(int colorCont);//get data colorCont - count color
};

class Monohrom :public IColor
{
public:
    QList <QColor>* GetColors(int colorCont);//get data colorCont - count color
};

#endif // ICOLOR_H
