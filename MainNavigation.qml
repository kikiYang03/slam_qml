import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    color: "#f5f5f5"

    property int productType: 0 // 0: 2D, 1: 3D
    signal backToSelector()

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // 左侧导航栏
        Rectangle {
            Layout.preferredWidth: 250
            Layout.fillHeight: true
            color: "#2c3e50"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 5

                // 标题区域
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 60
                    color: "transparent"

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10

                        Rectangle {
                            width: 30
                            height: 30
                            color: root.productType === 0 ? "#4CAF50" : "#2196F3"
                            radius: 15

                            Text {
                                anchors.centerIn: parent
                                text: root.productType === 0 ? "2D" : "3D"
                                color: "white"
                                font.bold: true
                            }
                        }

                        Text {
                            text: root.productType === 0 ? "2D激光雷达" : "3D点云处理"
                            color: "white"
                            font.pixelSize: 16
                            font.bold: true
                        }

                        Item { Layout.fillWidth: true }

                        Button {
                            text: "切换"
                            onClicked: root.backToSelector()
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    height: 1
                    color: "#34495e"
                }

                // 导航菜单
                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: navigationModel
                    delegate: navigationDelegate
                }

                Item { Layout.fillHeight: true }
            }
        }

        // 右侧内容区域
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#ffffff"

            StackView {
                id: contentStack
                anchors.fill: parent
                anchors.margins: 20
                initialItem: connectionPage
            }
        }
    }

    // 导航菜单数据模型
    ListModel {
        id: navigationModel
        ListElement { title: "设备连接"; page: "ConnectionPage"; icon: "🔗" }
        ListElement { title: "参数配置"; page: "ParameterPage"; icon: "⚙️" }
        ListElement { title: "数据可视化"; page: "VisualizationPage"; icon: "📊" }
    }

    // 导航菜单委托
    Component {
        id: navigationDelegate
        Rectangle {
            width: ListView.view.width
            height: 50
            color: mouseArea.containsMouse ? "#34495e" : "transparent"

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    switch(model.page) {
                    case "ConnectionPage":
                        contentStack.replace(connectionPage)
                        break
                    case "ParameterPage":
                        contentStack.replace(parameterPage)
                        break
                    case "VisualizationPage":
                        contentStack.replace(visualizationPage)
                        break
                    }
                }
            }

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 15
                anchors.rightMargin: 15

                Text {
                    text: model.icon
                    font.pixelSize: 18
                }

                Text {
                    text: model.title
                    color: "white"
                    font.pixelSize: 14
                    Layout.fillWidth: true
                }
            }
        }
    }

    // 页面组件
    Component {
        id: connectionPage
        ConnectionPage {
            productType: root.productType
        }
    }

    Component {
        id: parameterPage
        ParameterPage {
            productType: root.productType
        }
    }

    Component {
        id: visualizationPage
        VisualizationPage {
            productType: root.productType
        }
    }
}