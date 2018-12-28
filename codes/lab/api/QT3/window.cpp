#include "window.moc"

#include <qapplication.h>

//----------------------------------------------------------

// implementation

MyWindow::MyWindow(QWidget *parent, const char* name)
    : QMainWindow(parent, name)
{
    this->setCaption("MyWindow");
}

MyWindow::~MyWindow()
{

}

//----------------------------------------------------------

int main(int argc, char **argv)
{
    // QT 应用程序必须有且仅有一个 QApplication
    // 必须在做其他任何事之前创建它
    QApplication app(argc, argv);
    
    MyWindow *window = new MyWindow();

    // 设置应用程序的主构件
    app.setMainWidget(window);

    window->show();

    // 启动事件循环，直到 QApplication::quit() 被调用或主构件被关闭
    return app.exec();
}