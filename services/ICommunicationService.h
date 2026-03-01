#ifndef ICOMMUNICATIONSERVICE_H
#define ICOMMUNICATIONSERVICE_H

#include <QObject>
#include <QString>
#include <QByteArray>

class ICommunicationService : public QObject
{
    Q_OBJECT

public:
    enum class ConnectionType {
        Serial,
        TCP,
        UDP
    };
    Q_ENUM(ConnectionType)

    enum class ConnectionState {
        Disconnected,
        Connecting,
        Connected,
        Error
    };
    Q_ENUM(ConnectionState)

    explicit ICommunicationService(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~ICommunicationService() = default;

    virtual bool connectDevice(ConnectionType type, const QString &address, int port = 0) = 0;
    virtual void disconnectDevice() = 0;
    virtual bool sendData(const QByteArray &data) = 0;
    virtual ConnectionState getConnectionState() const = 0;
    virtual ConnectionType getConnectionType() const = 0;

signals:
    void dataReceived(const QByteArray &data);
    void connectionStateChanged(ConnectionState state);
    void errorOccurred(const QString &error);
};

// 为了向后兼容，在全局命名空间中也定义枚举
using ConnectionType = ICommunicationService::ConnectionType;
using ConnectionState = ICommunicationService::ConnectionState;

#endif // ICOMMUNICATIONSERVICE_H