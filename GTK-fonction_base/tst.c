#include <gtk/gtk.h>
#include <string.h>
#include<stdlib.h>
#define maxTitre 30 //taille max d'un titre
#define maxPath 100 // taille max d'un chemin


/*
 * structure de dimention d'un widget
 */
typedef struct
{
    gint height; //longueur
    gint width; //largeur
}dimension;
/*
 * structure des coordonnees
 */
typedef struct
{
    gint x; //abscisse
    gint y;//ordonne
}coordonnees;
/*
 * structure de positionnement
 * soit avoir des coordonnees soit une position
 */
typedef union
{
    coordonnees cord;//les coordonnees
    gchar pos;       //position
}POS;

/*
 * structure du couleur
 */
typedef struct
{
 gchar*color;
 gfloat opacity;

}color_widg;

/*
 * structure d'un fenetre
 */
typedef struct
{
    GtkWidget *window;   //la fenetre
    gchar *titre;       //titre de la fenetre
    gchar *icon;       //chemin de l'icone de la fenetre
    dimension  dim;   //dimention de la fenetre
    POS place;       //l'emplacement de la fenetre
    gint resizable; // redimensionnement de la fenetre (0 la 1 ah )
    color_widg *color; //couleur de fenetre
    gint bordure_taille; // la taille de la bordure
}Fenetre;
/*
 * structure d'un widget fils
 */
typedef struct
{
    GtkWidget *elem;       //l'element lui meme
    gchar *titre;         //titre du widget
    GtkWidget *conteneur;//le pere conteneur du widget
}widg;



/******************************************************************/
 /// test d'allocation
void test_allocation(void *pointeur, char*nom)
{
    if(!pointeur) {
        printf("erreur d'allocation du %s\n", nom);
        exit(-1);
    }
}




/**********************************fonction du couleur***********************************/

void add_bgcolor(GtkWidget*widget,gchar*couleur,gfloat opc)

{

    if(couleur==NULL) return;

    GdkRGBA color;
    gdk_rgba_parse(&color,couleur);
    color.alpha=opc;
    gtk_widget_override_background_color(widget,GTK_STATE_FLAG_NORMAL,&color);
}
///-----------------------------------WINDOW-----------------------------------------------------------------------


/*************************************************************
  La fonction : init_window
  -Entrees :  titre de la fenêtre
      hauteur de notre fenêtre
      largeur de notre fenêtre
      position par defaults de la fenêtre :
        A = GTK_WIN_POS_NONE
        B = GTK_WIN_POS_CENTER
        C = GTK_WIN_POS_MOUSE
        D = GTK_WIN_POS_CENTER_ALWAYS
        E = GTK_WIN_POS_CENTER_ON_PARENT
                Ou bien
        position dans l'axe des x
        position dans l'axe des y
      Possibilité de changer la taille:
        0=NON
        1=OUI
      chemin de l'icon de la fenetre
  -Sortie: La structure WindowObjet apres initialisation
  -Description: Cette fonction permet d'allouer de l'espace memoire pour notre variable de type
                   Fenetre et de l'initaliser
*************************************************************/
Fenetre* init_window(gchar* titre,POS P,dimension D, gint res, gchar*path,color_widg *couleur,gint border)
{
    Fenetre* Window = NULL;
    //Allocation memoire
    Window = (Fenetre*)malloc(sizeof(Fenetre));
    // Test d'allocation
    test_allocation(Window, "fenetre");

    if(titre)
    {  //Allocation de la memoire pour le titre
        Window->titre = (gchar *) malloc(maxTitre*sizeof(gchar));

        test_allocation(Window->titre, "titre fenetre");
        strcpy(Window->titre, titre);//donner le titre a notre fenetre
    }
    if(path)
    {//Allocation de la memoire pour le chemin de l'icon
        Window->icon = (gchar *) malloc(maxPath*sizeof(gchar));
        test_allocation(Window->icon, "Icon fenetre");
        strcpy(Window->icon, path);//donner le titre a notre fenetre
    }
    else Window->icon=NULL;
    Window->dim.height = D.height; // initialisation de la hauteur
    Window->dim.width = D.width; // initialisation de la largeur
    Window->resizable = res; //initialisation du resizable
    Window->place=P;
    Window->color=(color_widg*)malloc(sizeof(color_widg));
    test_allocation(Window->color,"allocation_couleur");
    if(couleur){
        Window->color=couleur;
        }
        else{
            (Window->color)=NULL;
        }

    Window->bordure_taille=border;
    return (Fenetre*)Window; //Retourner la structure
}//fin

//positionnement de la fenetre
/*************************************************************
 La fonction : pos_Window
 Entree :Un pointeur vers la structure Fenetre
           initialisée
 Sortie :  Un pointeur vers la variable W (Fenetre)
 Description : Cette fonction permet d'affecter un type de
    positionement de la fenetre
*************************************************************/
Fenetre *pos_Window(Fenetre*W)
{
    switch(W->place.pos)
    {
        case 'A' : gtk_window_set_position(GTK_WINDOW(W->window),GTK_WIN_POS_NONE);
            break ;
            // Au centre de l'ecran
        case 'B' : gtk_window_set_position(GTK_WINDOW(W->window),GTK_WIN_POS_CENTER);
            break;
            // La position du curseur
        case 'C' : gtk_window_set_position(GTK_WINDOW(W->window),GTK_WIN_POS_MOUSE);
            break;
            // Toujours au centre
        case 'D' : gtk_window_set_position(GTK_WINDOW(W->window),GTK_WIN_POS_CENTER_ALWAYS);
            break;
            // Au centre par rapport a l'élement parent
        case 'E' : gtk_window_set_position(GTK_WINDOW(W->window),GTK_WIN_POS_CENTER_ON_PARENT);
            break;
    }
    return (Fenetre*)W;
}//fin

