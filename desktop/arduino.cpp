#include "arduino.h"

Arduino::Arduino(QObject* parent)
    : QObject(parent)
{
    const auto& ports = QSerialPortInfo::availablePorts();

    QString arduino_uno_port_name = "";

    foreach(const QSerialPortInfo &serialPortInfo, ports)
    {
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier())
        {
            //  check if the product ID and the vendor ID match those of the arduino uno
            static constexpr quint16 arduino_uno_product_id = 67;
            static constexpr quint16 arduino_uno_vendor_id = 9025;
            if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){

                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }

    if (arduino_uno_port_name.isEmpty())
    {
        throw std::runtime_error ("Arduino board is disconnected");
    }
    port = new QSerialPort();
    qDebug() << "Arduino is found on port " << arduino_uno_port_name << "\n";

    port->setPortName(arduino_uno_port_name);
    port->open(QSerialPort::ReadOnly);
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);

    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(readMeasurements ()));

}


void Arduino::readMeasurements ()
{
    const auto& buff = port->readAll();

    int x = buff.size();

    qDebug() << "Got " << x << " bytes\n";
}
