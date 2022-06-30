#include "mainwindow.h"
#include <QMessageBox>
//#include "ichart.h"
#include "CreatroGraphs.h"
#include "IOCContainer.h"
#include "iscanner.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
        //set visual
    setWindowTitle("Lab 3");
    setGeometry(0,0,1280,720);
    horizontalLayout = new QHBoxLayout(this);
    verticalLeftLayout = new QVBoxLayout();
    verticalRightLayout = new QVBoxLayout();
    horizontalGraphSettingsLayout = new QHBoxLayout();
    horizontalLayout->addLayout(verticalLeftLayout);
    horizontalLayout->addLayout(verticalRightLayout);
    verticalRightLayout->addLayout(horizontalGraphSettingsLayout);
    splitterLeft = new QSplitter;
    splitterRight = new QSplitter;
    verticalLeftLayout->addWidget(splitterLeft);
    verticalRightLayout->addWidget(splitterRight);
    
    directoryButton = new QPushButton ("Open directory");
    tableModel =  new QFileSystemModel(this);
    tableModel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    directoryName = QDir::homePath();
    tableModel->setRootPath(directoryName);
    tableView = new QTableView;
    tableView->setModel(tableModel);
    QItemSelectionModel *selectionModel = tableView->selectionModel();

    printButton = new QPushButton ("Print graph");
    monohromchbox = new QCheckBox("B/w graph");
    viewCombobox = new QComboBox();
    viewCombobox->insertItem(1, QString("Pie chart"));
    viewCombobox->insertItem(2, QString("Bar chart"));
    view = new QChartView;
//add object ui
    splitterLeft->addWidget(tableView);
    verticalLeftLayout->addWidget(directoryButton);
    horizontalGraphSettingsLayout->addWidget(printButton);
    horizontalGraphSettingsLayout->addWidget(monohromchbox);
    horizontalGraphSettingsLayout->addWidget(viewCombobox);
    verticalRightLayout ->addWidget(view);
//connect slot
    connect (directoryButton, SIGNAL(clicked()), this, SLOT(OpenDirectorySlot()));
    connect (printButton, SIGNAL(clicked()), this, SLOT(PrintCharSlot()));
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),this, SLOT(ChoseFileSlot(const QItemSelection &, const QItemSelection &)));
    connect (monohromchbox, SIGNAL(toggled(bool)), this, SLOT(RecolorChareSlot()));
    connect (viewCombobox, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangeTypeSlot()));
}

void MainWindow::RepaintChart(QString path, QString type_in_combobox, bool bw)//Repain graphs
{
    isChartOpen = 0;
    bool isFindedType = 0;
    if (path.endsWith(".sqlite"))
    {
        gContainer.RegisterInstance<IScanner, SqliteScanner>();
        isFindedType = 1;
    }
    else if (path.endsWith(".json"))
    {
        gContainer.RegisterInstance<IScanner, JsonScanner>();
        isFindedType = 1;
    }
    else
    {
        QMessageBox file_type_err;
        file_type_err.setText("Unknown file type");
        file_type_err.exec();
    }
    QString coloring = "";
    if (isFindedType)//check color type
    {
        if (bw)
            coloring = "bw";
        else
            coloring = "colored";
        QString chartType = "";
        bool isFindedType = 0;
        if (type_in_combobox == "Bar chart")
        {
            chartType = "barchart";
            isFindedType = 1;
        }
        else if (type_in_combobox == "Pie chart")
        {
            chartType = "piechart";
            isFindedType = 1;
        }
        else
        {
            QMessageBox chart_type_err;
            chart_type_err.setText("Unknown chart type");
            chart_type_err.exec();
        }
        if (chartType != "" && isFindedType)//check view type
        {
            CreatroGraphs graph_generator;
            graph = graph_generator.GetGraph(
                                              gContainer.GetObject<IScanner>()->GetData(fileName), //создаем и передаем данные
                                              chartType, coloring); //имя расцветки, имя типа графика
            view->setChart(graph->GetChart());
            isChartOpen = 1;
        }
    }
}

void MainWindow::RecolorChareSlot ()//Recolor 
{
    if (isChartOpen) RepaintChart(fileName, viewCombobox->currentText(), monohromchbox->checkState());
}

void  MainWindow::ChangeTypeSlot()//Change type
{
    if (isChartOpen) RepaintChart (fileName, viewCombobox->currentText(), monohromchbox->checkState());


}

void MainWindow::OpenDirectorySlot()//open directory
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec()) directoryName = dialog.selectedFiles().first();
   tableView->setRootIndex(tableModel->setRootPath(directoryName));
}

void MainWindow::PrintCharSlot()
{
    QString savingPath (" ");
    if (isChartOpen)//check open
    {
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::Directory);
        if (dialog.exec())
            savingPath = dialog.selectedFiles().first();
        if (savingPath != "")//print graph to pdf
        {
            QPdfWriter writer (savingPath + "/out.pdf");
            writer.setCreator("Someone");
            writer.setPageSize(QPageSize::A4);
            QPainter painter(&writer);
            view->render(&painter);
            painter.end();
        }
        else //can t way directore
        {
            QMessageBox nowae;
            nowae.setText("Cant open saving way");
            nowae.exec();
        }
        }
        else//not chart
        {
            QMessageBox nowae;
            nowae.setText("No chart to print");
            nowae.exec();
        }
}

void MainWindow::ChoseFileSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    QModelIndexList indexs =  selected.indexes();
    fileName = "";
    if (indexs.count() >= 1)
    {
        QModelIndex ix =  indexs.constFirst();
        fileName = tableModel->filePath(ix);
    }
    if (fileName != "") RepaintChart(fileName, viewCombobox->currentText(), monohromchbox->checkState());
    else
    {
        QMessageBox path_err;
        path_err.setText("Can`t find file");
        path_err.exec();
    }
}

MainWindow::~MainWindow()
{

}
