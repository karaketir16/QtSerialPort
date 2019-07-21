#include "logtest.h"
#include "ui_logtest.h"
#include <QRandomGenerator64>
struct Data
{
    uint8_t a;
    uint8_t b;
    uint8_t arr[5];
};

logTest::logTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logTest)
{
    ui->setupUi(this);
    keyG = 0;
    buffer = new QByteArray();
    portList = new QList<QSerialPortInfo>();
    (*portList) = QSerialPortInfo::availablePorts();
    for(auto port: *portList)
    {
        ui->comboBox->addItem(port.portName());
        ui->comboBox_2->addItem(port.portName());
    }

    portRead = new QSerialPort;
    portWrite = new QSerialPort;
    connect(portRead, &QSerialPort::readyRead, this, &logTest::dataReady);

}


logTest::~logTest()
{
    delete ui;
}

void logTest::on_pushButton_released()
{
    portWrite->setPortName((*portList)[ui->comboBox->currentIndex()].systemLocation());
    if(portWrite->isOpen())
    {
        qDebug()<<"Port is busy";
        return;
    }
    if(portWrite->open(QIODevice::ReadWrite))
    {
        qDebug()<<"Port connected";
    }
    else
    {
        qDebug()<<"Port can not open";
    }
}
QString stringfy(Data* d)
{
    QString s = "%1 %2 %3 %4 %5 %6 %7";
    s = s
            .arg(d->a).arg(d->b)
            .arg(d->arr[0]).arg(d->arr[1]).arg(d->arr[2]).arg(d->arr[3]).arg(d->arr[4]);
   return s;
}
void logTest::on_pushButton_2_released()
{
    data = new Data();
    data->a = (uint8_t) QRandomGenerator64::global()->generate();
    data->b = (uint8_t) QRandomGenerator64::global()->generate();
    for(int i = 0; i< 5; i++)
    {
        data->arr[i] = (uint8_t) QRandomGenerator64::global()->generate();
    }
    uint8_t key = 4;
    QByteArray ba(sizeof (uint8_t) + sizeof(Data), 0x00);
    memcpy(ba.data(), &key, sizeof(uint8_t));
    memcpy(ba.data()+sizeof(uint8_t), data, sizeof(Data));
    portWrite->write(ba);
    ui->textEdit->append("Sent");
    ui->textEdit->append(stringfy(data));

}

void logTest::dataReady()
{
    while(portRead->bytesAvailable())
    {
        QByteArray income = portRead->read(portRead->bytesAvailable());
        buffer->append(income);
    }
    if(keyG == 0 )
    {
        if(buffer->size() >= sizeof(uint8_t))
        {
            memcpy(&keyG, buffer->data(), sizeof(uint8_t));
            buffer->remove(0, sizeof(uint8_t));
        }
    }
    if(buffer->size() >= sizeof(Data))
    {
        comingData = new Data();
        memcpy(comingData, buffer->data(), sizeof (Data));
        buffer->remove(0, sizeof (Data));
        keyG = 0;
        ui->textEdit->append("coming");
        ui->textEdit->append(stringfy(comingData));

    }

}


void logTest::on_pushButton_3_released()
{
    portRead->setPortName((*portList)[ui->comboBox_2->currentIndex()].systemLocation());
    if(portRead->isOpen())
    {
        qDebug()<<"Port is busy";
        return;
    }
    if(portRead->open(QIODevice::ReadWrite))
    {
        qDebug()<<"Port connected";
    }
    else
    {
        qDebug()<<"Port can not open";
    }
}