/*************************************************************
 La fonction : creer_Window
 Entree :Un pointeur vers la structure Fenetre
           initialisée
 Sortie :  Un pointeur vers la variable W (Fenetre)
 Description : Cette fonction permet de créer une fenêtre en
Fct des paramètres récupérés de la structure
                 Fenetre
*************************************************************/
Fenetre* creer_Window(Fenetre *W)
{

    GdkPixbuf *pixbuf;//pointeur sur le peffeur
    //Creation de la fenetre
    W->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if(W->titre)//affectation du titre
        gtk_window_set_title(GTK_WINDOW(W->window),W->titre);
    if((W->dim.height) && (W->dim.width))//affectation de la dimension
        gtk_widget_set_size_request(W->window,(W->dim.width),(W->dim.height));
    //si le positionement est spesifier
    if((W->place.pos>='A')&&(W->place.pos<='E'))
        W=pos_Window(W);
        //sinon affecter les coordonnees de positionment
    else gtk_window_move(GTK_WINDOW(W->window),W->place.cord.x,W->place.cord.y);
    //Si res = 1, redimensionnement = VRAI
    if(W->resizable)
        gtk_window_set_resizable(GTK_WINDOW(W->window),TRUE);
    else
        gtk_window_set_resizable(GTK_WINDOW(W->window),FALSE);
    //ajouter l'icon de la fenetre apartire du beffeur
    if(W->icon) {
        pixbuf = gdk_pixbuf_new_from_file(W->icon, NULL);
        gtk_window_set_icon(GTK_WINDOW(W->window), pixbuf);
    }

    if((W->color))
   add_bgcolor(W->window,W->color->color,W->color->opacity);

   gtk_container_set_border_width(W->window,W->bordure_taille);

    return (Fenetre*)W;
}//fin



///----------------------------------- BOX -----------------------------------------------------------------------
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************

/*
 * structure du widget GTK_BOX
 * Expend: n'est utile que si la GtkBox en question n'est pas définie comme homogène (homogeneous=FALSE lors de la création).
 * Dans ce cas, tous les widgets qui auront été insérés avec la valeur expand=TRUE se partageront tout l'espace libre de la GtkBox
 * (les widgets avec expand=FALSE n'utiliseront que l'espace qui leur est nécessaire).
 */
typedef struct
{
    widg box;        // le box
    gchar type;    // type horizontal ou vertical
    gint homogene; // l'homogénéité des fils du box ( true or false)
    gint spacing; // nombre de pixles entre les fils du box
    gint bordure_taille; //taille de bordure dans le box
    color_widg *color; //couleur du box
    dimension D;

}MonBox;

/*************************************************************
  La fonction : Init_box
  -Entrees :  pere du box ou conteneur
      titre du box
      type du box :
        V = GTK_ORIENTATION_VERTICAL
        H = GTK_ORIENTATION_HORIZONTAL
      homogeniete:
        0=NON
        1=OUI
      l'espace entre les elements du box
  -Sortie: La structure MonBox apres initialisation
  -Description: Cette fonction permet d'allouer de l'espace memoire pour notre variable de type
                   MonBox et de l'initaliser
*************************************************************/
MonBox*Init_box(GtkWidget*pere,gchar*titre,gchar type,gint homo,dimension dim,
                gint spacing,gint border,color_widg *couleur)
{
    MonBox*B=NULL;//declaration du pointeur de type MonBox
    //allocation de la memoire de B
    B=(MonBox*) malloc(sizeof (MonBox));
    //verifier l'allocation
    test_allocation(B,"box");
    if(titre)//titre no vide
    {//allocation de la memoire du titre du box
        B->box.titre = (gchar *) malloc(100*sizeof(titre));
        //verifier l'allocation
        test_allocation(B->box.titre,"titre Box");
        strcpy(B->box.titre, titre);//affecter le titre
    }
    else B->box.titre=NULL;
    B->type=type;//affecter le type
    if(pere) {B->box.conteneur=pere;}//affecter le conteneur
    else B->box.conteneur=NULL;
    B->spacing=spacing;//affecter l'espacement
    B->homogene=homo;//affecter l'omogeite
    B->bordure_taille=border;
    B->color=(color_widg*)malloc(sizeof(color_widg));
    test_allocation(B->color,"allocation_couleur");
    if(couleur){
        B->color=couleur;
        }
        else{
            (B->color)=NULL;
        }
        B->D=dim;

    return ((MonBox*)B);

}//fin

