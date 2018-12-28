#include <qmainwindow.h>

// QVBoxLayout 和 QHBoxLayout 都是不可见对象，分别以垂直和水平方向包含其他的构件和布局

// QMainWindow 不能直接添加 QLayout ，因此需要创建一个抽象的 QWidget 来包含它

class WindowWithBoxLayout : public QMainWindow
{
Q_OBJECT

public:
    WindowWithBoxLayout(QWidget *parent = 0, const char *name = 0);
    virtual ~WindowWithBoxLayout();

private:
    QWidget *m_layout_widget;
};