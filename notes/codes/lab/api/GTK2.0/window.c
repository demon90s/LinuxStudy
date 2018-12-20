#include <gtk/gtk.h>

static GtkWidget *window;

/*
	GtkWidget* gtk_window_new(GtkWindowType type);

	在内存中创建一个类型为 type 的窗口， type 可以是：
	- GTK_WINDOW_TOPLEVEL 标准框架窗口
	- GTK_WINDOW_POPUP 一个适用于对话框的无框架窗口
 */
void test_gtk_window_new(GtkWindowType window_type)
{
	window = gtk_window_new(window_type);
}

/*
	void gtk_window_set_title(GtkWindow *window, const gchar* title);

	设置一个窗口的标题
 */
void test_gtk_window_set_title()
{
	gtk_window_set_title(GTK_WINDOW(window), "First Title");
}

/*
 	void
	gtk_window_set_position(GtkWindow *window, GtkWindowPosition position);

	给窗口设定一个位置
 */
void test_gtk_window_set_position()
{
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
}

/*
 	void
	gtk_window_set_default_size(GtkWindow *window,
		gint width, gint height);

	设置窗口的默认大小。以像素为单位。
*/
void test_gtk_window_set_default_size()
{
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);	// 初始化 GTK+ 库，必须在调用任何 GTK 函数之前调用

	test_gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//test_gtk_window_new(GTK_WINDOW_POPUP);
	
	test_gtk_window_set_title();
	test_gtk_window_set_position();
	test_gtk_window_set_default_size();

	gtk_widget_show(window); // 显示实际窗口
	gtk_main();				// 把控制权交给 GTK+ 来启动交互过程，并且一直运行，直到调用 gtk_main_quit 才返回

	return 0;
}
