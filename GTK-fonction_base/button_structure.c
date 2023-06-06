
#include <gtk/gtk.h>

typedef struct
{
    int x; //abscisse
    int y;//ordonne

}coordonnees;

typedef struct
{
    GtkWidget *button;      // le boutton
    //GtkWidget *racine;    // le conteneur
    gchar* label;     // label du button
    gchar* nom;       // nom du button
    int mnemonic ;
    gchar *url;        // path
    int type_special;         // button special
   coordonnees *pos; //pointeur sur la structure contenant les coordonnées du button

}MonBoutonSimple;


MonBoutonSimple *init_simple_button( gchar*label,gchar *nom,gint mnemonic,int x, int y, int type)
{

    MonBoutonSimple *butt =NULL;
   // allocation dynamique des différentes champs

   butt=(MonBoutonSimple*) malloc(sizeof(MonBoutonSimple));

   butt->pos=(coordonnees*) malloc(sizeof(coordonnees));
 
   butt->label=(gchar*)malloc(256 *sizeof(gchar));

   butt->nom=(gchar*)malloc(256*sizeof(gchar));

  // initialisation des champs et affectation des valeurs

  //label
  if(label) strcpy(butt->label,label);
  else butt->label = NULL;

   //nom
   if(nom) strcpy(butt->nom,nom);
   else butt->nom= NULL;

  //position
  butt->mnemonic=mnemonic;
  butt->pos->x =x;
  butt->pos->y =y;

  butt->type_special=type;

  return((MonBoutonSimple*)butt);

}//fin


GtkWidget* create_simple_button(MonBoutonSimple *btn)
{

   // allocation dynamique du bouton
   if(!btn) 
   	    btn=(MonBoutonSimple*)malloc(sizeof(MonBoutonSimple));

   if(btn->mnemonic && btn->label)

    btn->button=gtk_button_new_with_mnemonic((btn->label));

  if(btn->label)

     btn->button=gtk_button_new_with_label(btn->label);  
  else

     btn->button=gtk_button_new_with_label("");

 if(btn->nom)
    
      gtk_widget_set_name(btn->button,btn->nom);

  //type special
  switch(btn->type_special)
  {
   case 1:

   btn->button = gtk_file_chooser_button_new(btn->label,GTK_FILE_CHOOSER_ACTION_OPEN); break;

  case 2:
   btn->button = gtk_color_button_new();break;

 case 3:
    btn->button = gtk_font_button_new();break;

  default: break;
  }


       return ((GtkWidget*)btn->button);
}



int main(int argc, char* argv[])
{
     GtkWidget *pWindow;
     GtkWidget *pVBox;
     GtkWidget *pButton;
      GtkWidget *pButton2;

    gtk_init(&argc, &argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Le widget GtkEntry");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
   
    pVBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

    MonBoutonSimple * btnsimple;
    MonBoutonSimple * btnsimple2;

    btnsimple = init_simple_button( "Bouton quiter","quiter",1,4,4,0);
    
      pButton = create_simple_button(btnsimple);

    btnsimple2 = init_simple_button( "Bouton ajouter","quiter",1,4,4,2);

      pButton2 = create_simple_button(btnsimple2);

    
    gtk_box_pack_start(GTK_BOX(pVBox), pButton, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pButton2, FALSE, FALSE, 0);
   
    gtk_widget_show_all(pWindow);
    gtk_main();

    return 0;
}



