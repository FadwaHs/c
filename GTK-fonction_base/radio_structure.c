
#include <stdlib.h>
#include <gtk/gtk.h>
 
void OnValider(GtkWidget *pBtn, gpointer data);

typedef struct
{
    int x; //abscisse
    int y;//ordonne

}coordonnees;


typedef struct prRadio
{

   GtkWidget *radioButton; /// l'objet button radio
   GtkWidget *rad2; /// le père du group
   GSList *group; /// group des buttons créer
   gchar *label; /// label du button
  char *nom; ///Le nom du radio (pour le css)
  int mnemonic; ///1 si création avec mnemonic, 0 sinon
  coordonnees *pos; ///position du bouton


} prRadioButton;


prRadioButton *initialise_radio_button (gchar* label,gchar *nom,gint mnemonic,int x,int y)
{

  ///déclaration des variables:
  prRadioButton *bout = NULL;
  //allocation mémoire :
  bout = (prRadioButton*)malloc (sizeof (prRadioButton)); 
  bout->pos=(coordonnees*)malloc(sizeof(coordonnees));
  bout->label = (gchar*)malloc (30*sizeof (gchar));
  bout->nom = (gchar*)malloc (30*sizeof (gchar));

  ///label
  if (label)
    strcpy (bout->label, label);
  else bout->label = NULL;
  ///nom du bouton
  if (nom)
  strcpy (bout->nom, nom);
  else bout->nom = NULL;
  ///button with mnemonic
  bout->mnemonic = mnemonic;
  ///position du button
  bout->pos->x=x;
  bout->pos->y=y;
  
  return ((prRadioButton*)bout);

}


GtkWidget* create_radio_button (prRadioButton *btn2 ,prRadioButton *btn, prRadioButton *btn1)

{ 
 
  GtkWidget *group = NULL;

  if (btn1)

  	 btn1->radioButton = gtk_radio_button_new_with_label(NULL, btn1->label);
     group = btn1->radioButton;


// le fils 1 
if ((btn->mnemonic) && (btn->label))

    btn->radioButton = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (group),(btn->label));

else if((btn->label))

    btn->radioButton =gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (group),btn->label);

else

btn->radioButton = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (group),"prRadioButton");

///nom
if (btn->nom) gtk_widget_set_name(btn->radioButton, btn->nom);


// le fils 2

if ((btn2->mnemonic) && (btn2->label))

    btn2->radioButton = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (group),(btn2->label));

else if((btn2->label))

    btn2->radioButton =gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (group),btn2->label);

else

btn2->radioButton = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (group),"prRadioButton");

///nom
if (btn2->nom) gtk_widget_set_name(btn2->radioButton, btn2->nom);



return ((GtkWidget*) btn1->radioButton);

}



int main(int argc, char **argv)
{
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pRadio1;
    GtkWidget *pRadio2;
    GtkWidget *pValider;
    GtkWidget *pLabel;
    GSList *pList;
  
 
    gtk_init(&argc, &argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "GtkRadioButton");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
 
    pVBox = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow),pVBox);

    pLabel = gtk_label_new("Votre choix :");
    gtk_box_pack_start(GTK_BOX(pVBox), pLabel, FALSE, FALSE, 0);


   /* creation et aafichage des buttons radio with macros */
      prRadioButton *btn;
      prRadioButton *btn1;
      prRadioButton *btn2;

        btn= initialise_radio_button ("Contre","test",0,2,2);

        btn2 = initialise_radio_button ("Sans opinion","test",0,2,2);

        btn1 = initialise_radio_button ("pour","test2",0,2,2);// le pere
 
        pRadio1 = create_radio_button(btn2,btn,btn1);

       
      pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(pRadio1));

    while(pList)
    {
            gtk_box_pack_start(GTK_BOX (pVBox),GTK_WIDGET(pList->data), FALSE, FALSE, 0);
            pList = g_slist_next(pList); 
    }


    pValider = gtk_button_new_with_label("ok");
    gtk_box_pack_start(GTK_BOX (pVBox), pValider, FALSE, FALSE, 0);
 
    g_signal_connect(G_OBJECT(pValider), "clicked", G_CALLBACK(OnValider), pRadio1);
 
    gtk_widget_show_all(pWindow);
    gtk_main();
 
    return EXIT_SUCCESS;
}



void OnValider(GtkWidget *pBtn, gpointer data)
{
    GtkWidget *pInfo;
    GtkWidget *pWindow;
    GSList *pList2;
    const gchar *sLabel;
 
    /* Récupération de la liste des boutons */
    pList2 = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));
 
    /* Parcours de la liste */
    while(pList2)
    {
        /* Le bouton est-il sélectionné */
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList2->data)))
        {
            /* OUI -> on copie le label du bouton */
            sLabel = gtk_button_get_label(GTK_BUTTON(pList2->data));
            /* On met la liste a NULL pour sortir de la boucle */
            pList2 = NULL;
        }
        else
        {
            /* NON -> on passe au bouton suivant */
            pList2 = g_slist_next(pList2);
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




