import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 1200
    height: 800
    visible: true
    title: qsTr("2D/3D综合项目")

    property int currentProduct: -1 // -1: 未选择, 0: 2D, 1: 3D

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: currentProduct === -1 ? productSelector : mainNavigation
    }

    Component {
        id: productSelector
        ProductSelector {
            onProductSelected: {
                root.currentProduct = productType
                stackView.replace(mainNavigation)
            }
        }
    }

    Component {
        id: mainNavigation
        MainNavigation {
            productType: root.currentProduct
            onBackToSelector: {
                root.currentProduct = -1
                stackView.replace(productSelector)
            }
        }
    }
}
