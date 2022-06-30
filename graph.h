#ifndef GRAPH_H
#define GRAPH_H
#include <QChart>
#include <QChartView>
#include <QPdfWriter>

class Graph
{
private:
    QChartView* view;//view
public:
    void SetGraphView (QChartView* _view) {view = _view;};//set view
    QChart* GetChart() {return view->chart();}//get chart from view 
    QChartView* GetGraphView () {return view;};//get view
};

#endif // GRAPH_H
