#include <stdlib.h>
#include <gtk/gtk.h>
 
int main(int argc, char **argv)
{
    GtkWidget *pWindow;
    GtkWidget *grid;
    GtkWidget *pButton[4];
 
    gtk_init(&argc, &argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Les GtkTable");
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 
    /* Creation et insertion de la table 3 lignes 2 colonnes */
    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(grid));
 
    /* Creation des boutons */
    pButton[0]= gtk_button_new_with_label("Bouton 1");
    pButton[1]= gtk_button_new_with_label("Bouton 2");
    pButton[2]= gtk_button_new_with_label("Bouton quite");
    
    /* Insertion des boutons */
    
     /* Place the first button in the grid cell (0, 0), and make it fill
        just 1 cell horizontally and vertically (ie no spanning)*/
    gtk_grid_attach (GTK_GRID (grid), pButton[0],0, 0, 1, 1);
    
    
  /* Place the second button in the grid cell (1, 0), and make it fill
     just 1 cell horizontally and vertically (ie no spanning)*/
    gtk_grid_attach(GTK_GRID (grid), pButton[1],1, 0, 1, 1);
    
     gtk_grid_attach (GTK_GRID (grid), pButton[2], 0, 1, 2, 1);
    
 
    gtk_widget_show_all(pWindow);
    gtk_main();
 
    return EXIT_SUCCESS;
}
