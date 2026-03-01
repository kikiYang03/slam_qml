import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    color: "#000000"

    // 对外暴露的属性
    property bool isRunning: false
    property int fps: 30
    property int pointCount: 0
    property real updateRate: 0
    property string status: "就绪"

    // 可视化参数
    property real scale: 50.0  // 像素/米
    property real centerX: width / 2
    property real centerY: height / 2
    property real maxRange: 10.0

    // 数据存储
    property var laserPoints: []
    property var robotPose: ({ x: 0, y: 0, theta: 0 })

    function clearData() {
        laserPoints = []
        pointCount = 0
        canvas.requestPaint()
    }

    function saveScreenshot() {
        canvas.save("screenshot_2d.png")
    }

    // 坐标转换函数
    function worldToScreen(worldX, worldY) {
        return {
            x: centerX + worldX * scale,
            y: centerY - worldY * scale  // Y轴翻转
        }
    }

    Canvas {
        id: canvas
        anchors.fill: parent
        
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            
            // 绘制网格
            drawGrid(ctx)
            
            // 绘制坐标轴
            drawAxes(ctx)
            
            // 绘制激光点
            drawLaserPoints(ctx)
            
            // 绘制机器人
            drawRobot(ctx)
        }
        
        function drawGrid(ctx) {
            ctx.strokeStyle = "#333333"
            ctx.lineWidth = 1
            
            var gridSize = scale // 1米网格
            
            // 垂直线
            for (var x = centerX % gridSize; x < width; x += gridSize) {
                ctx.beginPath()
                ctx.moveTo(x, 0)
                ctx.lineTo(x, height)
                ctx.stroke()
            }
            
            // 水平线
            for (var y = centerY % gridSize; y < height; y += gridSize) {
                ctx.beginPath()
                ctx.moveTo(0, y)
                ctx.lineTo(width, y)
                ctx.stroke()
            }
        }
        
        function drawAxes(ctx) {
            ctx.strokeStyle = "#666666"
            ctx.lineWidth = 2
            
            // X轴
            ctx.beginPath()
            ctx.moveTo(0, centerY)
            ctx.lineTo(width, centerY)
            ctx.stroke()
            
            // Y轴
            ctx.beginPath()
            ctx.moveTo(centerX, 0)
            ctx.lineTo(centerX, height)
            ctx.stroke()
        }
        
        function drawLaserPoints(ctx) {
            if (laserPoints.length === 0) return
            
            ctx.fillStyle = "#00ff00"
            
            for (var i = 0; i < laserPoints.length; i++) {
                var point = laserPoints[i]
                var screen = worldToScreen(point.x, point.y)
                
                if (screen.x >= 0 && screen.x <= width && 
                    screen.y >= 0 && screen.y <= height) {
                    ctx.beginPath()
                    ctx.arc(screen.x, screen.y, 2, 0, 2 * Math.PI)
                    ctx.fill()
                }
            }
        }
        
        function drawRobot(ctx) {
            var robotScreen = worldToScreen(robotPose.x, robotPose.y)
            
            ctx.save()
            ctx.translate(robotScreen.x, robotScreen.y)
            ctx.rotate(-robotPose.theta) // 负号因为屏幕Y轴翻转
            
            // 绘制机器人本体（矩形）
            ctx.fillStyle = "#ff0000"
            ctx.fillRect(-15, -10, 30, 20)
            
            // 绘制方向指示（三角形）
            ctx.fillStyle = "#ffff00"
            ctx.beginPath()
            ctx.moveTo(15, 0)
            ctx.lineTo(5, -8)
            ctx.lineTo(5, 8)
            ctx.closePath()
            ctx.fill()
            
            ctx.restore()
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
            
            // 模拟数据更新（实际应该从协议解析器获取）
            if (root.isRunning) {
                generateTestData()
                canvas.requestPaint()
            }
        }
    }

    // 生成测试数据
    function generateTestData() {
        var points = []
        var angleStep = Math.PI * 2 / 360 // 1度步长
        
        for (var i = 0; i < 360; i++) {
            var angle = i * angleStep
            var range = 3 + Math.sin(Date.now() / 1000 + angle * 5) * 2 // 模拟动态障碍物
            
            if (range > 0.1 && range < maxRange) {
                points.push({
                    x: range * Math.cos(angle),
                    y: range * Math.sin(angle)
                })
            }
        }
        
        laserPoints = points
        pointCount = points.length
        status = "运行中"
    }

    // 鼠标交互
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
                
                root.centerX += deltaX
                root.centerY += deltaY
                
                lastX = mouseX
                lastY = mouseY
                
                canvas.requestPaint()
            }
        }
        
        onWheel: {
            var scaleFactor = wheel.angleDelta.y > 0 ? 1.1 : 0.9
            root.scale *= scaleFactor
            
            // 限制缩放范围
            root.scale = Math.max(10, Math.min(200, root.scale))
            
            canvas.requestPaint()
        }
    }

    // 控制面板
    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        width: 200
        height: 150
        color: "#2c3e50"
        opacity: 0.8
        radius: 5

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5

            Text {
                text: "2D激光雷达视图"
                color: "white"
                font.bold: true
            }

            Text {
                text: "缩放: " + root.scale.toFixed(1) + "px/m"
                color: "white"
                font.pixelSize: 12
            }

            Text {
                text: "范围: " + root.maxRange.toFixed(1) + "m"
                color: "white"
                font.pixelSize: 12
            }

            Text {
                text: "点数: " + root.pointCount
                color: "white"
                font.pixelSize: 12
            }

            Rectangle {
                width: parent.width
                height: 1
                color: "#34495e"
            }

            Text {
                text: "鼠标拖拽: 平移视图"
                color: "#bdc3c7"
                font.pixelSize: 10
            }

            Text {
                text: "滚轮: 缩放视图"
                color: "#bdc3c7"
                font.pixelSize: 10
            }
        }
    }
}