#ifndef LOGTEST_H
#define LOGTEST_H

#include <QWidget>
#include <QtSerialPort>
namespace Ui {
class logTest;
}

struct Data;

class logTest : public QWidget
{
    Q_OBJECT

public:
    uint8_t keyG;
    QByteArray *buffer;
    QList<QSerialPortInfo> *portList;
    QSerialPort *portWrite;
    QSerialPort *portRead;
    Data *data;
    Data *comingData;
    explicit logTest(QWidget *parent = nullptr);
    ~logTest();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();



    void on_pushButton_3_released();

public slots:
    void dataReady();

private:
    Ui::logTest *ui;
};

#endif // LOGTEST_H
