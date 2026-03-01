import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    color: "#1a1a1a"

    // 对外暴露的属性
    property bool isRunning: false
    property int fps: 30
    property int pointCount: 0
    property real updateRate: 0
    property string status: "就绪"

    // 3D视图参数
    property real cameraDistance: 10.0
    property real cameraAngleX: 30.0
    property real cameraAngleY: 45.0
    property real pointSize: 2.0

    function clearData() {
        pointCount = 0
        status = "已清空"
    }

    function saveScreenshot() {
        // 3D截图功能需要OpenGL支持
        status = "截图已保存"
    }

    // 3D渲染区域（占位符，实际需要OpenGL实现）
    Rectangle {
        anchors.fill: parent
        color: "#000000"
        
        // 模拟3D点云显示
        Repeater {
            model: Math.min(pointCount, 1000) // 限制显示点数以提高性能
            
            Rectangle {
                width: root.pointSize
                height: root.pointSize
                radius: root.pointSize / 2
                color: Qt.hsla(index / model * 0.8, 0.8, 0.6, 0.8)
                
                // 模拟3D投影位置
                x: parent.width / 2 + (index % 50 - 25) * 8 + Math.sin(index * 0.1) * 50
                y: parent.height / 2 + Math.floor(index / 50) * 8 + Math.cos(index * 0.1) * 30
                
                // 简单的深度效果
                scale: 0.5 + 0.5 * Math.sin(index * 0.05)
                
                Behavior on x { NumberAnimation { duration: 100 } }
                Behavior on y { NumberAnimation { duration: 100 } }
                Behavior on scale { NumberAnimation { duration: 100 } }
            }
        }
        
        // 坐标轴指示器
        Item {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 20
            width: 100
            height: 100
            
            // X轴 (红色)
            Rectangle {
                width: 50
                height: 2
                color: "#ff0000"
                anchors.centerIn: parent
                transformOrigin: Item.Left
            }
            
            // Y轴 (绿色)
            Rectangle {
                width: 2
                height: 50
                color: "#00ff00"
                anchors.centerIn: parent
                transformOrigin: Item.Top
            }
            
            // Z轴 (蓝色) - 模拟透视
            Rectangle {
                width: 35
                height: 2
                color: "#0000ff"
                anchors.centerIn: parent
                transformOrigin: Item.Left
                rotation: -30
            }
            
            Text {
                text: "X"
                color: "#ff0000"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
            
            Text {
                text: "Y"
                color: "#00ff00"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
            }
            
            Text {
                text: "Z"
                color: "#0000ff"
                anchors.right: parent.right
                anchors.top: parent.top
            }
        }
    }

    // 更新定时器
    Timer {
        id: updateTimer
        interval: 1000 / fps
        running: root.isRunning
        repeat: true
        
        property int frameCount: 0
        property real lastTime: Date.now()
        
        onTriggered: {
            frameCount++
            var currentTime = Date.now()
            
            if (currentTime - lastTime >= 1000) {
                root.updateRate = frameCount
                frameCount = 0
                lastTime = currentTime
            }
            
            // 模拟3D数据更新
            if (root.isRunning) {
                generateTest3DData()
            }
        }
    }

    // 生成测试3D数据
    function generateTest3DData() {
        // 模拟动态点云数据
        var time = Date.now() / 1000
        pointCount = 500 + Math.sin(time) * 200
        status = "3D渲染中"
    }

    // 鼠标交互控制视角
    MouseArea {
        anchors.fill: parent
        
        property real lastX: 0
        property real lastY: 0
        
        onPressed: {
            lastX = mouseX
            lastY = mouseY
        }
        
        onPositionChanged: {
            if (pressed) {
                var deltaX = mouseX - lastX
                var deltaY = mouseY - lastY
                
                root.cameraAngleY += deltaX * 0.5
                root.cameraAngleX += deltaY * 0.5
                
                // 限制X轴旋转角度
                root.cameraAngleX = Math.max(-90, Math.min(90, root.cameraAngleX))
                
                lastX = mouseX
                lastY = mouseY
            }
        }
        
        onWheel: {
            var scaleFactor = wheel.angleDelta.y > 0 ? 0.9 : 1.1
            root.cameraDistance *= scaleFactor
            
            // 限制缩放范围
            root.cameraDistance = Math.max(1, Math.min(50, root.cameraDistance))
        }
    }

    // 3D控制面板
    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        width: 220
        height: 200
        color: "#2c3e50"
        opacity: 0.9
        radius: 5

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 8

            Text {
                text: "3D点云视图"
                color: "white"
                font.bold: true
                font.pixelSize: 14
            }

            Rectangle {
                width: parent.width
                height: 1
                color: "#34495e"
            }

            Text {
                text: "相机距离: " + root.cameraDistance.toFixed(1)
                color: "white"
                font.pixelSize: 12
            }

            Text {
                text: "俯仰角: " + root.cameraAngleX.toFixed(1) + "°"
                color: "white"
                font.pixelSize: 12
            }

            Text {
                text: "方位角: " + root.cameraAngleY.toFixed(1) + "°"
                color: "white"
                font.pixelSize: 12
            }

            Text {
                text: "点云数量: " + root.pointCount
                color: "white"
                font.pixelSize: 12
            }

            Rectangle {
                width: parent.width
                height: 1
                color: "#34495e"
            }

            Text {
                text: "鼠标拖拽: 旋转视角"
                color: "#bdc3c7"
                font.pixelSize: 10
            }

            Text {
                text: "滚轮: 缩放距离"
                color: "#bdc3c7"
                font.pixelSize: 10
            }

            Rectangle {
                width: parent.width
                height: 1
                color: "#34495e"
            }

            Text {
                text: "注意: 这是3D渲染的简化版本"
                color: "#f39c12"
                font.pixelSize: 10
                wrapMode: Text.WordWrap
                width: parent.width
            }

            Text {
                text: "完整版本需要OpenGL集成"
                color: "#f39c12"
                font.pixelSize: 10
                wrapMode: Text.WordWrap
                width: parent.width
            }
        }
    }

    // 性能指示器
    Rectangle {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 10
        width: 150
        height: 60
        color: "#34495e"
        opacity: 0.8
        radius: 3

        Column {
            anchors.centerIn: parent
            spacing: 5

            Text {
                text: "渲染性能"
                color: "white"
                font.bold: true
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Text {
                text: "FPS: " + root.updateRate
                color: root.updateRate > 25 ? "#27ae60" : "#e74c3c"
                font.pixelSize: 11
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}