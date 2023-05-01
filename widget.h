#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include"chart.h"
#include<QHBoxLayout>
//#include"port.h"
#include<QPushButton>
#include<QComboBox>
#include<QSerialPort>
#include<QSerialPortInfo>
#include<functional>
#include"serialport.h"
#include<QDebug>
#include<QGridLayout>
#include<QGroupBox>
#include<QLabel>
#include <QtCharts>
#include<QTimerEvent>
#include<QTimer>
#include"dchart.h"
#include<QSlider>
#include<QCheckBox>
#include<QTabWidget>
#include<QTextEdit>



#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif



using namespace QtCharts;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void changeIndex(int index);
    void onTimerTimeout();
private:
    Ui::Widget *ui;
    //QSerialPort*port;
    SerialPort*serialPort;
    QComboBox*portNameBox;
    QComboBox*baudRateBox;
    QComboBox*parityBox;
    QComboBox*dataBitsBox;
    QComboBox*stopBitsBox;
    QComboBox*endMarkerBox;
    std::function<void(int)>func;


    dChart*dchart;







    QPushButton*    button;
    QPushButton*    flush;
    QPushButton*    clearText;




    //波形图控制部分
    QSlider     * pageSlider;
    QCheckBox   * checkBox;
    QPushButton * rangeButton;
    QLineEdit   * minLine;
    QLineEdit   * maxLine;

    QPushButton * maxPageButton;
    QLineEdit   * maxPageLine;
    QHBoxLayout *maxPageLayout;


    QGridLayout * chartGroup;
    QGroupBox   * chartBox;

    QTextEdit   * textView;
    QTextEdit   * sendEdit;
    QGroupBox   * textGroupBox;
    QGroupBox   * chartGroupBox;
    QVBoxLayout * textLayout;
    QTabWidget  * tabWidget;


};
#endif // WIDGET_H
