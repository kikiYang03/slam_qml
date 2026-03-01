#include "DeviceConnectionModel.h"
#include "../services/CommunicationService.h"

DeviceConnectionModel::DeviceConnectionModel(QObject *parent)
    : QObject(parent)
    , m_connectionType(ICommunicationService::ConnectionType::Serial)
    , m_connectionState(ICommunicationService::ConnectionState::Disconnected)
    , m_address("COM1")
    , m_port(9600)
    , m_communicationService(nullptr)
{
}

int DeviceConnectionModel::connectionType() const
{
    return static_cast<int>(m_connectionType);
}

int DeviceConnectionModel::connectionState() const
{
    return static_cast<int>(m_connectionState);
}

QString DeviceConnectionModel::address() const
{
    return m_address;
}

int DeviceConnectionModel::port() const
{
    return m_port;
}

QString DeviceConnectionModel::errorMessage() const
{
    return m_errorMessage;
}

void DeviceConnectionModel::setAddress(const QString &address)
{
    if (m_address != address) {
        m_address = address;
        emit addressChanged();
    }
}

void DeviceConnectionModel::setPort(int port)
{
    if (m_port != port) {
        m_port = port;
        emit portChanged();
    }
}

void DeviceConnectionModel::setCommunicationService(CommunicationService *service)
{
    m_communicationService = service;
}

bool DeviceConnectionModel::connectDevice(int type)
{
    if (!m_communicationService) {
        return false;
    }
    
    m_connectionType = static_cast<ICommunicationService::ConnectionType>(type);
    emit connectionTypeChanged();
    
    return m_communicationService->connectDevice(m_connectionType, m_address, m_port);
}

void DeviceConnectionModel::disconnectDevice()
{
    if (m_communicationService) {
        m_communicationService->disconnectDevice();
    }
}

bool DeviceConnectionModel::sendData(const QString &data)
{
    if (m_communicationService) {
        return m_communicationService->sendData(data.toUtf8());
    }
    return false;
}

void DeviceConnectionModel::onConnectionStateChanged(ICommunicationService::ConnectionState state)
{
    if (m_connectionState != state) {
        m_connectionState = state;
        emit connectionStateChanged();
    }
}

void DeviceConnectionModel::onErrorOccurred(const QString &error)
{
    if (m_errorMessage != error) {
        m_errorMessage = error;
        emit errorMessageChanged();
    }
}