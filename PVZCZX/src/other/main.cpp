#include <QApplication>
#include "mainwindow.h"
#include "../simpleQtLogger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create and initialize SimpleQtLogger instance
    simpleqtlogger::SimpleQtLogger::createInstance(&a)->setLogFileName("testSimpleQtLogger.log", 10*1000*1000, 20);
    simpleqtlogger::ENABLE_LOG_SINK_FILE = true;
    simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_DEBUG = true;
    simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_INFO = true;

    MainWindow w;
    // Set size and title of the window
    w.setFixedSize(900, 600);
    w.setWindowTitle("PlantsVsZombies");

    // Set the main window as the parent object for the logger instance
    simpleqtlogger::SimpleQtLogger::getInstance()->setParent(&w);

    w.show();

    // Log an info message
    L_DEBUG("Game started");

    QObject::connect(&a, &QApplication::aboutToQuit, [&]() {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(&w, "Quit", "For sure to quit game?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // 如果用户点击了"确定"按钮，关闭应用程序
                L_WARN("Quit game without save");
                a.quit();
            } else {
                // 如果用户点击了"取消"按钮，取消退出操作
                // 这里可以添加一些逻辑来处理取消退出的情况
            }
        });

    return a.exec();
}
