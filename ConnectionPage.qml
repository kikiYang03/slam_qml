import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ScrollView {
    id: root
    property int productType: 0

    ColumnLayout {
        width: root.width
        spacing: 20

        // 页面标题
        Text {
            text: "设备连接"
            font.pixelSize: 24
            font.bold: true
            color: "#2c3e50"
        }

        // 连接状态卡片
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            color: "#ffffff"
            border.color: "#e0e0e0"
            border.width: 1
            radius: 8

            RowLayout {
                anchors.fill: parent
                anchors.margins: 20

                Rectangle {
                    width: 60
                    height: 60
                    radius: 30
                    color: "#95a5a6" // 默认为未连接状态

                    Text {
                        anchors.centerIn: parent
                        text: "●"
                        color: "white"
                        font.pixelSize: 24
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 5

                    Text {
                        text: "设备未连接"
                        font.pixelSize: 18
                        font.bold: true
                        color: "#2c3e50"
                    }

                    Text {
                        text: "准备就绪"
                        font.pixelSize: 14
                        color: "#7f8c8d"
                    }
                }

                Button {
                    text: "连接设备"
                    onClicked: {
                        console.log("连接设备按钮被点击")
                    }
                }
            }
        }

        // 连接配置
        GroupBox {
            Layout.fillWidth: true
            title: "连接配置"

            GridLayout {
                anchors.fill: parent
                columns: 2
                columnSpacing: 20
                rowSpacing: 15

                Label {
                    text: "连接类型:"
                    font.bold: true
                }

                ComboBox {
                    id: connectionTypeCombo
                    Layout.fillWidth: true
                    model: ["串口", "TCP", "UDP"]
                    currentIndex: Services.deviceConnection().connectionType
                }

                Label {
                    text: connectionTypeCombo.currentIndex === 0 ? "串口号:" : "IP地址:"
                    font.bold: true
                }

                TextField {
                    id: addressField
                    Layout.fillWidth: true
                    text: Services.deviceConnection().address
                    placeholderText: connectionTypeCombo.currentIndex === 0 ? "COM1" : "192.168.1.100"
                    onTextChanged: Services.deviceConnection().address = text
                }

                Label {
                    text: connectionTypeCombo.currentIndex === 0 ? "波特率:" : "端口:"
                    font.bold: true
                }

                TextField {
                    id: portField
                    Layout.fillWidth: true
                    text: Services.deviceConnection().port.toString()
                    placeholderText: connectionTypeCombo.currentIndex === 0 ? "115200" : "8080"
                    validator: IntValidator { bottom: 1; top: 999999 }
                    onTextChanged: {
                        if (text.length > 0) {
                            Services.deviceConnection().port = parseInt(text)
                        }
                    }
                }
            }
        }

        // 测试区域
        GroupBox {
            Layout.fillWidth: true
            title: "连接测试"

            ColumnLayout {
                anchors.fill: parent
                spacing: 10

                RowLayout {
                    TextField {
                        id: testDataField
                        Layout.fillWidth: true
                        placeholderText: "输入测试数据..."
                    }

                    Button {
                        text: "发送"
                        enabled: Services.deviceConnection().connectionState === 2
                        onClicked: {
                            if (testDataField.text.length > 0) {
                                Services.deviceConnection().sendData(testDataField.text)
                                testDataField.clear()
                            }
                        }
                    }
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 200
                    
                    TextArea {
                        id: logArea
                        readOnly: true
                        wrapMode: TextArea.Wrap
                        placeholderText: "数据日志将显示在这里..."
                        
                        Connections {
                            target: Services.deviceConnection()
                            function onDataReceived(data) {
                                logArea.append(new Date().toLocaleTimeString() + " 接收: " + data)
                            }
                        }
                    }
                }

                Button {
                    text: "清空日志"
                    onClicked: logArea.clear()
                }
            }
        }

        Item { Layout.fillHeight: true }
    }
}