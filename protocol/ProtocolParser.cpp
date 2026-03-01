#include "ProtocolParser.h"
#include <QDataStream>
#include <QDebug>
#include <QVector3D>
#include <QColor>

ProtocolParser::ProtocolParser(QObject *parent)
    : QObject(parent)
{
}

void ProtocolParser::parseData(const QByteArray &data)
{
    m_buffer.append(data);
    
    // 查找完整的数据包
    while (m_buffer.size() >= 4) { // 最小包头长度
        // 查找包头 0xAA 0x55
        int headerIndex = -1;
        for (int i = 0; i <= m_buffer.size() - 2; ++i) {
            if (static_cast<quint8>(m_buffer[i]) == 0xAA && 
                static_cast<quint8>(m_buffer[i + 1]) == 0x55) {
                headerIndex = i;
                break;
            }
        }
        
        if (headerIndex == -1) {
            // 没有找到包头，清空缓冲区
            m_buffer.clear();
            break;
        }
        
        // 移除包头前的无效数据
        if (headerIndex > 0) {
            m_buffer.remove(0, headerIndex);
        }
        
        // 检查是否有足够的数据读取包长度
        if (m_buffer.size() < 4) {
            break;
        }
        
        // 读取包长度（包含包头）
        quint16 packetLength = (static_cast<quint8>(m_buffer[2]) << 8) | static_cast<quint8>(m_buffer[3]);
        
        if (packetLength < 4 || packetLength > 65535) {
            // 无效的包长度，移除当前包头继续查找
            m_buffer.remove(0, 2);
            continue;
        }
        
        // 检查是否接收到完整的包
        if (m_buffer.size() < packetLength) {
            break; // 等待更多数据
        }
        
        // 提取完整的包
        QByteArray packet = m_buffer.left(packetLength);
        m_buffer.remove(0, packetLength);
        
        // 解析包
        if (!parsePacket(packet)) {
            emit parseError("Failed to parse packet");
        }
    }
}

bool ProtocolParser::parsePacket(const QByteArray &packet)
{
    if (packet.size() < 6) { // 最小包：头(2) + 长度(2) + 类型(1) + 校验(1)
        return false;
    }
    
    if (!validatePacket(packet)) {
        return false;
    }
    
    quint8 messageType = static_cast<quint8>(packet[4]);
    QByteArray payload = packet.mid(5, packet.size() - 6); // 去掉头、长度、类型和校验
    
    switch (messageType) {
    case 0x01: // LaserScan
        return parseLaserScan(payload);
    case 0x02: // TF
        return parseTF(payload);
    case 0x03: // PointCloud
        return parsePointCloud(payload);
    case 0x04: // Parameter Response
        return parseParameterResponse(payload);
    default:
        return false;
    }
}

bool ProtocolParser::parseLaserScan(const QByteArray &data)
{
    if (data.size() < 28) { // 基本字段大小
        return false;
    }
    
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    
    LaserScanMsg scan;
    stream >> scan.angle_min >> scan.angle_max >> scan.angle_increment
           >> scan.time_increment >> scan.scan_time >> scan.range_min >> scan.range_max;
    
    quint32 rangeCount;
    stream >> rangeCount;
    
    scan.ranges.resize(rangeCount);
    for (quint32 i = 0; i < rangeCount; ++i) {
        stream >> scan.ranges[i];
    }
    
    quint32 intensityCount;
    stream >> intensityCount;
    
    scan.intensities.resize(intensityCount);
    for (quint32 i = 0; i < intensityCount; ++i) {
        stream >> scan.intensities[i];
    }
    
    emit laserScanReceived(scan);
    return true;
}

bool ProtocolParser::parseTF(const QByteArray &data)
{
    if (data.size() < 64) { // 基本TF数据大小
        return false;
    }
    
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    
    TFMsg tf;
    
    // 读取frame_id长度和内容
    quint16 frameIdLength;
    stream >> frameIdLength;
    if (frameIdLength > 0) {
        QByteArray frameIdBytes(frameIdLength, 0);
        stream.readRawData(frameIdBytes.data(), frameIdLength);
        tf.frame_id = QString::fromUtf8(frameIdBytes);
    }
    
    // 读取child_frame_id长度和内容
    quint16 childFrameIdLength;
    stream >> childFrameIdLength;
    if (childFrameIdLength > 0) {
        QByteArray childFrameIdBytes(childFrameIdLength, 0);
        stream.readRawData(childFrameIdBytes.data(), childFrameIdLength);
        tf.child_frame_id = QString::fromUtf8(childFrameIdBytes);
    }
    
    stream >> tf.timestamp >> tf.translation_x >> tf.translation_y >> tf.translation_z
           >> tf.rotation_x >> tf.rotation_y >> tf.rotation_z >> tf.rotation_w;
    
    emit tfReceived(tf);
    return true;
}

