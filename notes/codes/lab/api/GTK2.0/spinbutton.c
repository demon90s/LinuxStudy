/*
 * GtkSpinButton
 * 限制用户只能输入数字字符，并设置上下限
 *
 * 它依赖与一种抽象类型 GtkAdjustment
 * GtkObject* gtk_adjustment_new(gdouble value, gdouble lower, gdouble upper, gdouble step_increment, gdouble page_increment, gdouble page_size);
 *
 * value 是初始值， lower 是下限， upper 是上限。
 * step_increment 是每次增加多少值。
 * 对于 GtkSkinButton ，最后俩参数没有意义。
 */

#include <gtk/gtk.h>

static GtkWidget *window;

// GtkWidget* gtk_spin_button_new(GtkAdjustment *adjustment, gdouble climb_rate, guint digits);
// 创建一个 SpinButton ，adjustment 是其初始值和上下限，climb_rate 表明了数值修改的速率，digits 是精度，比如精度3可以表示0.001
void test_gtk_spin_button_new()
{
	GtkObject* adjustment = gtk_adjustment_new(0.0, -1.0, 1.0, 0.01, 0, 0);
	GtkWidget* spin_button = gtk_spin_button_new(GTK_ADJUSTMENT(adjustment), 0.01, 2);
	
	gtk_container_add(GTK_CONTAINER(window), spin_button);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	test_gtk_spin_button_new();

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
