#ifndef PARAMETERSERVICE_H
#define PARAMETERSERVICE_H

#include <QObject>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonDocument>

class ParameterService : public QObject
{
    Q_OBJECT

public:
    explicit ParameterService(QObject *parent = nullptr);

    // 参数读取
    QVariant getParameter(const QString &key, const QVariant &defaultValue = QVariant()) const;
    QVariantMap getAllParameters() const;
    
    // 参数设置
    void setParameter(const QString &key, const QVariant &value);
    void setParameters(const QVariantMap &parameters);
    
    // 参数持久化
    bool loadFromFile(const QString &filePath);
    bool saveToFile(const QString &filePath) const;
    
    // 参数下发到设备
    QByteArray buildParameterPacket(const QString &key, const QVariant &value) const;
    QByteArray buildAllParametersPacket() const;

signals:
    void parameterChanged(const QString &key, const QVariant &value);
    void parametersLoaded();
    void parametersSaved();

private:
    QVariantMap m_parameters;
    QString m_currentFilePath;
    
    void initializeDefaultParameters();
};

#endif // PARAMETERSERVICE_H