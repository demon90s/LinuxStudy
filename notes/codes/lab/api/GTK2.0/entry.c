/*
    GtkEntry 相关的方法

    GtkEntry 是一个单行文本输入框。
*/

#include <gtk/gtk.h>

static GtkWidget *window;

// GtiWidget* gtk_entry_new();
// 创建一个单行文本输入框
void test_gtk_entry_new()
{
    GtkWidget *entry = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(window), entry);
}

// GtiWidget* gtk_entry_new_with_max_length(gint max);
// 创建一个有最大的输入长度的文本框
void test_gtk_entry_new_with_max_length()
{
    GtkWidget *entry = gtk_entry_new_with_max_length(6);
    gtk_container_add(GTK_CONTAINER(window), entry);
}

// void gtk_entry_set_max_length(GtkEntry *entry, gint max);
// 设置最大输入长度
void on_click_change_max_length_button(GtkWidget *button, gpointer entry)
{
    printf("change entry max length to 6\n");
    gtk_entry_set_max_length(GTK_ENTRY((GtkWidget*)entry), 6);
}
void test_gtk_entry_set_max_length()
{
    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("Change max length to 6");
    g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(on_click_change_max_length_button), entry);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
}

// G_CONST_RETURN gtk_entry_get_text(GtkEntry *entry);
// 获取输入的内容
void on_gtk_entry_get_text(GtkWidget *button, gpointer entry)
{
    printf("your entered: %s\n", gtk_entry_get_text(GTK_ENTRY((GtkWidget*)entry)));
}
void test_gtk_entry_get_text()
{
    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("button");
    g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(on_gtk_entry_get_text), entry);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
}

// void gtk_entry_set_text(GtkEntry *entry, const gchar *text);
// 设置输入内容
void test_gtk_entry_set_text()
{
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), "Hi entry");
    gtk_container_add(GTK_CONTAINER(window), entry);
}

// void gtk_entry_append_text(GtkEntry *entry, const gchar *text);
// void gtk_entry_prepend_text(GtkEntry *entry, const gchar *text);
// 后置或前置内容
void on_button_append(GtkWidget *button, gpointer entry)
{
    printf("on button append, append a character x\n");
    gtk_entry_append_text(GTK_ENTRY((GtkWidget*)entry), "x");
}
void on_button_prepend(GtkWidget *button, gpointer entry)
{
    printf("on button prepend, prepend a character o\n");
    gtk_entry_prepend_text(GTK_ENTRY((GtkWidget*)entry), "o");
}
void test_gtk_entry_append_text_gtk_entry_preend_text()
{
    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    GtkWidget *button_append = gtk_button_new_with_label("button_append");
    GtkWidget *button_prepend = gtk_button_new_with_label("button_prepend");
    g_signal_connect(GTK_OBJECT(button_append), "clicked", GTK_SIGNAL_FUNC(on_button_append), entry);
    g_signal_connect(GTK_OBJECT(button_prepend), "clicked", GTK_SIGNAL_FUNC(on_button_prepend), entry);
    gtk_box_pack_start(GTK_BOX(vbox), button_append, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_prepend, FALSE, FALSE, 0);
}

// void gtk_entry_set_visibility(GtkEntry *entry, gboolean visible);
// 设置内容是否可见
void on_button_set_visibility(GtkWidget *button, gpointer entry)
{
    static gboolean visible = TRUE;
    visible = !visible;
    printf("now is visible? %s\n", visible ? "yes" : "no");

    gtk_entry_set_visibility(GTK_ENTRY((GtkWidget*)entry), visible);
}
void test_gtk_entry_set_visibility()
{
    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("toggle visible");
    g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(on_button_set_visibility), entry);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
}

// void gtk_entry_set_invisible_char(GtkEntry *entry, gchar invch);
// 设置不可见内容显示的字符
void test_gtk_entry_set_invisible_char()
{
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(entry), '?');
    gtk_container_add(GTK_CONTAINER(window), entry);
}

// void gtk_entry_set_editable(GtkEntry *entry, gboolean editable);
// 设置内容是否可以编辑
void on_button_set_editable(GtkWidget *button, gpointer entry)
{
    static gboolean editable = TRUE;
    editable = !editable;
    printf("now is editable? %s\n", editable ? "yes" : "no");

    gtk_entry_set_editable(GTK_ENTRY((GtkWidget*)entry), editable);
}
void test_gtk_entry_set_editable()
{
    GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    GtkWidget *button = gtk_button_new_with_label("toggle editable");
    g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(on_button_set_editable), entry);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    //test_gtk_entry_new();
    //test_gtk_entry_new_with_max_length();
    //test_gtk_entry_set_max_length();
    //test_gtk_entry_get_text();
    //test_gtk_entry_set_text();
    //test_gtk_entry_append_text_gtk_entry_preend_text();
    //test_gtk_entry_set_visibility();
    //test_gtk_entry_set_invisible_char();
    test_gtk_entry_set_editable();
    
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}