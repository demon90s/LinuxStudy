/*
    GtkToggleButton

    一个拥有状态的按钮，可以派生出 GtkCheckButton, GtkRadioButton
*/

#include <gtk/gtk.h>

static GtkWidget *window;

/*
    gboolean gtk_toggle_button_get_active(GtkToggleButton *toggle_button);
    判断按钮是否激活，如果是激活，就是被按下的样式。
*/
void on_clicked_check_button(GtkWidget *check_button, gpointer toggle_button)
{
    gboolean is_active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON((GtkWidget*)toggle_button));
    printf("is toggle button active? %s\n", is_active ? "yes" : "no");
}
void test_gtk_toggle_button_get_active()
{
    GtkWidget *toggle_button = gtk_toggle_button_new_with_label("ToggleButton");
    GtkWidget *check_button = gtk_button_new_with_label("CheckButton");
    g_signal_connect(GTK_OBJECT(check_button), "clicked", GTK_SIGNAL_FUNC(on_clicked_check_button), toggle_button);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), toggle_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), check_button, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    test_gtk_toggle_button_get_active();
    
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}