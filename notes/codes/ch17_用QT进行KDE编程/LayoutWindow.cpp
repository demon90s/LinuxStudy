// 实验：信号和槽

#include <qapplication.h>
#include <qlabel.h>
#include <qlayout.h>

#include "LayoutWindow.moc"

LayoutWindow::LayoutWindow(QWidget *parent, const char* name):
	QMainWindow(parent, name)
{
	this->setCaption("Layouts");

	// 需要创建一个哑 QWidget 来容纳 QHBoxLayout ，这是因为你不能在 QMainWindow 中直接添加 QLayout
	QWidget *widget = new QWidget(this);
	setCentralWidget(widget);

	QHBoxLayout *horizontal = new QHBoxLayout(widget, 5, 10, "horizontal");
	QVBoxLayout *vertical = new QVBoxLayout();

	QLabel *label1 = new QLabel("Top", widget, "textLabel1");
	QLabel *label2 = new QLabel("Bottom", widget, "textLabel2");
	QLabel *label3 = new QLabel("Right", widget, "textLabel3");

	vertical->addWidget(label1);
	vertical->addWidget(label2);
	horizontal->addLayout(vertical);
	horizontal->addWidget(label3);
	resize(150, 100);
}

LayoutWindow::~LayoutWindow()
{
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	LayoutWindow *window = new LayoutWindow();

	app.setMainWidget(window);
	window->show();

	return app.exec();
}
