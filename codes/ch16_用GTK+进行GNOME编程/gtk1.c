// 实验：一个空白的Gtkindow

// 需要安装好这些包：
// gtk2
// gtk2-devel
// gtk2-engines
// libgnome
// libgnomeui
// libgnome-devel
// libgnomeui-devel

// 编译命令：gcc gtk1.c -o gtk1 `pkg-config --cflags --libs gtk+-2.0`

#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *window;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window);
	gtk_main();

	return 0;
}
