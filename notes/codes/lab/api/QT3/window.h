#include <qmainwindow.h>

// 一个最简单的窗口
class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = 0, const char* name = 0);
    virtual ~MyWindow();
};