//creer box
/*************************************************************
 La fonction : creer_Box
 Entree :Un pointeur vers la structure MonBox
           initialisée
 Sortie :  Un pointeur vers la variable B (MonBox)
 Description : Cette fonction permet de créer une Box en
Fonction des paramètres récupérés de la structure MonBox
*************************************************************/
MonBox*creer_Box(MonBox*B)
{
    //si le box est vertical
    if(B->type=='v'|| B->type=='V')
        B->box.elem= gtk_box_new(GTK_ORIENTATION_VERTICAL,B->spacing);
    //sinon si c'est horizontal
    else if(B->type=='h'|| B->type=='H')
        B->box.elem= gtk_box_new(GTK_ORIENTATION_HORIZONTAL,B->spacing);
    //sinon c'est une erreur
    else{printf("error type box");exit(-1);}
    //affecter l'omogeniete
    gtk_box_set_homogeneous(GTK_BOX(B->box.elem),B->homogene);
    //affecter le titre
    gtk_widget_set_name(B->box.elem,B->box.titre);
    if(B->box.conteneur)
    gtk_container_add(GTK_CONTAINER(B->box.conteneur),B->box.elem);
    gtk_container_set_border_width(B->box.elem,B->bordure_taille);
    if(B->color)
    add_bgcolor(B->box.elem,B->color->color,B->color->opacity);
    gtk_widget_set_size_request(B->box.elem,B->D.width,B->D.height);
    return ((MonBox*)B);
}//fin

//ajouter debut
/*************************************************************
 La fonction : ajouter_Box
 Entree :Un pointeur vers la structure MonBox
           initialisée et cree
         un pointeur sur un element (fils) qui sera
           inserer dans le box
         un boolean (fill)   : (1) le fils peut remplir son espace complet, 0 non
         un boolean  (expend): (1) le fils peut s'etendre dans le box, 0 non
         un entiere (padding): qui rerpesente le rembourrage du fils
         un entiere (posF): (1) on ajoute le fils au debut du box, sinon a la fin
 Sortie :  Un pointeur vers la variable B (MonBox)
 Description : Cette fonction permet d'ajouter une widget dans un box

*************************************************************/
MonBox *ajouter_Box(MonBox*B,GtkWidget*fils,gboolean fill,gboolean expend,int padding,int posF)
{
    if(posF==1)//ajouter l'element au debut du box
        gtk_box_pack_start(GTK_BOX(B->box.elem),fils,expend,fill,padding);
    //ajouter l'element a la fin du box
    else gtk_box_pack_end(GTK_BOX(B->box.elem),fils,expend,fill,padding);
    return ((MonBox*)B);

}//fin


///-------------------------------------BUTTON-----------------------------------------------------------------------------------
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************
/*
 * structure d'un boutton
 */
typedef struct
{
    widg button;        // le boutton
    GtkWidget * pere;  // pour les bouttons radios
    gchar *url_im;     // path pour image
    gchar *url_ic ;     // path pour icon
    gint type;       // spin/radio/check/nomale

    dimension dim; //dimension du bouton
    gint mnemo;//la creation du button(mnemonic/label)
    color_widg *color; //couleur de button
}MonBouton;

/**********************************************************
La fonction : init_button
-Entrees : mere : la mere du button
          url: chemin de l'icone du boutton
          C les coordonnes du bouton
          D la dimention du bouton
          tit:le titre du button
          conte:le coteneur du bouton
          type:le type du bouton (normal,radio,
                                  check...)
                mnemo:(cration du bouton
                       soit avec label ou birn
                       avec mnemoniac)
-Sortie : B : Objet bouton
-Description: Cette fonction permet d'allouer de l'espace pour
 la structure de type ButtonObject, d'initialiser
 ses champs et de la retourner .
***********************************************************/

MonBouton *init_Button(GtkWidget *mere, gchar *url1,gchar *url2,
                       dimension D,gchar*tit, GtkWidget*conte,gint type,
                        gint mnemo,color_widg *couleur)
{
    MonBouton*B;
    //allocation de la memoire pour le bouton
    B=(MonBouton*)malloc(sizeof(MonBouton));
    test_allocation(B,"bouton");
    if(tit){
        B->button.titre= (gchar*)malloc(30*sizeof(gchar));
        test_allocation( B->button.titre,"titre");
        strcpy( B->button.titre,tit);
    }


    //allocation de la memoire pour l'url 1
        B->url_im=(gchar*)malloc(100*sizeof(gchar));
        test_allocation(B->url_im,"url bouton");
        //initialisation de l url 1
        if(url1)
        strcpy(B->url_im,url1);
        else B->url_im=NULL;

        //allocation de la memoire pour l'url 2
        B->url_ic=(gchar*)malloc(100*sizeof(gchar));
        test_allocation(B->url_ic,"url bouton");
        //initialisation de l url
        if(url2)
        strcpy(B->url_ic,url2);
        else B->url_ic=NULL;

if(conte)
    B->button.conteneur=conte;
    else B->button.conteneur=NULL;

    B->dim=D;//initialisation du dimention
    B->pere=mere;//initialisation du widget pere
    B->type=type;//initialisation du type de bouton
    B->mnemo=mnemo;
   B->color=(color_widg*)malloc(sizeof(color_widg));
    test_allocation(B->color,"allocation_couleur");
    if(couleur){
        B->color=couleur;
        }
        else{
            (B->color)=NULL;
        }

    // return le bouton
    return ((MonBouton*)B);

}

/**********************************************************
La fonction : creer_normal_button
-Entrees : B : objet bouton initialise
-Sortie : B : Objet bouton cree
-Description:Cette fonction permet la creation d'un boutton
normal en fct des parametres recuperes de la structure
 ButtonObject initialisee.
***********************************************************/
MonBouton *creer_normal_Bouton(MonBouton *B)

