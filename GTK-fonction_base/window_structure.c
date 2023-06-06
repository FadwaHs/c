#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

typedef struct
{
    GtkWidget *window;   //la fenetre
    GtkWindowType Type; //type de fenêtre
    gchar *titre;       //titre de la fenetre
    gchar *icon;       //chemin de l'icone de la fenetre
    int Hauteur; 
    int Largeur;
    GtkWindowPosition pos;  //l'emplacement de la fenetre
    gint resizable; // redimensionnement de la fenetre (0 la 1 ah )
    GtkWidget*child; //pointeur sur le fils

}Fenetre;



void Init_default_window_prop(Fenetre *winde)
{

   winde->pos= GTK_WIN_POS_CENTER;//la position du fenêtre est au centre de l'écran.
   winde->child = NULL;
   winde->Largeur=300;
   winde->Hauteur = 300;
   strcpy(winde->titre, "default title");

   //strcpy(winde->icon, "/home/fadwa/Desktop/gtk.png");

   winde->Type = GTK_WINDOW_TOPLEVEL;


}


GtkWidget*Creatwindow(Fenetre wind)
{
	   GtkWidget*  window;
	   window = gtk_window_new(wind.Type);
	   gtk_window_set_position(GTK_WINDOW(window),wind.pos);
	   gtk_window_set_default_size(GTK_WINDOW(window),wind.Hauteur,wind.Largeur);
	   gtk_window_set_title (GTK_WINDOW (window), wind.titre);
       //gtk_window_set_icon_from_file(GTK_WINDOW(window),wind.icon,NULL);

       return((GtkWidget*)window);
}


int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    Fenetre wind;

    Init_default_window_prop(&wind);
    GtkWidget* window = Creatwindow(wind);


    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

