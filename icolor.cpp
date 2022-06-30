#include "icolor.h"

QList <QColor>* Colored::GetColors(int colorCont)
{
    QList <QColor>* colors = new QList <QColor>;
    for (int i = 0; i < colorCont; i++)
    {
        int r = rand()%255;
        int g = rand()%255;
        int b = rand()%255;
        colors->push_back(QColor(r,g,b)); //добавляем случайный цвет
    }
    return colors;
};

QList <QColor>* Monohrom::GetColors(int colorCont)
{
    QList <QColor>* colors = new QList <QColor>;

    for (int i = 0; i < colorCont; i++)
    {
        int color = rand()%255;
        colors->push_back(QColor(color,color,color));
    }
    return colors;
};
