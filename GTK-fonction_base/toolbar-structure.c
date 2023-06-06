
#include <gtk/gtk.h>


typedef struct toolbarre
{

GtkWidget *toolbar ; // barre d’outil
GtkToolItem *toolitem; // les buttons de la barre
gchar* icon; // l’icon d’apres le stock
gpointer *signal; // signal du button

}tool;

GtkWidget * creat_toolbar(tool* p){

//création d'un toolbar
p->toolbar=gtk_toolbar_new();

//définir le style d'un toolbar avec des icons
gtk_toolbar_set_style(GTK_TOOLBAR(p->toolbar), GTK_TOOLBAR_ICONS);

 return((GtkWidget * )p->toolbar);


}


GtkWidget * creat_toolitem(tool* p,gchar* icone){

//création d'un toolitem avec une icone du stock
p->toolitem= gtk_tool_button_new_from_stock(icone);

//inseret le toolitem dans le toolbar
gtk_toolbar_insert(GTK_TOOLBAR(p->toolbar), p->toolitem, -1);

 return((GtkWidget * )p->toolbar);

}

void connectre_item_sig( GtkToolItem* p,gchar* signal){

g_signal_connect(G_OBJECT(p), signal,G_CALLBACK(gtk_main_quit),NULL);

}


int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget * toolbr;
  

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
  gtk_window_set_title(GTK_WINDOW(window), "toolbar");

   vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
   gtk_container_add(GTK_CONTAINER(window), vbox); 


  /* test de macro */
  tool * toolbar;

  toolbr = creat_toolbar(toolbar);
  toolbr =creat_toolitem(toolbar,GTK_STOCK_SAVE);
  toolbr =creat_toolitem(toolbar,GTK_STOCK_NEW);
  toolbr =creat_toolitem(toolbar,GTK_STOCK_OPEN);
  toolbr =creat_toolitem(toolbar,GTK_STOCK_QUIT);

  connectre_item_sig( toolbar->toolitem,"clicked");
  

  gtk_box_pack_start(GTK_BOX(vbox), toolbr, FALSE, FALSE, 5);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

