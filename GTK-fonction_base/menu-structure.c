#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

typedef struct{

char *label;
int sub_items;
char sub_menu[6][15]; //6 :max number of children in menu bar menus
                      //15:max number of chars                       
}MuButton;


MuButton Menulist[] = {
{"File", 6,{"New","open","save","New","open","save"}},
{"Edit", 4, {"cut","copy","paste","delete"}},
{"View", 4,{"fullscreen","larger","smaller","Normal"}},
{"Search",4,{"find","find next","find prev","replace"}},
{"Tools", 1,{"spelling"}},
{"document" ,2,{"close all","save all"}},
{"Help",2,{"contents","about"}}
};


const int mlimit = 7;

void button_click(GtkWidget * button, gpointer data)
{

   g_print("Click");
}

// menu macros
void  make_menu(GtkWidget* vbox)
{
    GtkWidget *menubar =gtk_menu_bar_new();
    int index;
    for(index=0; index < mlimit;index++)
    {
       GtkWidget*item = gtk_menu_item_new_with_label(Menulist[index].label);
       GtkWidget*item_menu =gtk_menu_new();
       gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);
       gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), item_menu);

       int loop;
       int limit=Menulist[index].sub_items;
       for(loop =0 ; loop < limit ; loop++)
       {

          GtkWidget *subitem;
          subitem = gtk_menu_item_new_with_label(Menulist[index].sub_menu[loop]);

          g_signal_connect(GTK_WIDGET(subitem),"activate",
                                                G_CALLBACK(button_click),
                                                Menulist[index].sub_menu[loop]);

          gtk_menu_shell_append(GTK_MENU_SHELL(item_menu), subitem); 

       }

    } 

    gtk_container_add(GTK_CONTAINER(vbox),menubar);     
}


int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget*  window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //window function
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (window), "menu with structur");
    gtk_window_set_default_size (GTK_WINDOW (window), 300, 300);
    
   GtkWidget *vbox= gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
   gtk_container_add(GTK_CONTAINER(window),vbox);
    
    ///creer un menu 
    make_menu(vbox);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}


















