#include <QCoreApplication>
#include <QDebug>
#include "core/ServiceManager.h"
#include "services/CommunicationService.h"
#include "services/ParameterService.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qDebug() << "Testing Service Architecture...";
    
    // 初始化服务管理器
    ServiceManager::instance()->initialize();
    
    // 测试通信服务
    auto commService = ServiceManager::instance()->communicationService();
    qDebug() << "Communication service state:" << static_cast<int>(commService->getConnectionState());
    
    // 测试参数服务
    auto paramService = ServiceManager::instance()->parameterService();
    paramService->setParameter("test_param", 42);
    qDebug() << "Test parameter:" << paramService->getParameter("test_param");
    
    // 测试设备连接模型
    auto deviceModel = ServiceManager::instance()->deviceConnectionModel();
    qDebug() << "Device model address:" << deviceModel->address();
    
    qDebug() << "All services initialized successfully!";
    
    return 0;
}