{

    if(B->button.titre)
    {
        switch(B->mnemo)
        {   // creation du bouton with label
            case 0: B->button.elem=gtk_button_new_with_label(B->button.titre);
                break;
                // creation du bouton with mnemonic
            case 1: B->button.elem=gtk_button_new_with_mnemonic(B->button.titre);
                break;
        }
        // donner un nom au bouton
        gtk_widget_set_name(B->button.elem,B->button.titre);
    }
// creation du bouton sans titre
    else B->button.elem = gtk_button_new();
    gtk_widget_set_size_request(B->button.elem,B->dim.width,B->dim.height);

//retourner le bouton
    return ((MonBouton*)B);
}

/**********************************************************
La fonction : creer_radio_button
-Entrees : B : objet bouton initialise
-Sortie : B : Objet bouton cree
-Description:Cette fonction permet la creation d'un boutton
radio en fct des parametres recuperes de la structure
 ButtonObject initialisee.
***********************************************************/
MonBouton *creer_radio_Bouton(MonBouton *B)
{
    if(B->button.titre)//boutton avec titre
    {
        switch(B->mnemo)//bouton avec mnemonic
        {
            case 0:// creation du bouton with label
                if(B->pere)//si le bouton a un pere
                {//affecter le bouton au group du bouton pere
                    B->button.elem=gtk_radio_button_new_with_label(
                     gtk_radio_button_get_group(GTK_RADIO_BUTTON(B->pere)),B->button.titre);
                }
                else//sinon
                    B->button.elem=gtk_radio_button_new_with_label(NULL,B->button.titre);
                break;
            case 1:// creation du bouton avec mnemonic
                if(B->pere)//si le bouton a un pere
                    B->button.elem=gtk_radio_button_new_with_mnemonic(
                            gtk_radio_button_get_group(GTK_RADIO_BUTTON(B->pere)),B->button.titre);
                    //sinon
                else B->button.elem=gtk_radio_button_new_with_mnemonic(NULL,B->button.titre);
                break;
        }//fin switch
        // donner un nom au bouton
        gtk_widget_set_name(B->button.elem,B->button.titre);
    }
        //creation du bouton sans titre
    else B->button.elem = gtk_button_new();
    gtk_widget_set_size_request(B->button.elem,B->dim.width,B->dim.height);
    return ((MonBouton*)B);
}

/**********************************************************
La fonction : creer_check_button
-Entrees : B : objet bouton initialise
-Sortie : B : Objet bouton cree
-Description:Cette fonction permet la creation d'un boutton
check en fct des parametres recuperes de la structure
 ButtonObject initialisee.
***********************************************************/
MonBouton *creer_check_Bouton(MonBouton *B)
{
    if(B->button.titre)
    {
        switch(B->mnemo)
        {
            case 0:// creation du bouton with label
                B->button.elem=gtk_check_button_new_with_label(B->button.titre);break;
            case 1:// creation du bouton with mnemonic
                B->button.elem=gtk_check_button_new_with_mnemonic(B->button.titre);break;
        }//fin switch
        //donner un nom au bouton
        gtk_widget_set_name(B->button.elem,B->button.titre);
    }//fin if
        // creation du bouton sans titre
    else B->button.elem = gtk_button_new();
    gtk_widget_set_size_request(B->button.elem,B->dim.width,B->dim.height);
    return ((MonBouton*)B);
}

/**********************************************************
La fonction : creer_toggle_button
-Entrees : B : objet bouton initialise
-Sortie : B : Objet bouton cree
-Description:Cette fonction permet la creation d'un boutton
toggle en fct des parametres recuperes de la structure
 ButtonObject initialisee.
***********************************************************/

MonBouton *creer_toggle_Bouton(MonBouton *B)
{
    if(B->button.titre)
    {
        switch(B->mnemo)
        {
            case 0:// creation du bouton with label
                B->button.elem=gtk_toggle_button_new_with_label(B->button.titre);break;
            case 1:// creation du bouton with mnemonic
                B->button.elem=gtk_toggle_button_new_with_mnemonic(B->button.titre);break;
        }//fin switch
        gtk_widget_set_name(B->button.elem,B->button.titre);
    }
        //creation du bouton sans titre
    else B->button.elem = gtk_button_new();
    gtk_widget_set_size_request(B->button.elem,B->dim.width,B->dim.height);
    return ((MonBouton*)B);
}

/**********************************************************
La fonction : creer_button
-Entrees : B : objet bouton initialise
-Sortie : B : Objet bouton cree
-Description:Cette fonction permet la creation d'un boutton
 en fct des parametres recuperes de la structure
 ButtonObject initialisee.
***********************************************************/


MonBouton *creer_Bouton(MonBouton *B)
{
    GdkPixbuf *pixbuf;
    switch(B->type)
    {
        case 1: B=creer_normal_Bouton(B) ;  break;    /* normal button */
        case 2: B=creer_radio_Bouton(B);break;         /* radio button */
        case 3: B= creer_check_Bouton(B); break;    /* check button*/
        case 4: B= creer_toggle_Bouton(B); break;    /* toggle button*/
    }
    /// ajout de couleur
    if(B->color)
    add_bgcolor(B->button.elem,B->color->color,B->color->opacity);

  if(B->button.conteneur)  gtk_container_add(B->button.conteneur,B->button.elem);

    if(B->url_ic)
        ajouter_icon_button(B->url_ic,B);

     if(B->url_im)
        ajouter_image_button(B->url_im,B);

    return ((MonBouton*)B);
}


/*******  Ajouter image to button *******/
void ajouter_image_button(gchar* url,MonBouton *B)
{
if(!url) return;

    GtkWidget* image_button;
    image_button=gtk_image_new_from_file(url);
    gtk_button_set_image(GTK_BUTTON(B->button.elem),image_button);
    gtk_button_set_always_show_image(GTK_BUTTON(B->button.elem),TRUE);

}


 /*******  Ajouter icon to button *******/
