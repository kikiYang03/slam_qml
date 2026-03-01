#include "ServiceManager.h"
#include <QQmlEngine>
#include <QDebug>

ServiceManager* ServiceManager::s_instance = nullptr;

ServiceManager* ServiceManager::instance()
{
    if (!s_instance) {
        s_instance = new ServiceManager();
    }
    return s_instance;
}

ServiceManager::ServiceManager(QObject *parent)
    : QObject(parent)
    , m_communicationService(nullptr)
    , m_parameterService(nullptr)
    , m_protocolParser(nullptr)
    , m_deviceConnectionModel(nullptr)
{
}

void ServiceManager::initialize()
{
    // 创建服务实例
    m_communicationService = new CommunicationService(this);
    m_parameterService = new ParameterService(this);
    m_protocolParser = new ProtocolParser(this);
    m_deviceConnectionModel = new DeviceConnectionModel(this);
    
    // 连接服务之间的信号槽
    connectServices();
    
    qDebug() << "ServiceManager initialized";
}

void ServiceManager::registerQmlTypes()
{
    // 注册枚举类型 - 需要从ICommunicationService中注册
    qmlRegisterUncreatableMetaObject(
        ICommunicationService::staticMetaObject,
        "App.Core",
        1, 0,
        "ConnectionType",
        "Cannot create ConnectionType in QML"
    );
    
    // 注册单例提供者
    qmlRegisterSingletonType<ServiceManagerQmlProvider>(
        "App.Services",
        1, 0,
        "Services",
        [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)
            return new ServiceManagerQmlProvider();
        }
    );
    
    // 注册数据模型
    qmlRegisterUncreatableType<DeviceConnectionModel>(
        "App.Models",
        1, 0,
        "DeviceConnectionModel",
        "DeviceConnectionModel is managed by ServiceManager"
    );
    
    qmlRegisterUncreatableType<ParameterService>(
        "App.Services",
        1, 0,
        "ParameterService",
        "ParameterService is managed by ServiceManager"
    );
}

void ServiceManager::connectServices()
{
    // 设置DeviceConnectionModel的通信服务
    m_deviceConnectionModel->setCommunicationService(m_communicationService);
    
    // 连接通信服务和协议解析器
    connect(m_communicationService, &CommunicationService::dataReceived,
            m_protocolParser, &ProtocolParser::parseData);
    
    // 连接通信服务和设备连接模型
    connect(m_communicationService, &CommunicationService::connectionStateChanged,
            m_deviceConnectionModel, &DeviceConnectionModel::onConnectionStateChanged);
    
    connect(m_communicationService, &CommunicationService::errorOccurred,
            m_deviceConnectionModel, &DeviceConnectionModel::onErrorOccurred);
    
    // 连接协议解析器和参数服务
    connect(m_protocolParser, &ProtocolParser::parameterResponse,
            [this](const QString &key, const QVariant &value) {
                m_parameterService->setParameter(key, value);
            });
};
