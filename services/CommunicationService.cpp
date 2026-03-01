#include "CommunicationService.h"
#include <QDebug>
#include <QHostAddress>

CommunicationService::CommunicationService(QObject *parent)
    : ICommunicationService(parent)
    , m_state(ICommunicationService::ConnectionState::Disconnected)
    , m_type(ICommunicationService::ConnectionType::Serial)
    , m_port(0)
    , m_serialPort(nullptr)
    , m_tcpSocket(nullptr)
    , m_udpSocket(nullptr)
{
}

CommunicationService::~CommunicationService()
{
    cleanup();
}

bool CommunicationService::connectDevice(ConnectionType type, const QString &address, int port)
{
    if (m_state == ICommunicationService::ConnectionState::Connected || 
        m_state == ICommunicationService::ConnectionState::Connecting) {
        disconnectDevice();
    }

    m_type = type;
    m_address = address;
    m_port = port;

    setState(ICommunicationService::ConnectionState::Connecting);

    switch (type) {
    case ICommunicationService::ConnectionType::Serial:
        return connectSerial();
    case ICommunicationService::ConnectionType::TCP:
        return connectTcp();
    case ICommunicationService::ConnectionType::UDP:
        return connectUdp();
    }

    return false;
}

void CommunicationService::disconnectDevice()
{
    cleanup();
    setState(ICommunicationService::ConnectionState::Disconnected);
}

bool CommunicationService::sendData(const QByteArray &data)
{
    if (m_state != ICommunicationService::ConnectionState::Connected) {
        return false;
    }

    switch (m_type) {
    case ICommunicationService::ConnectionType::Serial:
        if (m_serialPort) {
            return m_serialPort->write(data) == data.size();
        }
        break;
    case ICommunicationService::ConnectionType::TCP:
        if (m_tcpSocket) {
            return m_tcpSocket->write(data) == data.size();
        }
        break;
    case ICommunicationService::ConnectionType::UDP:
        if (m_udpSocket) {
            return m_udpSocket->writeDatagram(data, QHostAddress(m_address), m_port) == data.size();
        }
        break;
    }

    return false;
}

ICommunicationService::ConnectionState CommunicationService::getConnectionState() const
{
    return m_state;
}

ICommunicationService::ConnectionType CommunicationService::getConnectionType() const
{
    return m_type;
}

bool CommunicationService::connectSerial()
{
    m_serialPort = new QSerialPort(this);
    m_serialPort->setPortName(m_address);
    m_serialPort->setBaudRate(QSerialPort::Baud115200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);

    connect(m_serialPort, &QSerialPort::readyRead, this, &CommunicationService::onSerialDataReady);
    connect(m_serialPort, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::error),
            this, &CommunicationService::onSerialError);

    if (m_serialPort->open(QIODevice::ReadWrite)) {
        setState(ICommunicationService::ConnectionState::Connected);
        return true;
    } else {
        emit errorOccurred(m_serialPort->errorString());
        setState(ICommunicationService::ConnectionState::Error);
        return false;
    }
}

bool CommunicationService::connectTcp()
{
    m_tcpSocket = new QTcpSocket(this);
    
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &CommunicationService::onTcpDataReady);
    connect(m_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &CommunicationService::onTcpError);
    connect(m_tcpSocket, &QAbstractSocket::stateChanged, this, &CommunicationService::onTcpStateChanged);

    m_tcpSocket->connectToHost(m_address, m_port);
    return true; // 异步连接，状态通过信号更新
}

bool CommunicationService::connectUdp()
{
    m_udpSocket = new QUdpSocket(this);
    
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &CommunicationService::onUdpDataReady);

    if (m_udpSocket->bind(QHostAddress::Any, m_port)) {
        setState(ICommunicationService::ConnectionState::Connected);
        return true;
    } else {
        emit errorOccurred("UDP bind failed");
        setState(ICommunicationService::ConnectionState::Error);
        return false;
    }
}

void CommunicationService::onSerialDataReady()
{
    if (m_serialPort) {
        QByteArray data = m_serialPort->readAll();
        emit dataReceived(data);
    }
}

void CommunicationService::onTcpDataReady()
{
    if (m_tcpSocket) {
        QByteArray data = m_tcpSocket->readAll();
        emit dataReceived(data);
    }
}

void CommunicationService::onUdpDataReady()
{
    if (m_udpSocket) {
        while (m_udpSocket->hasPendingDatagrams()) {
            QByteArray data;
            data.resize(m_udpSocket->pendingDatagramSize());
            m_udpSocket->readDatagram(data.data(), data.size());
            emit dataReceived(data);
        }
    }
}

void CommunicationService::onSerialError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        emit errorOccurred(m_serialPort->errorString());
        setState(ICommunicationService::ConnectionState::Error);
    }
}

void CommunicationService::onTcpError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)
    emit errorOccurred(m_tcpSocket->errorString());
    setState(ICommunicationService::ConnectionState::Error);
}

void CommunicationService::onTcpStateChanged(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::ConnectedState:
        setState(ICommunicationService::ConnectionState::Connected);
        break;
    case QAbstractSocket::UnconnectedState:
        setState(ICommunicationService::ConnectionState::Disconnected);
        break;
    case QAbstractSocket::ConnectingState:
        setState(ICommunicationService::ConnectionState::Connecting);
        break;
    default:
        break;
    }
}

void CommunicationService::cleanup()
{
    if (m_serialPort) {
        m_serialPort->close();
        m_serialPort->deleteLater();
        m_serialPort = nullptr;
    }
    
    if (m_tcpSocket) {
        m_tcpSocket->disconnectFromHost();
        m_tcpSocket->deleteLater();
        m_tcpSocket = nullptr;
    }
    
    if (m_udpSocket) {
        m_udpSocket->close();
        m_udpSocket->deleteLater();
        m_udpSocket = nullptr;
    }
}

void CommunicationService::setState(ICommunicationService::ConnectionState state)
{
    if (m_state != state) {
        m_state = state;
        emit connectionStateChanged(state);
    }
}