#ifndef DEVICECONNECTIONMODEL_H
#define DEVICECONNECTIONMODEL_H

#include <QObject>
#include "../services/ICommunicationService.h"

// 前向声明
class CommunicationService;

class DeviceConnectionModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int connectionType READ connectionType NOTIFY connectionTypeChanged)
    Q_PROPERTY(int connectionState READ connectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)

public:
    explicit DeviceConnectionModel(QObject *parent = nullptr);

    int connectionType() const;
    int connectionState() const;
    QString address() const;
    int port() const;
    QString errorMessage() const;

    void setAddress(const QString &address);
    void setPort(int port);
    void setCommunicationService(CommunicationService *service);

    Q_INVOKABLE bool connectDevice(int type);
    Q_INVOKABLE void disconnectDevice();
    Q_INVOKABLE bool sendData(const QString &data);

public slots:
    void onConnectionStateChanged(ICommunicationService::ConnectionState state);
    void onErrorOccurred(const QString &error);

signals:
    void connectionTypeChanged();
    void connectionStateChanged();
    void addressChanged();
    void portChanged();
    void errorMessageChanged();
    void dataReceived(const QString &data);

private:
    ICommunicationService::ConnectionType m_connectionType;
    ICommunicationService::ConnectionState m_connectionState;
    QString m_address;
    int m_port;
    QString m_errorMessage;
    CommunicationService *m_communicationService;
};

#endif // DEVICECONNECTIONMODEL_H