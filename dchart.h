#ifndef DCHART_H
#define DCHART_H

#include <QWidget>
#include <QtCharts>
#include <QTimerEvent>
#include <QTimer>
#include <vector>
#include <QHBoxLayout>
#include <QDebug>


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif





class dChart : public QWidget
{
    Q_OBJECT
public:
    explicit dChart(QWidget *parent = nullptr);


    void setViewMode(bool model);
    int  getCurPage();
    void setRange(double min,double max);
    void setMaxPage(int maxPage);
signals:
    void push_value(double value);
    void curPageChange();
public slots:

    void recv_value(double value);
    void browsing_mode(int page);

private:
    QLineSeries *m_pLineSeries;
    QChart *m_pChart;
    QValueAxis *m_pAxisX ;
    QValueAxis *m_pAxisY ;
    QChartView *chartView;

    std::vector<double>points;

    //参数配置

    int timeBase=0;
    int maxPage;
    int curPage=0;
    int curPointX=0;
    bool viewMode=false;
    double minYValue=-40;
    double maxYValue=0;
    double step=0.5;


};

#endif // DCHART_H
