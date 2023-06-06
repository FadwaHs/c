

#include <stdlib.h>
#include <gtk/gtk.h>
 
void OnValider(GtkWidget *pBtn, gpointer data);
 
int main(int argc, char **argv)
{
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pRadio1;
    GtkWidget *pRadio2;
    GtkWidget *pRadio3;
    GtkWidget *pValider;
    GtkWidget *pLabel;
 
    gtk_init(&argc, &argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "GtkRadioButton");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
 
    pVBox = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow),pVBox);
 
    pLabel = gtk_label_new("Votre choix :");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, FALSE, FALSE, 0);
 
    /* Création du premier bouton radio */
    pRadio1 = gtk_radio_button_new_with_label(NULL, "Pour");
    gtk_box_pack_start(GTK_BOX (pVBox), pRadio1, FALSE, FALSE, 0);
    /* Ajout du deuxieme */
    pRadio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio1), "Contre");
    gtk_box_pack_start(GTK_BOX (pVBox), pRadio2, FALSE, FALSE, 0);
    /* Ajout du troisième */
    pRadio3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (pRadio1), "Sans opinion");
    gtk_box_pack_start(GTK_BOX (pVBox), pRadio3, FALSE, FALSE, 0);
 
    pValider = gtk_button_new_with_label("ok");
    gtk_box_pack_start(GTK_BOX (pVBox), pValider, FALSE, FALSE, 0);
 
    gtk_widget_show_all(pWindow);
 
    /* Connexion des signaux */
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(pValider), "clicked", G_CALLBACK(OnValider), pRadio1);
 
    gtk_main();
 
    return EXIT_SUCCESS;
}
 
void OnValider(GtkWidget *pBtn, gpointer data)
{
    GtkWidget *pInfo;
    GtkWidget *pWindow;
    GSList *pList;
    const gchar *sLabel;
 
    /* Récupération de la liste des boutons */
    pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));
 
    /* Parcours de la liste */
    while(pList)
    {
        /* Le bouton est-il sélectionné */
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data)))
        {
            /* OUI -> on copie le label du bouton */
            sLabel = gtk_button_get_label(GTK_BUTTON(pList->data));
            /* On met la liste a NULL pour sortir de la boucle */
            pList = NULL;
        }
        else
        {
            /* NON -> on passe au bouton suivant */
            pList = g_slist_next(pList);
        }
    }
 
    /* On récupère la fenêtre principale */
    /*
    /* À partir d'un widget, gtk_widget_get_toplevel
    /* remonte jusqu'à la fenêtre mère qui nous est
    /* utile pour l'affichage de la boite de dialogue
    */
    pWindow = gtk_widget_get_toplevel(GTK_WIDGET(data));
 
    pInfo = gtk_message_dialog_new(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Vous avez choisi : %s",sLabel);
 
    gtk_dialog_run(GTK_DIALOG(pInfo));
 
    gtk_widget_destroy(pInfo);
}