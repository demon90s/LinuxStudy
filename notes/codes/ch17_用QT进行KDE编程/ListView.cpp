#include "ListView.moc"
#include <qapplication.h>

ListView::ListView(QWidget *parent, const char *name)
	: QMainWindow(parent, name)
{
	listview = new QListView(this, "listview1");

	listview->addColumn("Artist");
	listview->addColumn("Title");
	listview->addColumn("Catalogue");

	listview->setRootIsDecorated(TRUE);

	QListViewItem *topLevel = new QListViewItem(listview, "Avril Lavigne", "Let GO", "AVCD01");

	new QListViewItem(topLevel, "Complicated");
	new QListViewItem(topLevel, "Sk8er Boi");

	setCentralWidget(listview);
}

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	ListView *window = new ListView();

	app.setMainWidget(window);
	window->show();

	return app.exec();
}
