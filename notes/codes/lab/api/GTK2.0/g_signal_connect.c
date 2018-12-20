/*
	gulong g_signal_connect(gpointer *object, const gchar *name, 
		GCallback func, gpointer user_data);

	令一个绑定到 object 的事件 name ，连接到一个回调函数 func 。
	可以给它传递一个参数 user_data

	此回调函数定义为：
	void a_callback_function(GtkWidget *widget, gpointer user_data);
*/

#include <gtk/gtk.h>

static GtkWidget *window;

void button_clicked(GtkWidget *button, gpointer data)
{
	printf("%s\n", (char*)data);
}

void test_g_signal_connect()
{
	GtkWidget *button;

	button = gtk_button_new_with_label("First Button");
	gtk_container_add(GTK_CONTAINER(window), button);
	
	g_signal_connect(GTK_OBJECT(button), "clicked",
			GTK_SIGNAL_FUNC(button_clicked), "Clicked Button");

	gtk_widget_show(button);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	test_g_signal_connect();

	gtk_widget_show(window);
	gtk_main();

	return 0;
}
