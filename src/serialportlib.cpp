#include "serialportlib.h"
#include <QDebug>
#include <QTime>

SerialPortLib::SerialPortLib()
{
}

SerialPortLib::~SerialPortLib()
{
}

void SerialPortLib::setBeginAndEnd(const char beginPoint, const char endPoint)
{
    m_beginPoint = beginPoint;
    m_endPoint = endPoint;
}

bool SerialPortLib::openSerialPort(const QString portName, const uint32_t baudRate, const serial::bytesize_t dataBits,
                                      const serial::parity_t parity, const serial::stopbits_t stopBits, const serial::flowcontrol_t  flowControl)
{
    if(m_serialPort.isOpen())
    {
        m_serialPort.close();
    }

    m_serialPort.setPort(portName.toStdString());
    m_serialPort.setBaudrate(baudRate);
    m_serialPort.setBytesize(dataBits);
    m_serialPort.setParity(parity);
    m_serialPort.setStopbits(stopBits);
    m_serialPort.setFlowcontrol(flowControl);
    m_serialPort.open();

    return m_serialPort.isOpen();
}

bool SerialPortLib::sendSerialMsg(std::string message)
{
    if (!m_serialPort.isOpen())
    {
        return false;
    }

    message.insert(0,1,m_beginPoint);
    message.push_back(m_endPoint);

//    emit device_log_signal(QString::fromStdString(message));

    m_serialPort.flushInput();
    m_serialPort.flushOutput();

    return m_serialPort.write(message);
}

bool SerialPortLib::recvSerialMsg(std::string &msg, const int readSize, const int replyTime)
{
    serial::Timeout timeout= serial::Timeout(replyTime,readSize*replyTime);
    m_serialPort.setTimeout(timeout);
    //串口收到消息
    if (m_serialPort.isOpen())
    {
        if(m_serialPort.read(msg,readSize))
        {
            return true;
        }
        else
        {
            qDebug() << "read time out";

            return false;
        }
    }
    else
    {
        emit device_log_signal("serial close",-1);

        return false;
    }
}

bool SerialPortLib::sendAndRecvSerialMsg(const std::string sendMsg, std::string &recvMsg, const int readSize, const int replyTime)
{
    if(sendSerialMsg(sendMsg))
    {
        return recvSerialMsg(recvMsg,readSize,replyTime);
    }
    else
    {
        return false;
    }
}

bool SerialPortLib::isOpen()
{
    return m_serialPort.isOpen();
}

bool SerialPortLib::closeSerialPort()
{
    if (m_serialPort.isOpen())
    {
        m_serialPort.close();
    }
    return true;
}
