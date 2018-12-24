/*
    GtkRadioButton

    可以与同类型的 button 同为一组，它们有一个机械按钮，并且只有一个按钮可以激活。
    派生自 GtkToggleButton 。
*/

#include <gtk/gtk.h>

static GtkWidget *window;

/*
    GtkWidget* gtk_radio_button_new(GSList *group);
*/
void test_gtk_radio_button_new()
{
    GtkWidget *radio_button1 = gtk_radio_button_new(NULL);
    GtkWidget *radio_button2 = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(radio_button1));
    GtkWidget *radio_button3 = gtk_radio_button_new_from_widget(GTK_RADIO_BUTTON(radio_button1));

    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_box_pack_start(GTK_BOX(vbox), radio_button1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), radio_button2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), radio_button3, FALSE, FALSE, 0);
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    test_gtk_radio_button_new();
    
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}