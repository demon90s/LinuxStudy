/*

*/

#include <gtk/gtk.h>

static GtkWidget *window;

/*
	GtkWidget*
	gtk_button_new_with_label(const gchar *label);

	内存中创建一个 button ，其上的文字是 label

	gchar 是 GTK+ 定义的类型，为了实现跨平台开发，对应的标准类型是 char
 */
void test_gtk_button_new_with_label()
{
	GtkWidget *button;

	button = gtk_button_new_with_label("First Button");
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show(button);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	test_gtk_button_new_with_label();

	gtk_widget_show(window);
	gtk_main();

	return 0;
}
