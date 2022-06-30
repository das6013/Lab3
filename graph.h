#ifndef GRAPH_H
#define GRAPH_H
#include <QChart>
#include <QChartView>
#include <QPdfWriter>

class Graph
{
private:
    QChartView* view;
public:
    void SetGraphView (QChartView* _view) {view = _view;};
    QChart* GetChart() {return view->chart();}
    QChartView* GetGraphView () {return view;};
};

#endif // GRAPH_H
