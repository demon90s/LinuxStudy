#include <qmainwindow.h>
#include <qpushbutton.h>

// 信号和槽构成了 QT 程序的事件处理机制
// 需要使用伪关键字 signals 和 slots
// 通过 QObject::connect 方法将信号连接到槽
// 即，当发送一个信号的时候，可以呼叫槽对应的函数

// 要发出一个信号，调用： emit signalFunction();

// bool QObject::connect(const QObject *sender, const char *signal,
//                       const QObject *receiver, const char *member);

// 一个最简单的窗口，具有信号和槽
class WindowWithSignalSlot : public QMainWindow
{
    Q_OBJECT

public:
    WindowWithSignalSlot(QWidget *parent = 0, const char* name = 0);
    virtual ~WindowWithSignalSlot();

signals:
    void SignalA();

private slots:
    void OnButtonClicked();         // on m_button clicked
    void onRecvSignalA();

private:
    QPushButton *m_button;
};