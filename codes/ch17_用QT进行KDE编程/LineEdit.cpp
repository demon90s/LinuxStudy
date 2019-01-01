#include "LineEdit.moc"
#include <qpushbutton.h>
#include <qapplication.h>
#include <qlabel.h>
#include <qlayout.h>
#include <iostream>

LineEdit::LineEdit(QWidget *parent, const char *name) : QMainWindow(parent, name)
{
	QWidget *widget = new QWidget(this);
	setCentralWidget(widget);

	// 用 QGridLayout 排列构件。指定行数、列数、边距和间隔
	QGridLayout *grid = new QGridLayout(widget, 3,2,10, 10, "grid");

	QLineEdit *username_entry = new QLineEdit(widget, "username_entry");
	password_entry = new QLineEdit(widget, "password_entry");
	password_entry->setEchoMode(QLineEdit::Password);

	grid->addWidget(new QLabel("Username", widget, "userlabel"), 0, 0, 0);
	grid->addWidget(new QLabel("Password", widget, "passwordlabel"), 1, 0, 0);

	grid->addWidget(username_entry, 0, 1, 0);
	grid->addWidget(password_entry, 1, 1, 0);

	QPushButton *button = new QPushButton("OK", widget, "button");
	grid->addWidget(button, 2, 1, Qt::AlignRight);

	resize(350, 200);

	connect(button, SIGNAL(clicked()), this, SLOT(Clicked()));
}

LineEdit::~LineEdit() {}

void LineEdit::Clicked(void)
{
	std::cout << password_entry->text() << "\n";
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	LineEdit *window = new LineEdit();

	app.setMainWidget(window);
	window->show();

	return app.exec();
}
