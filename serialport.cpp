#include "serialport.h"

SerialPort::SerialPort(QSerialPort*parent)
    :QSerialPort(parent)
{

    baudRateList <<"1200"<< "2400" << "4800" << "9600"
                 << "19200" << "38400"<< "57600" <<"115200";
    parityList<<tr("无校验")<<tr("偶校验")<<tr("奇校验");
    dataBitsList<<"5"<<"6"<<"7"<<"8";
    stopBitsList<<"1"<<"1.5"<<"2";
    endMarkerList<<"\r\n"<<"\r"<<"\n";
    // 参数配置
    // 波特率，波特率默认选择9600
    this->setBaudRate(QSerialPort::Baud9600);

    // 校验，校验默认选择无
    this->setParity(QSerialPort::NoParity);

    // 数据位，数据位默认选择8位
    this->setDataBits(QSerialPort::Data8);

    // 停止位，停止位默认选择1位
    this->setStopBits(QSerialPort::OneStop);

    // 控制流，默认选择无
    this->setFlowControl(QSerialPort::NoFlowControl);


    // 刷新串口
    refreshSerialPort();


    connect(this, &SerialPort::readyRead, this,[this]() {
        this->dataReceived();
    });
}


// 刷新串口
void SerialPort::refreshSerialPort()
{
    if(this->isOpen()){
        this->close();
        this->serialportClose();
    }
    portNameList.clear();
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) //添加新串口
    {
        portNameList.push_back(info.portName());
    }
}
bool SerialPort::setSerialPort(int index)
{
    if(this->isOpen()){
        this->close();
        this->serialportClose();
    }
    curPortIndex=index;
    this->setPortName(this->portNameList[index]);             //设置串口号
    if (this->open(QIODevice::ReadWrite)){
        qDebug()<<"serial "<<this->portNameList[index]<<"open succcess"<<endl;
        this->serialportOpen();
        return true;
    }
    //qDebug()<<"serial "<<this->portNameList[index]<<"open faild"<<endl;
    return false;
}
// 接收数据,使用read () / readLine () / readAll ()
void SerialPort::dataReceived()
{

    QByteArray data = this->readAll();                      // 读取数据
    if(!data.isEmpty())                                 // 接收到数据
    {
        QString str = std::move(readBuf);  // 返回纯文本
        str += tr(data);                                // 数据是一行一行传送的，要保存所有数据
        //qDebug() << "str info: " << str<<endl;
         // 清除之前的数据，防止追加，因为每次获取的数据不一样
        int index = str.indexOf(endMarker);                // 找到，返回索引值，找不到，返回-1
        if(index != -1)//接收到结尾标志符
        {
            //snprintf(buf,500,"%s", str.left(index + 2).toUtf8().data()); // QString转为char * 类型
            //str=str.left(index + endMarker);
            if(str.length()-index>endMarker.size()){
                readBuf=str.mid(index+endMarker.size());
            }
            str.remove(index, str.length() - index);
            readyData.push(std::move(str));                          // 将数据放入控件中
            dataReady();                               //数据已经准备好,发送信号
        }else{
            readBuf=std::move(str);
        }
    }
}
QString SerialPort::getData()
{
    if(!this->isOpen()){
        this->serialportClose();
    }
    QString tmp=readyData.front();
    readyData.pop();
    return tmp;
}
// 发送数据，write ()
void SerialPort::dataSend(QString data)
{
    if(!this->isOpen()){
        this->serialportClose();
    }
    qDebug()<<"send data:"<<data<<endl;
    data+=endMarker.toUtf8();
    this->write(data.toLatin1());      // 串口发送数据
}
QStringList SerialPort::getPortNameList(){
    return this->portNameList;
}
void SerialPort::setEndMarker(QString endMarker){     //设置以 "\r\n" "\r" "\n"等结尾
    this->endMarker=endMarker;
}
void SerialPort::setBaudRateC(int index){
    bool is=false;
    switch(index) {
        case 0:
            is=this->setBaudRate(BaudRate::Baud1200);
            break;
        case 1:
            is=this->setBaudRate(BaudRate::Baud2400);
            break;
        case 2:
            is=this->setBaudRate(BaudRate::Baud4800);
            break;
        case 3:
            is=this->setBaudRate(BaudRate::Baud9600);
            break;
        case 4:
            is=this->setBaudRate(BaudRate::Baud19200);
            break;
        case 5:
            is=this->setBaudRate(BaudRate::Baud38400);
            break;
        case 6:
            is=this->setBaudRate(BaudRate::Baud57600);
            break;
        case 7:
            is=this->setBaudRate(BaudRate::Baud115200);
            break;
        default:
            this->setBaudRate(BaudRate::UnknownBaud);
            break;
    }
    if(is){
        qDebug()<<"set baudrate success"<<endl;
    }else{
        qDebug()<<"set baudrate error"<<endl;
    }
}

// 校验，校验默认选择无
void SerialPort::setParityC(int index){
    switch(index) {
        case 0:
            this->setParity(QSerialPort::Parity::NoParity);
            break;
        case 1:
            this->setParity(QSerialPort::Parity::EvenParity);
            break;
        case 2:
            this->setParity(QSerialPort::Parity::OddParity);
            break;
        default:
            this->setBaudRate(BaudRate::UnknownBaud);
            break;
    }
}

// 数据位，数据位默认选择8位
void SerialPort::setDataBitsC(int index){
    bool is=false;
    switch(index) {
        case 0:
            is=this->setDataBits(QSerialPort::DataBits::Data5);
            break;
        case 1:
            is=this->setDataBits(QSerialPort::DataBits::Data6);
            break;
        case 2:
            is=this->setDataBits(QSerialPort::DataBits::Data7);
            break;
        case 3:
            is=this->setDataBits(QSerialPort::DataBits::Data8);
        default:
            break;
    }
    if(is){
        qDebug()<<"set databits success"<<endl;
    }else{
        qDebug()<<"set databits error"<<endl;
    }
}

// 停止位，停止位默认选择1位
void SerialPort::setStopBitsC(int index){
    switch(index) {
        case 0:
            this->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            this->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        case 2:
            this->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
    }
}
QStringList SerialPort::getParityList(){
    return this->parityList;
}
QStringList SerialPort::getDataBitsList(){
    return this->dataBitsList;
}
QStringList SerialPort::getStopBitsList(){
    return this->stopBitsList;
}
QStringList SerialPort::getBaudRateList(){
    return this->baudRateList;
}
QStringList SerialPort::getEndMarkerList(){
    return this->endMarkerList;
}
