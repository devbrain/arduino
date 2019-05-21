#ifndef ARDUINO_H
#define ARDUINO_H

#include <QtSerialPort>
#include <memory>

class Arduino : public QObject
{
    Q_OBJECT
public:
    explicit Arduino(QObject* parent = nullptr);

private slots:
    void readMeasurements ();

private:
    QSerialPort* port;
};

#endif // ARDUINO_H