void ajouter_icon_button(gchar* url,MonBouton *B)
{
    if(!url) return;
    GtkWidget *image_button;
 GdkPixbuf* pixt=gdk_pixbuf_new_from_file_at_size(B->url_ic,50,50,NULL);
        image_button=gtk_image_new_from_pixbuf(pixt);
 gtk_button_set_image(GTK_BUTTON(B->button.elem),image_button);

 gtk_button_set_always_show_image(GTK_BUTTON(B->button.elem),1);


}

//affichage Function

void Afficher_widget(GtkWidget *F)
{
  gtk_widget_show_all(GTK_WINDOW(F));

}


/**  Les macros du menu   **/


///---------------------------------------------------------------------------------------------------------------------------
///-------------------------------------------    Menu   -----------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------------------------
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************


typedef struct
{
    GtkWidget *barre; ///la barre de menu elle-même
    GtkWidget *menu; ///la partie déroulante qui contient les différentes éléments
    GtkWidget *ptr_menu;///c'est sur ce widget que l'utilisateur clique pour lancer une action
    GtkWidget  *conteneur; /// le conteneur
    gchar* titre;

}MonMenu;


///********************************/
/// Ajouter couleur

void color_menu(MonMenu* M,int choix,color_widg* C)
{
  if(C)
  {
  switch(choix)
  {
      case 1 : add_bgcolor(M->ptr_menu,C->color,C->opacity);   break; /// colorer la tete du menu

      case 2 : add_bgcolor(M->menu,C->color,C->opacity);break; ///colorer les élements du menu
      case 3 : add_bgcolor(M->ptr_menu,C->color,C->opacity); /// les deux
               add_bgcolor(M->menu,C->color,C->opacity); break;
  }

  }
}

/**************************/
///initialiser menu

MonMenu* init_menu(gchar*label,GtkWidget *cont)
{
    MonMenu* menu;
    //allocation de la memoire pour le menu
   menu=(MonMenu*)malloc(sizeof(MonMenu));
    test_allocation(menu,"menu");
    if(label){
        menu->titre= (gchar*)malloc(30*sizeof(gchar));
        test_allocation( menu->titre,"titre menu");
        strcpy(menu->titre,label);
             }
             if(cont)
    menu->conteneur=cont;
    else menu->conteneur=NULL;
return (MonMenu*) menu;

}


/// creer menu
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************
void Creer_Menu(MonMenu* monMenu)
{
    monMenu->barre=gtk_menu_bar_new();
    monMenu->menu=gtk_menu_new();
    monMenu->ptr_menu=gtk_menu_item_new_with_label(monMenu->titre);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(monMenu->ptr_menu),monMenu->menu); /// attacher
    gtk_menu_shell_append(GTK_MENU_SHELL(monMenu->barre), monMenu->ptr_menu); /// insertion du menu dans la barre
if(monMenu->conteneur)
   gtk_container_add(GTK_CONTAINER(monMenu->conteneur),monMenu->barre);

}

/// creer un menu dans une barre spécifique
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************
void Creer_Menu_barre(GtkWidget* barre,MonMenu* monMenu)
{
    monMenu->barre=barre;
    monMenu->menu=gtk_menu_new();
    monMenu->ptr_menu=gtk_menu_item_new_with_label(monMenu->titre);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(monMenu->ptr_menu),monMenu->menu); /// attacher (lier)
    gtk_menu_shell_append(GTK_MENU_SHELL(monMenu->barre), monMenu->ptr_menu); /// insertion du menu dans la barre


}

/// ajouter un element dans un menu
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************
GtkWidget * Ajouter_elem(MonMenu* monMenu,gchar* label,color_widg * couleur)
{
 GtkWidget *ptr_item;
ptr_item= gtk_menu_item_new_with_label(label);
gtk_menu_shell_append(GTK_MENU_SHELL(monMenu->menu),ptr_item);
if(couleur) add_bgcolor(ptr_item,couleur->color,couleur->opacity);
return ptr_item;
}

/// creer un sous-menu
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************
void Creer_sous_menu(MonMenu* menu_principale,MonMenu* Sous_Menu)
{

    Sous_Menu->menu=gtk_menu_new();

   Sous_Menu->ptr_menu=gtk_menu_item_new_with_label(Sous_Menu->titre);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(Sous_Menu->ptr_menu),Sous_Menu->menu);

     gtk_menu_shell_append(GTK_MENU_SHELL(Sous_Menu->conteneur), Sous_Menu->ptr_menu ); /// insertion du sous menu dans le menu principale
}

/*******************************************FIXED********************************************/
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************


/**   Structure du fixed   **/

typedef struct
{
 widg fix;
 dimension d;
 color_widg *couleur;
 
}Monfixed;


Monfixed *init_Fixed(dimension D,gchar*titre,GtkWidget *conten,color_widg *couleur)
{
     Monfixed*F=NULL;

    //allocation de la memoire de F
    F=(Monfixed*) malloc(sizeof (Monfixed));
    //verifier l'allocation
    test_allocation(F,"Monfixed");
    if(titre)//titre no vide
    {//allocation de la memoire du titre du box
        F->fix.titre = (gchar *) malloc(100*sizeof(titre));
        //verifier l'allocation
        test_allocation(F->fix.titre,"titre Box");
        strcpy(F->fix.titre, titre);//affecter le titre
    }
    else F->fix.titre=NULL;
    if(conten) {F->fix.conteneur=conten;}//affecter le conteneur
    else F->fix.conteneur=NULL;
    F->couleur=(color_widg*)malloc(sizeof(color_widg));
    test_allocation(F->couleur,"allocation_couleur");
    if(couleur){
        F->couleur=couleur;
        }
        else{
            F->couleur=NULL;
        }
        F->d=D;
    return((Monfixed*)F);

}


