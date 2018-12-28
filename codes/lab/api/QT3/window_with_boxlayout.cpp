#include "window_with_boxlayout.moc"

#include <qapplication.h>
#include <qlayout.h>
#include <qlabel.h>

//--------------------------------------------------------------------

// implementation

WindowWithBoxLayout::WindowWithBoxLayout(QWidget *parent, const char *name)
    : QMainWindow(parent, name), m_layout_widget(0)
{
    m_layout_widget = new QWidget(this);
    setCentralWidget(m_layout_widget);

    // 创建三个 Label ，放到 QVBoxLayout 里面去
    QVBoxLayout *v_layout = new QVBoxLayout(m_layout_widget, 0, 0, "v_layout");
    
    QLabel *label1 = new QLabel("label1", m_layout_widget, "label1");
    QLabel *label2 = new QLabel("label2", m_layout_widget, "label2");
    QLabel *label3 = new QLabel("label3", m_layout_widget, "label3");

    v_layout->addWidget(label1);
    v_layout->addWidget(label2);
    v_layout->addWidget(label3);
}

WindowWithBoxLayout::~WindowWithBoxLayout()
{

}

//--------------------------------------------------------------------

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    WindowWithBoxLayout *window = new WindowWithBoxLayout();
    app.setMainWidget(window);

    window->show();

    return app.exec();
}