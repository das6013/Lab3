#ifndef IVIEW_H
#define IVIEW_H
#include <QChartView>
#include "Dictionary.h"
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QColor>

class IView// type View graphs
{
public:
    virtual QChartView* GetView (QList<Dictonary> graphData, QList <QColor>* colors) = 0;//get view
};
#endif // IVIEW_H

class PieView :public IView //pie view
{
    QChartView* GetView (QList<Dictonary> graphData, QList <QColor>* colors)
    {
        //create view,chart and series
        QChartView *view = new QChartView;
        QChart *chart = view->chart();
        QPieSeries *series = new QPieSeries();
        int i = 0;
        foreach (Dictonary elem, graphData)
        {
            qDebug()<<series->count();
            series->append(elem.key, elem.val);//add value series
            qDebug()<<series->count();
            series->slices().at(i)->setBrush(colors->at(i));//Тут происходит выход у JSON после повтороного проверки//set color 
            i++;
        }
        chart->addSeries(series);//add all data series
        return view;
    }
};

class BarView :public IView//BarView 
{
    QChartView* GetView (QList<Dictonary> graphData, QList <QColor>* colors)
    {
        //creae view chart and series
        QChartView *view = new QChartView;
        view->setRenderHint(QPainter::Antialiasing);
        QChart *chart = view->chart();
        QBarSeries *series=new QBarSeries;;
        int i = 0;//conter
        foreach (Dictonary elem, graphData)
        {
            QBarSet *set = new QBarSet (elem.key);//set key
            *set << elem.val;//set value
            set->setBrush(colors->at(i));//color set
            series->append(set);//append change
            i++;
        }
        chart->addSeries(series);//add data in chart
        return view;
    };
};


