#ifndef COMMUNICATIONSERVICE_H
#define COMMUNICATIONSERVICE_H

#include "ICommunicationService.h"
#include <QSerialPort>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTimer>

class CommunicationService : public ICommunicationService
{
    Q_OBJECT

public:
    explicit CommunicationService(QObject *parent = nullptr);
    ~CommunicationService() override;

    bool connectDevice(ConnectionType type, const QString &address, int port = 0) override;
    void disconnectDevice() override;
    bool sendData(const QByteArray &data) override;
    ICommunicationService::ConnectionState getConnectionState() const override;
    ICommunicationService::ConnectionType getConnectionType() const override;

private slots:
    void onSerialDataReady();
    void onTcpDataReady();
    void onUdpDataReady();
    void onSerialError(QSerialPort::SerialPortError error);
    void onTcpError(QAbstractSocket::SocketError error);
    void onTcpStateChanged(QAbstractSocket::SocketState state);

private:
    void cleanup();
    void setState(ICommunicationService::ConnectionState state);
    bool connectSerial();
    bool connectTcp();
    bool connectUdp();

    ICommunicationService::ConnectionState m_state;
    ICommunicationService::ConnectionType m_type;
    QString m_address;
    int m_port;

    QSerialPort *m_serialPort;
    QTcpSocket *m_tcpSocket;
    QUdpSocket *m_udpSocket;
};

#endif // COMMUNICATIONSERVICE_H