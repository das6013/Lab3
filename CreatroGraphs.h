#ifndef CREATROGRAPHS_H
#define CREATROGRAPHS_H
#include <QString>
#include <graph.h>
#include <DataGraphs.h>
#include <QChartView>
#include "IOCContainer.h"
#include "IView.h"
#include "icolor.h"

class CreatroGraphs
{
public:
     Graph* GetGraph(DataGraph* data, QString graphType, QString coloring)//date -data graph graphType - type graph
     {
         Graph* graph = new Graph;//create graph 
         if (data->ChechEmpthy())//check emphy
         {
             return graph;
         }
          //set color graph
         if (coloring.toLower() == "colored")
             gContainer.RegisterInstance<IColor,Colored>();//
         else if (coloring.toLower() == "bw")
             gContainer.RegisterInstance<IColor, Monohrom>();
         else
             return graph;
          //set type graph
         if (graphType.toLower() == "barchart")
             gContainer.RegisterInstance<IView, BarView>();
         else if (graphType.toLower() == "piechart")
             gContainer.RegisterInstance<IView, PieView>();
         else
             return graph;
         QChartView  *view = gContainer.GetObject<IView>()
                 ->GetView(data->GetData(), gContainer.GetObject<IColor>()->GetColors(data->GetElementsCount()));//set data view
           graph->SetGraphView(view);
           return graph;
     };
};


#endif // CREATROGRAPHS_H
