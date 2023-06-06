#include <stdlib.h>
#include <gtk/gtk.h>
 
int main(int argc, char **argv)
{
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pFrame;
    GtkWidget *pVBoxFrame;
    GtkWidget *pSeparator;
    GtkWidget *pEntry;
    GtkWidget *pLabel;
    gchar *sUtf8;
 
    gtk_init(&argc, &argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    /* On ajoute un espace de 5 sur les bords de la fenêtre */
    gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Gtkframe");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
   
 
    pVBox =  gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 
    /* Creation du premier GtkFrame */
    pFrame = gtk_frame_new("Etat civil");
    gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, FALSE, 0);
 
    /* Creation et insertion d une boite pour le premier GtkFrame */
    pVBoxFrame =gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame);
 
    /* Creation et insertion des éléments contenus dans le premier GtkFrame */
    pLabel = gtk_label_new("Nom :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    sUtf8 = g_locale_to_utf8("Prénom :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("Date de naissance :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    /* Creation du deuxieme GtkFrame */
    pFrame = gtk_frame_new("Domicile");
    gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, FALSE, 0);
 
    /* Creation et insertion d une boite pour le deuxieme GtkFrame */
    pVBoxFrame =  gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame);
 
    /* Creation et insertion des éléments contenus dans le deuxieme GtkFrame */
    pLabel = gtk_label_new("Adresse :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("Adresse :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("Code postal :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("Ville :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    /* Creation du troisieme GtkFrame */
    sUtf8 = g_locale_to_utf8("Téléphones", -1, NULL, NULL, NULL);
    pFrame = gtk_frame_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, FALSE, 0);
 
    /* Creation et insertion d une boite pour le troisieme GtkFrame */
    pVBoxFrame =  gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame);
 
    /* Creation et insertion des éléments contenus dans le troisieme GtkFrame */
    pLabel = gtk_label_new("Domicile");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("Professionnel");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("Portable");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    gtk_widget_show_all(pWindow);
 
    gtk_main();
 
    return EXIT_SUCCESS;
}
