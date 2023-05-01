#include "dchart.h"

dChart::dChart(QWidget *parent) : QWidget(parent)
{
    maxPage=100;


    //x坐标轴
    m_pAxisX = new QValueAxis();
    m_pAxisX->setMin(0);
    m_pAxisX->setMax(maxPage);
    //y坐标轴
    m_pAxisY = new QValueAxis();
    m_pAxisY->setRange(minYValue, maxYValue);

    //创建QChart
    m_pChart = new QChart();

    m_pLineSeries = new QLineSeries(); //创建折线绘制对象

    m_pChart->addSeries(m_pLineSeries);

    m_pChart->addAxis(m_pAxisX, Qt::AlignBottom); //将X轴添加到图表上
    m_pChart->addAxis(m_pAxisY, Qt::AlignRight); //将Y轴添加到图表上

    //创建折线类

    m_pLineSeries->setPointsVisible(true); //设置数据点可见
    m_pLineSeries->attachAxis(m_pAxisX); //X轴绑定
    m_pLineSeries->attachAxis(m_pAxisY); //Y轴绑定



    m_pLineSeries->setPen(QPen(Qt::black, 2, Qt::SolidLine));


    m_pChart->setMargins(QMargins(0, 0, 0, 0));
    m_pChart->legend()->hide(); //隐藏图例

    //绑定chart控件
    chartView = new QChartView(this);
    chartView->setChart(m_pChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QHBoxLayout*hlayout=new QHBoxLayout(this);
    hlayout->addWidget(chartView);


    connect(this,&dChart::push_value,this,&dChart::recv_value);
}
void dChart::recv_value(double value)
{
    //qDebug()<<"value:"<<value<<endl;
        points.push_back(value);
        if(curPointX==maxPage){
            curPage++;
            if(!viewMode)curPageChange();
//            if(viewMode){
//                m_pChart->axisX()->setMin(timeBase+maxPage*curPage);
//                m_pChart->axisX()->setMax(timeBase+maxPage*curPage+maxPage);
//                m_pLineSeries->clear();
//            }

            curPointX=0;
        }

//设置每页显示多少数据

//      int curPoint=timeBase+maxPage*curPage+curPointX;
        curPointX++;

        if(!viewMode){
            browsing_mode(curPage);
        }
//      if(!viewMode)return;
//      m_pLineSeries->append(QPointF(curPoint, points[curPoint]));


}
void dChart::browsing_mode(int page){
    m_pChart->axisX()->setMin(timeBase+maxPage*page);
    m_pChart->axisX()->setMax(timeBase+maxPage*page+maxPage);
    m_pLineSeries->clear();

    int curPoint=timeBase+maxPage*page+maxPage;
    for(int i=timeBase+maxPage*page;(i<points.size())&&i<curPoint;++i){//每次刷新保证不占用过大内存
        double tmp;
        if(points[i]<minYValue){
            tmp=minYValue;
        }else if(points[i]>maxYValue){
            tmp=maxYValue;
        }else{
            tmp=points[i];
        }
        m_pLineSeries->append(QPointF(i, tmp));
    }
}
void dChart::setViewMode(bool model){
    this->viewMode=model;
}
int  dChart::getCurPage(){
    return this->curPage;
}
void  dChart::setRange(double min,double max){
    this->minYValue=min;
    this->maxYValue=max;
    m_pAxisY->setRange(minYValue, maxYValue);
    this->update();
    return;
}
void  dChart::setMaxPage(int maxPage){
    this->maxPage=maxPage;//更新页面最大点数
    this->curPage=this->points.size()/this->maxPage;//更新以当前maxPage下的当前页数
    this->curPointX=this->points.size()%this->maxPage;//更新以当前maxPage下的在当前页的第几个点
    curPageChange();//发送信号重新设置滚动条范围
    this->update();
    return;
}
