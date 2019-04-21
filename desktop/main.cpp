#include <iostream>
#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QtSerialPort>

using namespace std;

int main() {
    QSerialPort serialPort;
    serialPort.setPortName("ttyACM1");
    qDebug()<<"Hello Qt";
    cout << "Hello, World!" << endl;
    return 0;
}

