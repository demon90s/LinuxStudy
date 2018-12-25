/*
    GtkTreeView

    一种列表视图，也可以是行列表。

    其由三个构件组成：
    GtkTreeView - 树和列表视图
    GtkTreeViewColumn - 代表一个列表或树的列
    GtkCellRenderer - 控制绘图单元
    GtkTreeModel - 代表树和列表数据

    前三个是 view ，最后一个是 model 。这叫 模型/视图/控制器 模式（MVC）。

    创建出一个 view 的顺序是：
    1. 创建一个 model ，比如 GtkTreeStore
    2. 给 model 设置初始数据
    3. 使用 model 创建出 view
    4. 创建 renderer ，使用它给 view 的添加一个新的列（ GtkTreeViewColumn ）
    5. 把 view 添加到一个容器（比如 window ）里
*/

/*
    GtkTreeStore*
    gtk_tree_store_new(gint n_columns, ...);

    创建一个 tree store ，它有 n_columns 列，后面跟着每个类的类型定义( GType )。
*/

/*
    void
    gtk_tree_store_append(GtkTreeStore *tree_store,
                          GtkTreeIter *iter,
                          GtkTreeIter *parent);

    为 tree_store 增加一个新的行，如果 parent 非空，则是给 parent 增加一个子行。
    否则是增加到顶层行。

    新行由 iter 指向，其内容是空的。之后可使用 gtk_tree_store_set 来设置数据。
*/

/*
    void
    gtk_tree_store_set(GtkTreeStore *tree_store,
                       GtkTreeIter *iter,
                       ...);

    为 iter 所绑定的行设置数据。... 是 列-值 对，并必须以 -1 结尾。
    比如，若要设置第0列的一个字符类型的数据，可以：

    gtk_tree_store_set(tree_store, 
                       iter, 
                       0, "Foo", 
                       -1);
*/

/*
    GtkWidget*
    gtk_tree_view_new_with_model(GtkTreeModel *model);

    创建出一个 GtkTreeView 。其初始数据由 model 设定。
*/

/*
    gint
    gtk_tree_view_insert_column_with_attributes
                        (GtkTreeView *tree_view,
                        gint position,
                        const gchar *title,
                        GtkCellRenderer *cell,
                        ...);

    为 tree_view 创建一个新的 GtkTreeViewColumn ，这个新的列位于 postion ，名字叫做 title ，
    使用 cell 作渲染工作。
    Varargs 是一个以 NULL 结尾的属性。
*/

#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    GtkTreeStore* store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
    GtkTreeIter iter1;
    gtk_tree_store_append(store, &iter1, NULL);
    gtk_tree_store_set(store, &iter1, 
                    0, "diwen",
                    1, "1990-9-16",
                    -1);
    GtkTreeIter iter2;
    gtk_tree_store_append(store, &iter2, NULL);
    gtk_tree_store_set(store, &iter2,
                    0, "miemie",
                    1, "2015-9-19",
                    -1);

    GtkWidget *view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                        0,
                                        "name",
                                        renderer,
                                        "text", 0,
                                        NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(view),
                                        1,
                                        "birthday",
                                        renderer,
                                        "text", 1,
                                        NULL);

    gtk_container_add(GTK_CONTAINER(window), view);
    
    gtk_widget_show_all(GTK_WIDGET(window));
    gtk_main();
    return 0;
}