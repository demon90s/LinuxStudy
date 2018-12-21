#include <gtk/gtk.h>

static GtkWidget *window;

/*
 * void gtk_window_resize(GtkWindow *window, gint width, gint height);
 * 设置窗口的大小（像素单位）
 */ 
void on_clicked_resize(GtkWidget *widget, gpointer user_data)
{
	printf("Clicked resize button, window resize to (600, 400)\n");
	gtk_window_resize(GTK_WINDOW(window), 600, 400);
}

/*
 * void gtk_window_set_resizable(GtkWindow *window, gboolean resizable);
 * 设置窗口可否调整大小
 */
void on_clicked_set_resizable(GtkWidget *widget, gpointer user_data)
{
	static gboolean can_resizable = TRUE;
	can_resizable = !can_resizable;
	printf("Clicked set resizable button, window now resizable? %s\n",
		can_resizable ? "yes" : "no");
	
	gtk_window_set_resizable(GTK_WINDOW(window), can_resizable);
}

/*
 * void gtk_window_present(GtkWindow *window);
 * 为了确保窗口在屏幕上并且对用户是可见的，即它没有被最小化或隐藏，你可以使用此函数完成这个功能
 * 它对对话框来说很有用，可以确保你在需要用户输入时它们没有被最小化
 */
void on_clicked_present(GtkWidget *widget, gpointer user_data)
{
	printf("Clicked present, now window is present\n");

	gtk_window_present(GTK_WINDOW(window));
}

/*
 * void gtk_window_maximize(GtkWindow *window);
 * 最大化窗口
 */
void on_clicked_maximize(GtkWidget *widget, gpointer user_data)
{
	printf("Clicked maximize\n");

	gtk_window_maximize(GTK_WINDOW(window));
}

/*
 * void gtk_window_unmaximize(GtkWindow *window);
 * 最小化窗口（书本）
 * PS 只是取消最大化，而不是把窗口收到任务栏
 */
void on_clicked_unmaximize(GtkWidget *widget, gpointer user_data)
{
	printf("Clicked unmaximize\n");

	gtk_window_unmaximize(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);	// 初始化 GTK+ 库，必须在调用任何 GTK 函数之前调用

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// 添加几个 button ，每个 button 点击后操作窗口
	GtkWidget *btn_resize,
			  *btn_set_resizable,
			  *btn_present,
			  *btn_maximize,
			  *btn_unmaximize;

	btn_resize = gtk_button_new_with_label("resize window");
	btn_set_resizable = gtk_button_new_with_label("set window resizable");
	btn_present = gtk_button_new_with_label("present window");
	btn_maximize = gtk_button_new_with_label("maximize window");
	btn_unmaximize = gtk_button_new_with_label("unmaximize window");

	g_signal_connect(GTK_OBJECT(btn_resize), "clicked", GTK_SIGNAL_FUNC(on_clicked_resize), NULL);
	g_signal_connect(GTK_OBJECT(btn_set_resizable), "clicked", GTK_SIGNAL_FUNC(on_clicked_set_resizable), NULL);
	g_signal_connect(GTK_OBJECT(btn_present), "clicked", GTK_SIGNAL_FUNC(on_clicked_present), NULL);
	g_signal_connect(GTK_OBJECT(btn_maximize), "clicked", GTK_SIGNAL_FUNC(on_clicked_maximize), NULL);
	g_signal_connect(GTK_OBJECT(btn_unmaximize), "clicked", GTK_SIGNAL_FUNC(on_clicked_unmaximize), NULL);

	GtkWidget *vbox;
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn_resize, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn_set_resizable, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn_present, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn_maximize, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn_unmaximize, FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	gtk_widget_show_all(window); // 显示实际窗口
	gtk_main();				// 把控制权交给 GTK+ 来启动交互过程，并且一直运行，直到调用 gtk_main_quit 才返回

	return 0;
}
