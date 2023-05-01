#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include<QDebug>
#include<queue>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

class SerialPort: public QSerialPort
{
    Q_OBJECT
public:
    SerialPort(QSerialPort*parent=nullptr);

    void                    refreshSerialPort();                 // 刷新串口 //关闭当前打开的串口
    bool                    setSerialPort(int index);            //设置串口
    void                    setEndMarker(QString endMarker);     //设置以 "\r\n" "\r" "\n"等结尾
    QStringList             getPortNameList();
    QStringList             getParityList();
    QStringList             getBaudRateList();
    QStringList             getDataBitsList();
    QStringList             getStopBitsList();
    QStringList             getEndMarkerList();
    QString                 getData();

    //波特率
    void                    setBaudRateC(int index);
    // 校验，校验默认选择无
    void                    setParityC(int index);

    // 数据位，数据位默认选择8位
    void                    setDataBitsC(int index);

    // 停止位，停止位默认选择1位
    void                    setStopBitsC(int index);

    // 控制流，默认选择无
    void                    setFlowControlC(int index);
public slots:
    // 串口槽函数
    void                    dataReceived();                      // 接收数据
    // 串口槽函数
    void                    dataSend(QString data);              // 发送数据
signals:
    void                    dataReady();
    void                    serialportOpen();
    void                    serialportClose();
private:

    QStringList             portNameList;                        //当前存在的串口列表
    QStringList             baudRateList;
    QStringList             parityList;
    QStringList             dataBitsList;
    QStringList             stopBitsList;
    QStringList             endMarkerList;
    int                     curPortIndex=0;
    std::queue<QString>     readyData;                           //接收到的准备好的数据，(已去掉结尾标识符)
    QString                 readBuf;                             //未读取到结尾标识符的临时数据缓冲区
    QString                 endMarker="\r\n";


};

#endif // SERIALPORT_H