Monfixed *creer_Fixed(Monfixed* F)
{
     F->fix.elem= gtk_fixed_new();

     if(F->fix.conteneur)
         gtk_container_add(GTK_CONTAINER(F->fix.conteneur),F->fix.elem);
     if(F->couleur)
     {
           add_bgcolor(F->fix.elem,F->couleur->color,F->couleur->opacity);
     }
     return((Monfixed*)F);

}



Monfixed *ajouter_Fixed(Monfixed *F,GtkWidget *fils,coordonnees C)
{
    gtk_fixed_put(GTK_FIXED(F->fix.elem),fils,C.x,C.y);

    return((Monfixed*)F);
}


///**********************************************LABEL******************************************************************
///************************************************************************************************************
///************************************************************************************************************

typedef struct
{

    widg label; // objet label
    gchar * texte;//texte du label
    dimension dim; //dimension de la zone texte
    color_widg *couleur;
}Monlabel;


/**********************************************************
La fonction : init_label
-Entrees : titre:le titre du label
 texte : le texte du label
 conten : le conteneur du label
 coordonnee: les coordonnees du label
 dimention : la dimention du label
-Sortie : L : Objet label
-Description: Cette fonction permet d'allouer de l'espace pour
 la structure de type Monlabel, d'initialiser
 ses champs et de la retourner .
***********************************************************/

Monlabel *init_label(gchar *tit,gchar *texte,GtkWidget *conten,dimension D,color_widg*couleur)
{

    Monlabel* L;
    //allocation de la memoire pour l element

    L=(Monlabel*)malloc(sizeof(Monlabel));

    test_allocation(L,"lable");


        //allocation de la memoire pour le titre
        L->label.titre= (gchar*)malloc(30*sizeof(gchar));

        test_allocation( L->label.titre,"titre lable");
       //initialisation du titre
       if(tit)
        strcpy(L->label.titre,tit);
        else L->label.titre=NULL;

if(conten)
    L->label.conteneur=conten;
else  L->label.conteneur=NULL;

L->texte=(gchar*)malloc(300*sizeof(gchar));
test_allocation(L->texte,"text label");
if(texte)
    strcpy(L->texte,texte);
else L->texte=NULL;
if(couleur)
    L->couleur=couleur;
else L->couleur=NULL;
L->dim=D;
return((Monlabel*)L);

}


/**********************************************************
La fonction : creer_label
-Entrees : L : objet label initialisé
-Sortie : L : Objet label créé
-Description:Cette fonction permet la creation d'un label
 en fct des paramètres récuperés de la structure
 Monlabel initialisée.
***********************************************************/


Monlabel *creer_label(Monlabel *L)
{

   //creation d un  label avec un texte
    L->label.elem=gtk_label_new(L->texte);
    //donner un nom au label
    if(L->label.titre) gtk_widget_set_name(L->label.elem,L->label.titre);
    gtk_widget_set_size_request(L->label.elem,L->dim.width,L->dim.height);
    if(L->label.conteneur)
         gtk_container_add(GTK_CONTAINER(L->label.conteneur),L->label.elem);
     if(L->couleur)
     {
           add_bgcolor(L->label.elem,L->couleur->color,L->couleur->opacity);
     }

    return ((Monlabel*)L);

}



/*******************************************SCROLLbarWINDOW********************************************/
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************


typedef struct
{

  GtkWidget*parent; /*pointeur sur le parent de la fenêtre avec défilement*/
  GtkWidget*child; /*pointeur sur le fils de la fenêtre avec défilement*/

}scrolledwinProp;


scrolledwinProp * init_scrol(GtkWidget*parent,GtkWidget*child)
{
    scrolledwinProp *scrolbar;
    //allocation de la memoire pour l element

    scrolbar=(scrolledwinProp*)malloc(sizeof(scrolledwinProp));

    scrolbar->parent =parent;
    scrolbar->child = child;

    return((scrolledwinProp*)scrolbar);

}
  
void PutInContainerWithScrollBar(GtkWidget*parent,GtkWidget*child)
{

    GtkWidget*window= gtk_scrolled_window_new(NULL, NULL);
    //l'ajout du child au conteneur avec barre de défilement  
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(window),child);
    //l’ajout du child au widget parent 
    gtk_container_add(GTK_CONTAINER(parent),window);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(window), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);

}



/*******************************************ComboBox********************************************/
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************



#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct {

 GtkWidget *comboBox; // notre objet
 GtkWidget *container; // le conteneur
 gchar *nom; // le nom de l'objet
 int posx;
 int posy; // la position

} ComboBoxobject;

ComboBoxobject *init_combobox(GtkWidget *pere, gchar *nom,int x,int y){

 ComboBoxobject *cb = NULL;
 cb = (ComboBoxobject*) malloc (sizeof (ComboBoxobject));
 cb->comboBox = NULL;
 cb->container = pere;
 if (nom)
 {
 cb->nom = (gchar*) malloc (35*sizeof (gchar));
 strcpy (cb->nom, nom);
 }
 else cb->nom = NULL;
 cb->posx=x;
 cb->posy=y;

 return ((ComboBoxobject*) cb);

}

