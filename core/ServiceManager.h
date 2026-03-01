#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "../services/CommunicationService.h"
#include "../services/ParameterService.h"
#include "../protocol/ProtocolParser.h"
#include "../models/DeviceConnectionModel.h"

class ServiceManager : public QObject
{
    Q_OBJECT

public:
    static ServiceManager* instance();
    
    void initialize();
    void registerQmlTypes();
    
    // 获取服务实例
    CommunicationService* communicationService() const { return m_communicationService; }
    ParameterService* parameterService() const { return m_parameterService; }
    ProtocolParser* protocolParser() const { return m_protocolParser; }
    DeviceConnectionModel* deviceConnectionModel() const { return m_deviceConnectionModel; }

private:
    explicit ServiceManager(QObject *parent = nullptr);
    ~ServiceManager() = default;
    
    void connectServices();

    static ServiceManager* s_instance;
    
    CommunicationService* m_communicationService;
    ParameterService* m_parameterService;
    ProtocolParser* m_protocolParser;
    DeviceConnectionModel* m_deviceConnectionModel;
};

// QML单例提供者
class ServiceManagerQmlProvider : public QObject
{
    Q_OBJECT

public:
    explicit ServiceManagerQmlProvider(QObject *parent = nullptr) : QObject(parent) {}
    
    Q_INVOKABLE QObject* deviceConnection() const {
        return ServiceManager::instance()->deviceConnectionModel();
    }
    
    Q_INVOKABLE QObject* parameterService() const {
        return ServiceManager::instance()->parameterService();
    }
};

#endif // SERVICEMANAGER_H