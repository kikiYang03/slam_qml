@echo off
echo ========================================
echo 2D/3D综合项目 - QML重构版本
echo ========================================

echo.
echo 1. 编译测试项目 (控制台版本)
echo 2. 编译完整项目 (QML版本)
echo 3. 清理构建文件
echo.

set /p choice="请选择操作 (1-3): "

if "%choice%"=="1" (
    echo 正在编译测试项目...
    qmake test.pro
    if %errorlevel% equ 0 (
        nmake
        if %errorlevel% equ 0 (
            echo 测试项目编译成功！
            echo 运行: test_services.exe
        ) else (
            echo 编译失败！
        )
    ) else (
        echo qmake失败！请检查Qt环境配置。
    )
) else if "%choice%"=="2" (
    echo 正在编译QML项目...
    qmake qmlProject.pro
    if %errorlevel% equ 0 (
        nmake
        if %errorlevel% equ 0 (
            echo QML项目编译成功！
            echo 运行: qmlProject.exe
        ) else (
            echo 编译失败！
        )
    ) else (
        echo qmake失败！请检查Qt环境配置。
    )
) else if "%choice%"=="3" (
    echo 清理构建文件...
    if exist Makefile del Makefile
    if exist Makefile.Debug del Makefile.Debug
    if exist Makefile.Release del Makefile.Release
    if exist *.o del *.o
    if exist debug rmdir /s /q debug
    if exist release rmdir /s /q release
    if exist *.exe del *.exe
    echo 清理完成！
) else (
    echo 无效选择！
)

echo.
pause