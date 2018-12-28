#include "window_with_signal_slot.moc"

#include <iostream>
#include <qapplication.h>

//------------------------------------------------------------

// implementation

WindowWithSignalSlot::WindowWithSignalSlot(QWidget *parent, const char* name)
    : QMainWindow(parent, name), m_button(NULL)
{
    m_button = new QPushButton("Send Signal A", this, "Button");
    
    connect(m_button, SIGNAL(clicked()), this, SLOT(OnButtonClicked()));
    connect(this, SIGNAL(SignalA()), this, SLOT(onRecvSignalA()));
}

WindowWithSignalSlot::~WindowWithSignalSlot()
{

}

void WindowWithSignalSlot::OnButtonClicked()
{
    std::cout << "OnButtonClicked" << std::endl;

    emit SignalA();
}

void WindowWithSignalSlot::onRecvSignalA()
{
    std::cout << "onRecvSignalA" << std::endl;
}

//------------------------------------------------------------

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    WindowWithSignalSlot *window = new WindowWithSignalSlot();
    app.setMainWidget(window);

    window->show();

    return app.exec();
}