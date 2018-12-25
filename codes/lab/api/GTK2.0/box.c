#include <gtk/gtk.h>

static GtkWidget *window;

/*
	GtkWidget* gtk_hbox_new(gboolean homeogenerous, gint spacing);
	GtkWidget* gtk_vbox_new(gboolean homeogenerous, gint spacing);

	gtk_hbox_new gtk_vbox_new 创建一个盒子，盒子是一个容器，它本身看不见。
	homeogenerous 如果是 TRUE ，则盒子中的每个构件都占据相同的大小空间。
	space 是像素为单位的间距。

	void gtk_box_pack_start(GtkBox *box, GtkWidget *child,
							gboolean expand, gboolean fill,
							guint padding);
	void gtk_box_pack_end(GtkBox *box, GtkWidget *child,
						  gboolean expand, gboolean fill,
						  guint padding);
	操作	盒子	结果
	start	hbox	向右边添加构件
	start	vbox	向底部添加构件
	end		hbox	向左边添加构件
	end		vbox	向顶部添加构件

	expand 如果为 TRUE ，则这个构件将填充与其他该标志也被设为 TRUE 的构件共享的所有可用空间
	fill 如果为 TRUE ，则这个构件将填满分配给它的空间，而不是将它作为围绕它的边缘填充，此参数只有在 expand 为 TRUE 时才有效
	padding 围绕在构件周围的以像素为单位的填充
*/
void test_hbox()
{
	GtkWidget *hbox;
	hbox = gtk_hbox_new(FALSE, 0);

	GtkWidget *button1, *button2, *button3;
	button1 = gtk_button_new_with_label("Button1");
	button2 = gtk_button_new_with_label("Button2");
	button3 = gtk_button_new_with_label("Button3");

	gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), button3, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(window), hbox);
}

void test_vbox()
{
	GtkWidget *vbox;
	vbox = gtk_vbox_new(FALSE, 0);

	GtkWidget *button1, *button2, *button3;
	button1 = gtk_button_new_with_label("Button1");
	button2 = gtk_button_new_with_label("Button2");
	button3 = gtk_button_new_with_label("Button3");

	gtk_box_pack_end(GTK_BOX(vbox), button1, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(vbox), button2, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(vbox), button3, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(window), vbox);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

	//test_hbox();
	test_vbox();

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
