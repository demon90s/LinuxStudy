// 实验：一个 GNOME 窗口

// 构建命令：gcc gnome1.c -o gnome1 `pkg-config --cflags --libs libgnome-2.0 libgnomeui-2.0`

#include <gnome.h>

int main(int argc, char *argv[])
{
    GtkWidget *app;

    gnome_program_init("gnome1", "1.0", LIBGNOMEUI_MODULE, argc, argv, NULL);
    app = gnome_app_new("gnome1", "The Window Title");

    gtk_widget_show(app);
    gtk_main();

    return 0;
}