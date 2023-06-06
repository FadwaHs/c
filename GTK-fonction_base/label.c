#include <stdlib.h>
#include <gtk/gtk.h>
 
int main(int argc,char **argv)
{
    GtkWidget* pWindow;
    GtkWidget* pLabel;
    gchar* sUtf8;
 
    gtk_init(&argc,&argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow),"Les labels III");
    gtk_window_set_default_size(GTK_WINDOW(pWindow),320,200);
 
    /* Creation du label avec g_locale_to_utf8 */
    pLabel=gtk_label_new(NULL);
 
    /* On utilise les balises */
    sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><b>Courier New 10 Gras</b></span>\n"
        "<span font_desc=\"Times New Roman italic 12\" foreground=\"#0000FF\">Times New Roman 12 Italique</span>\n",-1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
    g_free(sUtf8);
 
    /* On centre le texte */
    gtk_label_set_justify(GTK_LABEL(pLabel), GTK_JUSTIFY_CENTER);
 
     /* On ajoute le label à l'intérieur de la fenêtre */
     gtk_container_add(GTK_CONTAINER(pWindow),pLabel);
 
     /* Affichage de la fenêtre et de tout ce qu'il contient */
    gtk_widget_show_all(pWindow);
 
 
     gtk_main();
 
    return EXIT_SUCCESS;
}
