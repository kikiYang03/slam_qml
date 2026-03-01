import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    color: "#f0f0f0"

    signal productSelected(int productType)

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 40

        Text {
            text: "选择产品模式"
            font.pixelSize: 32
            font.bold: true
            color: "#333333"
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            spacing: 60
            Layout.alignment: Qt.AlignHCenter

            // 2D产品卡片
            Rectangle {
                width: 300
                height: 200
                color: "#ffffff"
                border.color: "#e0e0e0"
                border.width: 2
                radius: 10

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.color = "#f8f8f8"
                    onExited: parent.color = "#ffffff"
                    onClicked: root.productSelected(0)
                }

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 20

                    Rectangle {
                        width: 80
                        height: 80
                        color: "#4CAF50"
                        radius: 40
                        Layout.alignment: Qt.AlignHCenter

                        Text {
                            anchors.centerIn: parent
                            text: "2D"
                            font.pixelSize: 24
                            font.bold: true
                            color: "white"
                        }
                    }

                    Text {
                        text: "2D激光雷达"
                        font.pixelSize: 18
                        font.bold: true
                        color: "#333333"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "平面扫描与建图"
                        font.pixelSize: 14
                        color: "#666666"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }

            // 3D产品卡片
            Rectangle {
                width: 300
                height: 200
                color: "#ffffff"
                border.color: "#e0e0e0"
                border.width: 2
                radius: 10

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: parent.color = "#f8f8f8"
                    onExited: parent.color = "#ffffff"
                    onClicked: root.productSelected(1)
                }

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 20

                    Rectangle {
                        width: 80
                        height: 80
                        color: "#2196F3"
                        radius: 40
                        Layout.alignment: Qt.AlignHCenter

                        Text {
                            anchors.centerIn: parent
                            text: "3D"
                            font.pixelSize: 24
                            font.bold: true
                            color: "white"
                        }
                    }

                    Text {
                        text: "3D点云处理"
                        font.pixelSize: 18
                        font.bold: true
                        color: "#333333"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "立体建模与渲染"
                        font.pixelSize: 14
                        color: "#666666"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
        }

        Text {
            text: "请选择要使用的产品模式"
            font.pixelSize: 16
            color: "#888888"
            Layout.alignment: Qt.AlignHCenter
        }
    }
}