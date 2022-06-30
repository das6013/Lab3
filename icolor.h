#ifndef ICOLOR_H
#define ICOLOR_H
#include <QColor>

class IColor
{
public:
    virtual QList <QColor>* GetColors(int colorCont) = 0;
};

class Colored : public IColor
{
public:
    QList <QColor>* GetColors(int colorCont);
};

class Monohrom :public IColor
{
public:
    QList <QColor>* GetColors(int colorCont);
};

#endif // ICOLOR_H
