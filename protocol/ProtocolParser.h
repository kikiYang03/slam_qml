#ifndef PROTOCOLPARSER_H
#define PROTOCOLPARSER_H

#include <QObject>
#include <QByteArray>
#include <QVariantMap>
#include <QVector>
#include <QVector3D>
#include <QColor>
#include <QString>

// ROS消息类型定义
struct LaserScanMsg {
    float angle_min;
    float angle_max;
    float angle_increment;
    float time_increment;
    float scan_time;
    float range_min;
    float range_max;
    QVector<float> ranges;
    QVector<float> intensities;
};

struct TFMsg {
    QString frame_id;
    QString child_frame_id;
    double timestamp;
    double translation_x;
    double translation_y;
    double translation_z;
    double rotation_x;
    double rotation_y;
    double rotation_z;
    double rotation_w;
};

struct PointCloudMsg {
    QString frame_id;
    double timestamp;
    QVector<QVector3D> points;
    QVector<QColor> colors;
};

Q_DECLARE_METATYPE(LaserScanMsg)
Q_DECLARE_METATYPE(TFMsg)
Q_DECLARE_METATYPE(PointCloudMsg)

class ProtocolParser : public QObject
{
    Q_OBJECT

public:
    explicit ProtocolParser(QObject *parent = nullptr);

    // 解析入口
    void parseData(const QByteArray &data);

    // 构建测试数据包
    static QByteArray buildTestPacket(const QString &type, const QVariantMap &data);

signals:
    void laserScanReceived(const LaserScanMsg &scan);
    void tfReceived(const TFMsg &tf);
    void pointCloudReceived(const PointCloudMsg &cloud);
    void parameterResponse(const QString &key, const QVariant &value);
    void parseError(const QString &error);

private:
    QByteArray m_buffer;
    
    bool parsePacket(const QByteArray &packet);
    bool parseLaserScan(const QByteArray &data);
    bool parseTF(const QByteArray &data);
    bool parsePointCloud(const QByteArray &data);
    bool parseParameterResponse(const QByteArray &data);
    
    quint16 calculateChecksum(const QByteArray &data) const;
    bool validatePacket(const QByteArray &packet) const;
};

#endif // PROTOCOLPARSER_H