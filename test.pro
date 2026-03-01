QT += core serialport network
CONFIG += console
CONFIG -= app_bundle

TARGET = test_services

SOURCES += \
    test_main.cpp \
    services/CommunicationService.cpp \
    services/ParameterService.cpp \
    protocol/ProtocolParser.cpp \
    models/DeviceConnectionModel.cpp \
    core/ServiceManager.cpp

HEADERS += \
    services/ICommunicationService.h \
    services/CommunicationService.h \
    services/ParameterService.h \
    protocol/ProtocolParser.h \
    models/DeviceConnectionModel.h \
    core/ServiceManager.h