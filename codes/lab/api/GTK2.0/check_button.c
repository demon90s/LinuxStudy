/*
    GtkCheckButton

    一个文本+一个复选框，派生自 GtkToggleButton
*/

#include <gtk/gtk.h>

static GtkWidget *window;

/*
    GtkWidget* gtk_check_button_new_with_label(const gchar *label);
    创建一个 GtkCheckButton
*/
void on_clicked_check_btn(GtkWidget *check_btn, gpointer check_button)
{
    gboolean is_active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON((GtkWidget*)check_button));
    printf("is check button active? %s\n", is_active ? "yes" : "no");
}
void test_gtk_check_button_new_with_label()
{
    GtkWidget *check_button = gtk_check_button_new_with_label("CheckButton");
    GtkWidget *check_btn = gtk_button_new_with_label("Check");
    g_signal_connect(GTK_OBJECT(check_btn), "clicked", GTK_SIGNAL_FUNC(on_clicked_check_btn), check_button);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), check_button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), check_btn, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    test_gtk_check_button_new_with_label();
    
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}