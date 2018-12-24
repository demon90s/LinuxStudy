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

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    
    
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}