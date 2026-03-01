import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ScrollView {
    id: root
    property int productType: 0

    ColumnLayout {
        width: root.width
        spacing: 20

        Text {
            text: "参数配置"
            font.pixelSize: 24
            font.bold: true
            color: "#2c3e50"
        }

        // 参数操作按钮
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "加载配置"
                onClicked: fileDialog.open()
            }

            Button {
                text: "保存配置"
                onClicked: {
                    Services.parameterService().saveToFile("config.json")
                }
            }

            Button {
                text: "下发参数"
                enabled: Services.deviceConnection().connectionState === 2
                onClicked: {
                    var packet = Services.parameterService().buildAllParametersPacket()
                    Services.deviceConnection().sendData(packet)
                }
            }

            Item { Layout.fillWidth: true }

            Button {
                text: "恢复默认"
                onClicked: confirmDialog.open()
            }
        }

        // 基础参数组
        GroupBox {
            Layout.fillWidth: true
            title: "基础参数"

            GridLayout {
                anchors.fill: parent
                columns: 2
                columnSpacing: 20
                rowSpacing: 15

                Label { text: "设备ID:" }
                SpinBox {
                    Layout.fillWidth: true
                    from: 1
                    to: 255
                    value: Services.parameterService().getParameter("device_id", 1)
                    onValueChanged: Services.parameterService().setParameter("device_id", value)
                }

                Label { text: "波特率:" }
                ComboBox {
                    Layout.fillWidth: true
                    model: [9600, 19200, 38400, 57600, 115200, 230400]
                    currentIndex: {
                        var rate = Services.parameterService().getParameter("baud_rate", 115200)
                        return model.indexOf(rate)
                    }
                    onCurrentValueChanged: Services.parameterService().setParameter("baud_rate", currentValue)
                }

                Label { text: "超时时间(ms):" }
                SpinBox {
                    Layout.fillWidth: true
                    from: 100
                    to: 30000
                    stepSize: 100
                    value: Services.parameterService().getParameter("timeout", 5000)
                    onValueChanged: Services.parameterService().setParameter("timeout", value)
                }
            }
        }

        // 扫描参数组
        GroupBox {
            Layout.fillWidth: true
            title: "扫描参数"

            GridLayout {
                anchors.fill: parent
                columns: 2
                columnSpacing: 20
                rowSpacing: 15

                Label { text: "最大距离(m):" }
                SpinBox {
                    Layout.fillWidth: true
                    from: 1
                    to: 1000
                    value: Services.parameterService().getParameter("max_range", 100)
                    onValueChanged: Services.parameterService().setParameter("max_range", value)
                }

                Label { text: "最小距离(m):" }
                DoubleSpinBox {
                    Layout.fillWidth: true
                    realFrom: 0.01
                    realTo: 10.0
                    realStepSize: 0.01
                    decimals: 2
                    realValue: Services.parameterService().getParameter("min_range", 0.1)
                    onRealValueChanged: Services.parameterService().setParameter("min_range", realValue)
                }

                Label { text: "扫描频率(Hz):" }
                DoubleSpinBox {
                    Layout.fillWidth: true
                    realFrom: 0.1
                    realTo: 100.0
                    realStepSize: 0.1
                    decimals: 1
                    realValue: Services.parameterService().getParameter("scan_frequency", 10.0)
                    onRealValueChanged: Services.parameterService().setParameter("scan_frequency", realValue)
                }

                Label { text: "分辨率(m):" }
                DoubleSpinBox {
                    Layout.fillWidth: true
                    realFrom: 0.001
                    realTo: 1.0
                    realStepSize: 0.001
                    decimals: 3
                    realValue: Services.parameterService().getParameter("resolution", 0.01)
                    onRealValueChanged: Services.parameterService().setParameter("resolution", realValue)
                }
            }
        }

        // 3D特有参数（仅在3D模式下显示）
        GroupBox {
            Layout.fillWidth: true
            title: "3D参数"
            visible: root.productType === 1

            GridLayout {
                anchors.fill: parent
                columns: 2
                columnSpacing: 20
                rowSpacing: 15

                Label { text: "垂直视场角(°):" }
                SpinBox {
                    Layout.fillWidth: true
                    from: 1
                    to: 180
                    value: Services.parameterService().getParameter("vertical_fov", 30)
                    onValueChanged: Services.parameterService().setParameter("vertical_fov", value)
                }

                Label { text: "垂直分辨率(°):" }
                DoubleSpinBox {
                    Layout.fillWidth: true
                    realFrom: 0.1
                    realTo: 10.0
                    realStepSize: 0.1
                    decimals: 1
                    realValue: Services.parameterService().getParameter("vertical_resolution", 1.0)
                    onRealValueChanged: Services.parameterService().setParameter("vertical_resolution", realValue)
                }

                Label { text: "点云密度:" }
                ComboBox {
                    Layout.fillWidth: true
                    model: ["低", "中", "高", "超高"]
                    currentIndex: Services.parameterService().getParameter("point_density", 1)
                    onCurrentIndexChanged: Services.parameterService().setParameter("point_density", currentIndex)
                }
            }
        }

        // 参数状态显示
        GroupBox {
            Layout.fillWidth: true
            title: "参数状态"

            TextArea {
                anchors.fill: parent
                readOnly: true
                text: {
                    var params = Services.parameterService().getAllParameters()
                    var result = ""
                    for (var key in params) {
                        result += key + ": " + params[key] + "\n"
                    }
                    return result
                }
            }
        }

        Item { Layout.fillHeight: true }
    }

    // 文件对话框（简化版，实际需要使用FileDialog）
    Dialog {
        id: fileDialog
        title: "选择配置文件"
        standardButtons: Dialog.Ok | Dialog.Cancel
        
        TextField {
            id: filePathField
            placeholderText: "输入文件路径..."
            anchors.fill: parent
        }
        
        onAccepted: {
            if (filePathField.text.length > 0) {
                Services.parameterService().loadFromFile(filePathField.text)
            }
        }
    }

    // 确认对话框
    Dialog {
        id: confirmDialog
        title: "确认操作"
        standardButtons: Dialog.Yes | Dialog.No
        
        Text {
            text: "确定要恢复默认参数吗？这将覆盖当前所有参数设置。"
            anchors.fill: parent
        }
        
        onAccepted: {
            // 重新初始化参数服务
            // Services.parameterService().resetToDefaults()
        }
    }

    // 双精度SpinBox组件
    component DoubleSpinBox: SpinBox {
        property real realValue: value / 100.0
        property real realFrom: from / 100.0
        property real realTo: to / 100.0
        property real realStepSize: stepSize / 100.0
        property int decimals: 2


        from: realFrom * 100
        to: realTo * 100
        stepSize: realStepSize * 100

        Component.onCompleted: {
            value = realValue * 100
        }

        onRealValueChanged: {
            if (Math.abs(value - realValue * 100) > 0.5) {
                value = realValue * 100
            }
        }

        validator: DoubleValidator {
            bottom: Math.min(parent.realFrom, parent.realTo)
            top: Math.max(parent.realFrom, parent.realTo)
        }

        textFromValue: function(value, locale) {
            return Number(value / 100).toLocaleString(locale, 'f', decimals)
        }

        valueFromText: function(text, locale) {
            return Number.fromLocaleString(locale, text) * 100
        }
    }
}
