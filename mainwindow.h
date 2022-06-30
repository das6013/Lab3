#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graph.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QSplitter>
#include <QTableView>
#include <QFileSystemModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPainter>
#include <QPdfWriter>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QPdfWriter>
#include <QtSql>
#include <QItemSelectionModel>

class MainWindow : public QWidget
{
    Q_OBJECT

private slots:
    void OpenDirectorySlot();
    void PrintCharSlot();
    void ChoseFileSlot(const QItemSelection &, const QItemSelection &);
    void RepaintChart (QString path, QString type, bool bw);
    void RecolorChareSlot ();
    void ChangeTypeSlot();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QString directoryName;
    QString fileName;
    QString savePath;
    QSplitter *splitterLeft;
    QSplitter *splitterRight;
    QVBoxLayout *verticalLeftLayout;
    QVBoxLayout *verticalRightLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalGraphSettingsLayout;
    QPushButton *directoryButton;
    QPushButton *printButton;
    QTableView *tableView;
    QFileSystemModel *tableModel;
    QCheckBox *monohromchbox;
    QComboBox *viewCombobox;
    QPainter painter;
    Graph* graph;
    QChartView* view;
    bool isChartOpen = 0;
};
#endif // MAINWINDOW_H