bool ProtocolParser::parsePointCloud(const QByteArray &data)
{
    if (data.size() < 16) {
        return false;
    }
    
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    
    PointCloudMsg cloud;
    
    // 读取frame_id
    quint16 frameIdLength;
    stream >> frameIdLength;
    if (frameIdLength > 0) {
        QByteArray frameIdBytes(frameIdLength, 0);
        stream.readRawData(frameIdBytes.data(), frameIdLength);
        cloud.frame_id = QString::fromUtf8(frameIdBytes);
    }
    
    double timestamp;
    stream >> timestamp;
    cloud.timestamp = timestamp;
    
    // 读取点数量
    quint32 pointCount;
    stream >> pointCount;
    
    cloud.points.resize(pointCount);
    cloud.colors.resize(pointCount);
    
    for (quint32 i = 0; i < pointCount; ++i) {
        float x, y, z;
        stream >> x >> y >> z;
        cloud.points[i] = QVector3D(x, y, z);
        
        quint8 r, g, b;
        stream >> r >> g >> b;
        cloud.colors[i] = QColor(r, g, b);
    }
    
    emit pointCloudReceived(cloud);
    return true;
}

bool ProtocolParser::parseParameterResponse(const QByteArray &data)
{
    if (data.size() < 4) {
        return false;
    }
    
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    
    quint16 keyLength;
    stream >> keyLength;
    
    QByteArray keyBytes(keyLength, 0);
    stream.readRawData(keyBytes.data(), keyLength);
    QString key = QString::fromUtf8(keyBytes);
    
    quint16 valueLength;
    stream >> valueLength;
    
    QByteArray valueBytes(valueLength, 0);
    stream.readRawData(valueBytes.data(), valueLength);
    QString valueStr = QString::fromUtf8(valueBytes);
    
    // 尝试转换为合适的类型
    QVariant value;
    bool ok;
    
    // 尝试整数
    int intValue = valueStr.toInt(&ok);
    if (ok) {
        value = intValue;
    } else {
        // 尝试浮点数
        double doubleValue = valueStr.toDouble(&ok);
        if (ok) {
            value = doubleValue;
        } else {
            // 作为字符串
            value = valueStr;
        }
    }
    
    emit parameterResponse(key, value);
    return true;
}

quint16 ProtocolParser::calculateChecksum(const QByteArray &data) const
{
    quint16 checksum = 0;
    for (int i = 0; i < data.size(); ++i) {
        checksum ^= static_cast<quint8>(data[i]);
    }
    return checksum;
}

bool ProtocolParser::validatePacket(const QByteArray &packet) const
{
    if (packet.size() < 6) {
        return false;
    }
    
    // 验证包头
    if (static_cast<quint8>(packet[0]) != 0xAA || static_cast<quint8>(packet[1]) != 0x55) {
        return false;
    }
    
    // 验证长度
    quint16 declaredLength = (static_cast<quint8>(packet[2]) << 8) | static_cast<quint8>(packet[3]);
    if (declaredLength != packet.size()) {
        return false;
    }
    
    // 验证校验和
    QByteArray dataToCheck = packet.mid(0, packet.size() - 1);
    quint8 declaredChecksum = static_cast<quint8>(packet.at(packet.size() - 1));
    quint8 calculatedChecksum = calculateChecksum(dataToCheck) & 0xFF;
    
    return declaredChecksum == calculatedChecksum;
}

QByteArray ProtocolParser::buildTestPacket(const QString &type, const QVariantMap &data)
{
    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    
    // 包头
    packet.append(static_cast<char>(0xAA));
    packet.append(static_cast<char>(0x55));
    
    // 预留长度位置
    int lengthPos = packet.size();
    packet.append(static_cast<char>(0x00));
    packet.append(static_cast<char>(0x00));
    
    // 消息类型
    if (type == "LaserScan") {
        packet.append(static_cast<char>(0x01));
    } else if (type == "TF") {
        packet.append(static_cast<char>(0x02));
    } else if (type == "PointCloud") {
        packet.append(static_cast<char>(0x03));
    } else if (type == "Parameter") {
        packet.append(static_cast<char>(0x04));
    } else {
        return QByteArray(); // 未知类型
    }
    
    // 添加测试数据（简化实现）
    if (type == "LaserScan") {
        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
        stream << 0.0f << 6.28f << 0.01f << 0.0f << 0.1f << 0.1f << 100.0f;
        stream << quint32(10); // 10个距离值
        for (int i = 0; i < 10; ++i) {
            stream << float(i + 1.0);
        }
        stream << quint32(10); // 10个强度值
        for (int i = 0; i < 10; ++i) {
            stream << float(100.0 + i);
        }
    }
    
    // 设置实际长度
    quint16 actualLength = packet.size() + 1; // +1 for checksum
    packet[lengthPos] = (actualLength >> 8) & 0xFF;
    packet[lengthPos + 1] = actualLength & 0xFF;
    
    // 计算并添加校验和
    quint8 checksum = 0;
    for (int i = 0; i < packet.size(); ++i) {
        checksum ^= static_cast<quint8>(packet[i]);
    }
    packet.append(static_cast<char>(checksum));
    
    return packet;
}