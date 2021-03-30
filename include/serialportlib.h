#ifndef SERIALPORTDEVICE_H
#define SERIALPORTDEVICE_H

//串口设备使用的共用类，包含有消息队列、超时处理等

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

#include "serial/serial.h"
#include "SerialPortLib_global.h"

#define REPLY_TIMEOUT 20

#ifdef INCLUDE_CODE
class SerialPortLib : public QObject
#else
class SERIALPORTLIB_EXPORT SerialPortLib : public QObject
#endif
{
    Q_OBJECT
public:
    explicit SerialPortLib();
    ~SerialPortLib();

    void setBeginAndEnd(const char beginPoint, const char endPoint);

    /**
     * @brief openSerialPort    打开串口
     * @param portName          串口名
     * @param baudRate          波特率
     * @param dataBits          数据位
     * @param parity            奇偶校验
     * @param stopBits          停止位
     * @param flowControl       流量控制
     * @return                  连接结果
     */
    bool openSerialPort(const QString portName,
                        const uint32_t baudRate = 19200,
                        const serial::bytesize_t dataBits = serial::eightbits,
                        const serial::parity_t parity = serial::parity_none,
                        const serial::stopbits_t  stopBits = serial::stopbits_one,
                        const serial::flowcontrol_t  flowControl = serial::flowcontrol_none);
    /**
     * @brief sendSerialMsg 发送串口消息
     * @param message       发送数据
     * @return              发送结果
     */
    bool sendSerialMsg(std::string message);

    /**
     * @brief recvSerialMsg 接收串口消息
     * @param message       数据引用
     * @param readSize      读取长度
     * @param replyTime     超时时间
     * @return              接收结果
     */
    bool recvSerialMsg(std::string &message, const int readSize = 20, const int replyTime = REPLY_TIMEOUT);

    /**
     * @brief sendAndRecvSerialMsg  发送串口消息并接收返回消息
     * @param sendMsg               发送数据
     * @param recvMsg               接受数据引用
     * @param readSize              读取长度
     * @param replyTime             超时时间
     * @return                      发送接受结果
     */
    bool sendAndRecvSerialMsg(const std::string sendMsg, std::string &recvMsg, const int readSize = 20, const int replyTime = REPLY_TIMEOUT);

    /**
     * @brief isOpen    串口是否打开
     * @return          true:打开  false:未打开
     */
    bool isOpen();

    /**
     * @brief closeSerialPort   关闭串口
     * @return                  关闭结果
     */
    bool closeSerialPort(); 

signals:
    //0info 1warn 2debug -1error
    void device_log_signal(QString msg, int level = 2);

private:
    //串口操作对象
    serial::Serial m_serialPort;

    //开始符
    char m_beginPoint;
    //结束符
    char m_endPoint;
};

#endif // SERIALPORTDEVICE_H
