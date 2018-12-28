#include "ButtonWindow.moc"
#include <qpushbutton.h>
#include <qapplication.h>
#include <iostream>

// 构造函数中，设置窗口标题，创建按钮，并且把按钮的 clicked 信号连接到槽
ButtonWindow::ButtonWindow(QWidget *parent, const char *name)
	: QMainWindow(parent, name)
{
	this->setCaption("This is the window Title");
	QPushButton *button = new QPushButton("Click Me!", this, "Button1");
	button->setGeometry(50, 30, 70, 20);
	connect(button, SIGNAL(clicked()), this, SLOT(Clicked()));
}

ButtonWindow::~ButtonWindow()
{
}

// 槽实现代码
void ButtonWindow::Clicked(void)
{
	std::cout << "clicked\n";
}

// 在 main 函数中，创建一个 ButtonWindow 的实例
int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	ButtonWindow *window = new ButtonWindow();

	app.setMainWidget(window);
	window->show();

	return app.exec();
}