ComboBoxobject *create_combobox (ComboBoxobject *cb)
{

 cb->comboBox = gtk_combo_box_text_new();
 gtk_widget_set_name (cb->comboBox, cb->nom);
 return ((ComboBoxobject*) cb);

}

void combobox_add (ComboBoxobject *cb, gchar *text){

 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cb->comboBox),NULL, text);
 gtk_combo_box_set_active(GTK_COMBO_BOX(cb->comboBox), 0);

}

void combobox_add_int(ComboBoxobject *cb, gchar *text){

 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cb->comboBox),NULL, text);
 gtk_combo_box_set_active(GTK_COMBO_BOX(cb->comboBox), 0);

}


///********************************Dialogue********************************/
///*************************************************************************
///*************************************************************************
///*************************************************************************

//structure du dialgue


typedef struct
{
 GtkWidget *dialog;//dialog
 GtkWidget *content_area;//espace de la fenetre dialogue ou on peut ajouter des widgets
 GtkWindow *tran;//transitoire de la fenetre dialogue
 gchar *titre;//Le titre de la fenetre dialogue
 gchar *icon;//icon de la fenetre dialogue
 gint modal;//1 s'il est modal:(dialogue s'affiche une seule fois),0 sinon
 dimension dim;//dimention de la fenetre dialogue
 color_widg *couleur;

}MonDialog;


///****************************************initialiser dialog************************************************************************
///************************************************************************************************************
///************************************************************************************************************


MonDialog *init_dialog(GtkWindow *parent , gchar* titre ,gchar* icon ,gint modal,
 dimension dim,color_widg *couleur)
{

 MonDialog *D;
 D =(MonDialog*)malloc(sizeof(MonDialog));
 //verifier d'allocation
 test_allocation(D,"fenetre dialogue");
 //titre


 D->titre = (gchar*)malloc(30*sizeof(gchar));
 test_allocation(D->titre,"titre dialog");

 if(titre) strcpy(D->titre , titre);
 else D->titre=NULL;
 //icon


 D->icon = (gchar*)malloc(50*sizeof(gchar));

 test_allocation(D->icon,"icon dialog");


     if(icon)
    {//Allocation de la memoire pour le chemin de l'icon
        D->icon = (gchar *) malloc(100*sizeof(gchar));
        test_allocation(D->icon, "Icon fenetre");
        strcpy(D->icon, icon);//donner le titre a notre fenetre
    }
    else D->icon=NULL;

 //transient
 D->tran = parent ;
 //modal
 D->modal = modal;
 //height and width
 D->dim=dim;
 //position

 if(parent)
    D->tran=parent;
 else D->tran=NULL;
 if(couleur)
    D->couleur=couleur;
 else D->couleur=NULL;

 return((MonDialog*)D);
}//fin


///**************************************creer dialog******************
///*********************************************************************
///*********************************************************************
///*********************************************************************

void creer_dialog(MonDialog *D)
{
 //creer un dialog
 D->dialog=gtk_dialog_new();
 //affecter le titre
 if(D->titre)
 gtk_window_set_title( GTK_WINDOW(D->dialog) ,D->titre);
 //affecter l'icon
 if(D->icon)
 gtk_window_set_icon_from_file(GTK_WINDOW(D->dialog),D->icon ,NULL);
 //initialiser content-area
 D->content_area = gtk_dialog_get_content_area(GTK_DIALOG(D->dialog));

 //transient
 gtk_window_set_transient_for(GTK_WINDOW (D->dialog ) , GTK_WINDOW ( D->tran));

 //affecter la dimension
 gtk_widget_set_size_request ( GTK_WIDGET(D->dialog) , D->dim.width ,D->dim.height);

 //si la fenêtre dialogue est modal activer la modalité
 if(D->modal == 1)
 gtk_window_set_modal(GTK_WINDOW(D->dialog) , TRUE);
 else gtk_window_set_modal(GTK_WINDOW(D->dialog) , FALSE);

 //affecter le positionnement
if(D->couleur)
    add_bgcolor(D->dialog,D->couleur->color,D->couleur->opacity);
 if(D->tran)
 gtk_container_add(D->tran,D->dialog);

}//fin

///** Add a button to dialog  **///

void ajouter_button_dialog(MonDialog *D,gchar *buttonlabel,gint idbutton)
{
    gtk_dialog_add_button(D->dialog,buttonlabel,idbutton);
}

///** Ajouter un element to content_area  **///

void ajouter_content_area(MonDialog *D,GtkWidget *elem)
{
    gtk_box_pack_start(D->content_area,elem,0,0,0);
}



/*************************Image****************************************/
/**********************************************************************
 *********************************************************************/

typedef struct
{
    GtkWidget *image;             //widget image
    GtkWidget *event_box ;         // évènement relatif à l'image
    char *chemin;                 //chemin de l'image
    gint largeur;                  // largeur d'image
    gint longueur;                  // longueur d'image
} str_Image;


str_Image* str_Image_init(char *url , int larg,int lon,GtkWidget *pere)
{
    str_Image *img=( str_Image*)malloc(sizeof(str_Image));
    //initialisation du chemin
    img->chemin=(char*)malloc(256*sizeof(char));
    if(url)
    strcpy(img->chemin,url);

//taille de limage
  img->largeur=larg;
  img->longueur=lon;
  img->event_box=pere;

    return ((str_Image*)img);
}//fin de la fonction initialiser_image

