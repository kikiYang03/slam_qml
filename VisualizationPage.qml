import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    property int productType: 0
    color: "#f8f9fa"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            text: "数据可视化"
            font.pixelSize: 24
            font.bold: true
            color: "#2c3e50"
        }

        // 工具栏
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "开始显示"
                checkable: true
                checked: visualizer.isRunning
                onClicked: visualizer.isRunning = checked
            }

            Button {
                text: "清空数据"
                onClicked: visualizer.clearData()
            }

            Button {
                text: "保存截图"
                onClicked: visualizer.saveScreenshot()
            }

            Item { Layout.fillWidth: true }

            Text {
                text: "FPS: " + visualizer.fps
                color: "#666666"
            }
        }

        // 可视化区域
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#ffffff"
            border.color: "#e0e0e0"
            border.width: 1
            radius: 8

            // 根据产品类型选择不同的可视化组件
            Loader {
                id: visualizerLoader
                anchors.fill: parent
                anchors.margins: 10
                source: root.productType === 0 ? "Visualizer2D.qml" : "Visualizer3D.qml"
            }

            // 加载指示器
            BusyIndicator {
                anchors.centerIn: parent
                visible: visualizerLoader.status === Loader.Loading
            }

            // 错误提示
            Text {
                anchors.centerIn: parent
                text: "可视化组件加载失败"
                visible: visualizerLoader.status === Loader.Error
                color: "#e74c3c"
                font.pixelSize: 16
            }
        }

        // 状态栏
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            color: "#ecf0f1"
            radius: 4

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: "数据点数: " + (visualizer.pointCount || 0)
                    color: "#2c3e50"
                }

                Rectangle {
                    width: 1
                    height: 20
                    color: "#bdc3c7"
                }

                Text {
                    text: "更新频率: " + (visualizer.updateRate || 0) + " Hz"
                    color: "#2c3e50"
                }

                Rectangle {
                    width: 1
                    height: 20
                    color: "#bdc3c7"
                }

                Text {
                    text: "状态: " + (visualizer.status || "就绪")
                    color: "#2c3e50"
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: new Date().toLocaleTimeString()
                    color: "#7f8c8d"
                }
            }
        }
    }

    // 可视化器属性（由子组件提供）
    property alias visualizer: visualizerLoader.item
}