#include "ParameterService.h"
#include <QFile>
#include <QJsonParseError>
#include <QDebug>

ParameterService::ParameterService(QObject *parent)
    : QObject(parent)
{
    initializeDefaultParameters();
}

QVariant ParameterService::getParameter(const QString &key, const QVariant &defaultValue) const
{
    return m_parameters.value(key, defaultValue);
}

QVariantMap ParameterService::getAllParameters() const
{
    return m_parameters;
}

void ParameterService::setParameter(const QString &key, const QVariant &value)
{
    if (m_parameters.value(key) != value) {
        m_parameters[key] = value;
        emit parameterChanged(key, value);
    }
}

void ParameterService::setParameters(const QVariantMap &parameters)
{
    for (auto it = parameters.begin(); it != parameters.end(); ++it) {
        setParameter(it.key(), it.value());
    }
}

bool ParameterService::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open parameter file:" << filePath;
        return false;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << error.errorString();
        return false;
    }

    m_parameters = doc.object().toVariantMap();
    m_currentFilePath = filePath;
    emit parametersLoaded();
    return true;
}

bool ParameterService::saveToFile(const QString &filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Cannot write parameter file:" << filePath;
        return false;
    }

    QJsonDocument doc(QJsonObject::fromVariantMap(m_parameters));
    file.write(doc.toJson());
    return true;
}

QByteArray ParameterService::buildParameterPacket(const QString &key, const QVariant &value) const
{
    // 构建参数下发协议包
    // 这里需要根据具体的协议格式实现
    QByteArray packet;
    
    // 示例格式: [Header][Key Length][Key][Value Length][Value][Checksum]
    packet.append(0xAA); // Header
    packet.append(0x55); // Header
    
    QByteArray keyBytes = key.toUtf8();
    packet.append(static_cast<char>(keyBytes.length()));
    packet.append(keyBytes);
    
    QByteArray valueBytes = value.toString().toUtf8();
    packet.append(static_cast<char>(valueBytes.length()));
    packet.append(valueBytes);
    
    // 简单校验和
    quint8 checksum = 0;
    for (int i = 2; i < packet.length(); ++i) {
        checksum ^= static_cast<quint8>(packet[i]);
    }
    packet.append(static_cast<char>(checksum));
    
    return packet;
}

QByteArray ParameterService::buildAllParametersPacket() const
{
    QByteArray allPackets;
    for (auto it = m_parameters.begin(); it != m_parameters.end(); ++it) {
        allPackets.append(buildParameterPacket(it.key(), it.value()));
    }
    return allPackets;
}

void ParameterService::initializeDefaultParameters()
{
    // 初始化默认参数
    m_parameters["device_id"] = 1;
    m_parameters["baud_rate"] = 115200;
    m_parameters["timeout"] = 5000;
    m_parameters["max_range"] = 100.0;
    m_parameters["min_range"] = 0.1;
    m_parameters["scan_frequency"] = 10.0;
    m_parameters["resolution"] = 0.01;
}