str_Image* str_Image_create (str_Image*img)
{

   GdkPixbuf *pixbuf1;
   pixbuf1 =gdk_pixbuf_new_from_file_at_scale(img->chemin,img->largeur,img->longueur,FALSE,NULL);

  img->image = gtk_image_new_from_pixbuf(pixbuf1);
  // l'existance du pere
  if(img->event_box)
  gtk_container_add( img->event_box,img->image);

  return ((str_Image*)img);
}



/*****************************GTK_ENTRY**************************************************************/
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************
///structure de gtk entry

typedef struct
{
    GtkWidget *entry; //widget d'une entree.
    dimension dim; //dimension du zone d entree
    gboolean visible; //le texte est visible ou pas.
    gboolean editable; //on peut saisir par clavier.
    const char* text_to_set; //le texte a saisir.
    const char* text_to_get;//le texte a recuperer.
    gint placeholder;/*0:pas de place holder
                       1:avec place holder*/
    gchar *titre;
    color_widg *couleur;

}MonEntry;

/**********************************************************
La fonction : init_entry
-Entrees : titre:le titre du label
 texte : le texte du label
 conten : le conteneur du label
 coordonnee: les coordonnees du label
 dimention : la dimention du label
-Sortie : L : Objet label
-Description: Cette fonction permet d'allouer de l'espace pour
 la structure de type Monlabel, d'initialiser
 ses champs et de la retourner .
***********************************************************/
MonEntry *init_MonEntry(dimension D,gboolean visibilite,gboolean edit,gchar *txt_set,
                        gchar *txt_get,gchar *tit,gint placeholder,color_widg*couleur)
{

    MonEntry *E=NULL;

    E=(MonEntry*)malloc(sizeof(MonEntry));

    test_allocation(E,"entry");

    E->dim=D;

    E->visible=visibilite;

    E->editable=edit;

    E->text_to_get=(gchar*)malloc(300*sizeof(gchar));

    test_allocation(E,"entry text get");

    if(txt_get) strcpy(E->text_to_get,txt_get);
    else E->text_to_get=NULL;

    E->text_to_set=(gchar*)malloc(100*sizeof(gchar));

    test_allocation(E,"entry text set");

    if(txt_set) strcpy(E->text_to_set,txt_set);
    else E->text_to_set=NULL;

    E->titre=(gchar*)malloc(30*sizeof(gchar));

    test_allocation(E,"entry titre");

    if(tit) strcpy(E->titre,tit);
    else E->titre=NULL;

   E->placeholder=placeholder;

   if(couleur)
    E->couleur=couleur;
   else E->couleur=NULL;

    return ((MonEntry*)E);
}

/**********************************************************
La fonction : creer_Entry
-Entrees : L : objet entry initialisé
-Sortie : L : Objet label créé
-Description:Cette fonction permet la creation d'un label
 en fct des paramètres récuperés de la structure
 Monlabel initialisée.
***********************************************************/
MonEntry *creer_entry(MonEntry *E)
{

    E->entry=gtk_entry_new();

    if(E->text_to_set)
    gtk_entry_set_text(GTK_ENTRY(E->entry),E->text_to_set);
    gtk_entry_get_text(GTK_ENTRY(E->entry));

   //gtk_entry_get_visibility(GTK_ENTRY(E->entry));
   gtk_entry_set_visibility (E->entry,E->visible);

   //gtk_entry_set_editable(GTK_EDITABLE(E->entry),E->editable);

    gtk_widget_set_size_request(E->entry,E->dim.width,E->dim.height);

   if(E->titre)
      gtk_widget_set_name(E->entry,E->titre);
   //E->entry=gtk_search_entry_new();
    if(E->placeholder==1)
          gtk_entry_set_placeholder_text (E->entry,"Ecrire");
    if(E->couleur)
          add_bgcolor(E->entry,E->couleur->color,E->couleur->opacity);

    return ((MonEntry*)E);
}


//Toolbar/////////////////////////////////////////////////////////////////////////

typedef struct toolbarre
{

GtkWidget *toolbar ; // barre d’outil
GtkToolItem *toolitem; // les buttons de la barre
gchar* icon; // l’icon d’apres le stock
gpointer *signal; // signal du button

}tool;

tool* init_toolbar()
  {

    tool *p;
    //allocation de la memoire pour l element

    p=(tool*)malloc(sizeof(tool));
    p->icon= (gchar*)malloc(30*sizeof(gchar));
    
    return((tool*)p);
  }


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














int main(int argc, char *argv[])
{


//initialisation du main
gtk_init(&argc, &argv);

POS p;
p.pos='C';
dimension d={600,700},d2={50,400},d3={40,10},d4={5,10},d5={0,0},d6={500,500},d7={5,130},d8={100,100};

coordonnees c0={5,1},c1={30,1},c2={30,180},c3={30,140},c4={30,230},c5={30,280},c6={30,330},c7={30,380},
             c8={30,430},c9={300,480},c10={300,530},c11={300,600},c12={5,680},c13={30,830};

color_widg couleur1={"white",99},couleur2={"#dcdada",60},couleur3={"green",90};

/// window
Fenetre *F=NULL;
F=init_window("Test Des Fonction GTK+",p,d,1,"index.jpeg",&couleur1,0);
F=creer_Window(F);


//afficher              
Afficher_widget(F->window);
gtk_main();

}

































