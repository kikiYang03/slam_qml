# 2D/3D综合项目 - QML重构版本

## 项目概述

本项目是对原有2D和3D QWidget项目的现代化重构，采用QML前端 + C++后端的架构模式。

## 架构设计

### 核心服务层 (Services)
- **CommunicationService**: 统一的通信服务，支持串口、TCP、UDP
- **ParameterService**: 参数管理服务，支持参数读取、设置、持久化
- **ProtocolParser**: 协议解析器，处理ROS消息解析

### 数据模型层 (Models)
- **DeviceConnectionModel**: 设备连接状态管理，暴露给QML使用

### 服务管理 (Core)
- **ServiceManager**: 单例服务管理器，负责服务初始化和依赖注入

### QML界面层
- **ProductSelector**: 产品选择器（2D/3D模式切换）
- **MainNavigation**: 主导航框架
- **ConnectionPage**: 设备连接页面
- **ParameterPage**: 参数配置页面
- **VisualizationPage**: 数据可视化页面
- **Visualizer2D/3D**: 2D和3D可视化组件

## 技术特性

### 已实现功能
1. ✅ 完整的服务层架构
2. ✅ 通信服务（串口/TCP/UDP）
3. ✅ 参数管理系统
4. ✅ 协议解析框架
5. ✅ QML界面框架
6. ✅ 产品模式切换
7. ✅ 设备连接管理
8. ✅ 参数配置界面
9. ✅ 2D可视化组件（Canvas实现）
10. ✅ 3D可视化组件（简化版）

### 待完善功能
1. 🔄 OpenGL 3D渲染集成
2. 🔄 多线程数据处理
3. 🔄 ROS消息完整解析
4. 🔄 文件对话框集成
5. 🔄 单元测试

## 文件结构

```
qmlProject/
├── main.cpp                    # 应用入口
├── main.qml                    # QML主界面
├── ProductSelector.qml         # 产品选择器
├── MainNavigation.qml          # 主导航
├── ConnectionPage.qml          # 连接页面
├── ParameterPage.qml           # 参数页面
├── VisualizationPage.qml       # 可视化页面
├── Visualizer2D.qml           # 2D可视化
├── Visualizer3D.qml           # 3D可视化
├── services/                   # 服务层
│   ├── ICommunicationService.h
│   ├── CommunicationService.h/cpp
│   └── ParameterService.h/cpp
├── protocol/                   # 协议层
│   └── ProtocolParser.h/cpp
├── models/                     # 数据模型
│   └── DeviceConnectionModel.h/cpp
└── core/                       # 核心管理
    └── ServiceManager.h/cpp
```

## 编译说明

### 主项目（QML版本）
```bash
qmake qmlProject.pro
make
```

### 测试项目（控制台版本）
```bash
qmake test.pro
make
./test_services
```

## 使用说明

1. **启动应用**: 运行编译后的可执行文件
2. **选择模式**: 在启动页面选择2D或3D模式
3. **设备连接**: 配置连接参数并连接设备
4. **参数配置**: 设置设备参数
5. **数据可视化**: 查看实时数据渲染

## 技术亮点

### 架构优势
- **完全解耦**: UI与业务逻辑完全分离
- **服务化**: 核心功能模块化，易于测试和维护
- **统一管理**: ServiceManager统一管理所有服务依赖
- **类型安全**: 强类型的数据模型和接口定义

### QML集成
- **属性绑定**: 通过Q_PROPERTY实现数据双向绑定
- **信号槽**: 异步事件处理
- **单例模式**: 全局服务访问
- **组件化**: 可复用的UI组件

### 扩展性
- **接口设计**: 基于接口的服务设计，易于扩展
- **插件架构**: 支持不同协议和渲染引擎
- **配置驱动**: 参数化配置，支持不同设备

## 下一步计划

1. **OpenGL集成**: 实现真正的3D渲染
2. **性能优化**: 多线程数据处理
3. **协议完善**: 完整的ROS消息支持
4. **测试覆盖**: 单元测试和集成测试
5. **文档完善**: API文档和用户手册

## 开发环境

- Qt 5.15.2
- C++17
- QML 2.15
- Windows/Linux/macOS