#include <gtk/gtk.h>
#include <string.h>
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

   //gtk_container_set_border_width(W->window,W->bordure_taille);

    return (Fenetre*)W;
}//fin



///----------------------------------- BOX -----------------------------------------------------------------------

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
MonBox*Init_box(gchar*titre,gchar type,gint homo,
                gint spacing,gint border,color_widg *couleur)
{
    MonBox*B=NULL;//declaration du pointeur de type MonBox
    //allocation de la memoire de B
    B=(MonBox*) malloc(sizeof (MonBox));
    //verifier l'allocation
    test_allocation(B,"box");
    if(titre)//titre no vide
    {//allocation de la memoire du titre du box
        B->box.titre = (gchar *) malloc(sizeof(strlen(titre)));
        //verifier l'allocation
        test_allocation(B->box.titre,"titre Box");
        strcpy(B->box.titre, titre);//affecter le titre
    }
    B->type=type;//affecter le type
    //if(pere) B->box.conteneur=pere;//affecter le conteneur

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
    //gtk_container_add(GTK_CONTAINER(B->box.conteneur),B->box.elem);
    gtk_container_set_border_width(B->box.elem,B->bordure_taille);
    if(B->color)
    add_bgcolor(B->box.elem,B->color->color,B->color->opacity);
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
    coordonnees ImCrd;//position du bouton
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

MonBouton *init_Button(GtkWidget *mere, gchar *url1,gchar *url2,coordonnees C,
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


    B->button.conteneur=conte;
    B->ImCrd=C; //initialisation du coordonnees
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

    gtk_container_add(B->button.conteneur,B->button.elem);

    if(B->url_ic)
        ajouter_icon_button(B->url_ic,B);

     if(B->url_im)
        ajouter_image_button(B->url_im,B);

    return ((MonBouton*)B);
}


void Afficher_widget(GtkWidget *F)
{
  gtk_widget_show_all(GTK_WINDOW(F));

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


/**  Les macros du menu   **/


///---------------------------------------------------------------------------------------------------------------------------
///-------------------------------------------    Menu   -----------------------------------------------------------------------------
///-------------------------------------------------------------------------------------------------------------------------


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
    menu->conteneur=cont;
return (MonMenu*) menu;
}


/// creer menu
void Creer_Menu(MonMenu* monMenu)
{
    monMenu->barre=gtk_menu_bar_new();
    monMenu->menu=gtk_menu_new();
    monMenu->ptr_menu=gtk_menu_item_new_with_label(monMenu->titre);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(monMenu->ptr_menu),monMenu->menu); /// attacher
    gtk_menu_shell_append(GTK_MENU_SHELL(monMenu->barre), monMenu->ptr_menu); /// insertion du menu dans la barre

   gtk_container_add(GTK_CONTAINER(monMenu->conteneur),monMenu->barre);

}

/// creer un menu dans une barre spécifique
void Creer_Menu_barre(GtkWidget* barre,MonMenu* monMenu)
{
    monMenu->barre=barre;
    monMenu->menu=gtk_menu_new();
    monMenu->ptr_menu=gtk_menu_item_new_with_label(monMenu->titre);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(monMenu->ptr_menu),monMenu->menu); /// attacher (lier)
    gtk_menu_shell_append(GTK_MENU_SHELL(monMenu->barre), monMenu->ptr_menu); /// insertion du menu dans la barre


}

/// ajouter un element dans un menu
GtkWidget * Ajouter_elem(MonMenu* monMenu,gchar* label,color_widg * couleur)
{
 GtkWidget *ptr_item;
ptr_item= gtk_menu_item_new_with_label(label);
gtk_menu_shell_append(GTK_MENU_SHELL(monMenu->menu),ptr_item);
if(couleur) add_bgcolor(ptr_item,couleur->color,couleur->opacity);
return ptr_item;
}

/// creer un sous-menu
void Creer_sous_menu(MonMenu* menu_principale,MonMenu* Sous_Menu)
{

    Sous_Menu->menu=gtk_menu_new();

   Sous_Menu->ptr_menu=gtk_menu_item_new_with_label(Sous_Menu->titre);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(Sous_Menu->ptr_menu),Sous_Menu->menu);

     gtk_menu_shell_append(GTK_MENU_SHELL(Sous_Menu->conteneur), Sous_Menu->ptr_menu ); /// insertion du sous menu dans le menu principale
}


//ScrolledWindow.


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

//Toolbar

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

//add widget to boxes 
void add_to_box(GtkWidget*box,  GtkWidget* elemtent)
{
    gtk_box_pack_start(GTK_BOX(box), elemtent, FALSE, FALSE, 5);

}


//GTK_Dialog
typedef struct
{

   GtkWidget *dialog; ///widget d'une entrée.
   GtkWindow *parent;
   GtkDialogFlags flags;
   GtkMessageType type;
   GtkButtonsType buttons;
   gchar *message_format;
   gchar *secondrytext;
}Dialog;


Dialog* init_dialog(GtkWindow *parent,GtkDialogFlags flags, GtkMessageType type,GtkButtonsType buttons,gchar * message_format,gchar *secondrytext)
{
   Dialog * mondialog = NULL;

  //allocation mémoire :
  mondialog = (Dialog*)malloc (sizeof (Dialog)); 
  mondialog->message_format = (gchar*)malloc (30*sizeof (gchar));
  mondialog->secondrytext = (gchar*)malloc (30*sizeof (gchar));


   mondialog->parent = parent;
   mondialog->flags = flags;
   mondialog->type=type;
   mondialog->buttons=buttons;
   strcpy (mondialog->message_format, message_format);
   strcpy (mondialog->secondrytext, secondrytext);
   return((Dialog*)mondialog);

}

void create_dialog(Dialog * mondialog)
{
   GtkWidget * hello=NULL;
   hello = gtk_message_dialog_new (mondialog->parent, mondialog->flags, mondialog->type, mondialog->buttons,mondialog->message_format);
   gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (hello), mondialog->secondrytext);

   gtk_dialog_run(GTK_DIALOG (hello)); 
}

// ComboBox


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

































int main(int argc, char *argv[])
{

  gtk_init(&argc, &argv);

  

  GtkWidget*img;
  img=gtk_image_new_from_file("images.jpeg");
  gtk_widget_set_name(img,"test");

    Fenetre* window;
    POS pos;
    dimension d={400,400};

    pos.pos='C';
    //d.height=50;
    //d.width=50;
color_widg t={"red",90};
color_widg t1={"brown",90};
color_widg t2={"white",90};
color_widg t3={"green",90};
color_widg t4={"grey",90};


window=init_window("fenetre",pos,d,1,"imgg.jpeg",NULL,0);
window=creer_Window(window);

MonBox * box;
box=Init_box("box",'V',0,0,0,&t3);
box=creer_Box(box);

//add scrolbar
//*******//
scrolledwinProp *scrollbar;
scrollbar = init_scrol(window->window,box->box.elem);
PutInContainerWithScrollBar(scrollbar->parent,scrollbar->child);

MonBouton*B;
MonBouton*B1,*B2;

coordonnees C={1,2};
dimension D={30,30};

B=init_Button(NULL,NULL,NULL,C,D,"button1", box->box.elem,2,1,&t1);
B=creer_Bouton(B);
B1=init_Button(B->button.elem,NULL,"images.jpeg",C,D,"button2", box->box.elem,2,1,&t2);
B1=creer_Bouton(B1);
B2=init_Button(B->button.elem,NULL,NULL,C,D,"button3", box->box.elem,2,1,&t4);
B2=creer_Bouton(B2);

MonMenu *Me=NULL,*Me2=NULL,*Me3=NULL,*Me4=NULL;

Me=init_menu("allo",box->box.elem);
Creer_Menu(Me);
Me2=init_menu("cv",box->box.elem);

Me3=init_menu("okk",Me->menu);

Creer_Menu_barre(Me->barre,Me2);

GtkWidget *elem;
elem=Ajouter_elem(Me2,"yalah sir",&t2);

Creer_Menu(Me3);
Creer_sous_menu(Me,Me3);

GtkWidget *elem2;
elem2=Ajouter_elem(Me3,"yalah sir2",&t2);
GtkWidget *elem3;
elem3=Ajouter_elem(Me3,"yalah sir3",&t2);
GtkWidget *elem4;
elem4=Ajouter_elem(Me3,"yalah sir4",&t2);


  add_bgcolor(Me->barre,t1.color,t1.opacity);

  //toolbar
  GtkWidget * toolbr;
  tool * toolbar;

  toolbar =init_toolbar(box->box.elem);
  toolbr = creat_toolbar(toolbar);
  toolbr =creat_toolitem(toolbar,GTK_STOCK_SAVE);
  toolbr =creat_toolitem(toolbar,GTK_STOCK_NEW);
  toolbr =creat_toolitem(toolbar,GTK_STOCK_OPEN);
  toolbr =creat_toolitem(toolbar,GTK_STOCK_QUIT);

  add_to_box(box->box.elem,toolbr);

    // add Dialog window
    Dialog * mondialog;
    mondialog = init_dialog(window->window, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "Voulez Vous afficher Une image","");
    create_dialog(mondialog);



  //ADD Combobox

    ComboBoxobject * comb;
    comb = init_combobox(box,NULL,100,100);
    comb = create_combobox(comb);
    combobox_add(comb,"fort");
    combobox_add(comb,"faible");
    combobox_add(comb,"moyenne");
    combobox_add(comb,"tres port");


    ComboBoxobject * comb2;
    comb2 = init_combobox(box,NULL,100,100);
    comb2 = create_combobox(comb2);
    combobox_add(comb2,"faire un choix");
    combobox_add(comb2,"Mip");
    combobox_add(comb2,"Merci");
    combobox_add(comb2,"Nasaa");


     add_to_box(box->box.elem,comb->comboBox);
     add_to_box(box->box.elem,comb2->comboBox);


     Afficher_widget(scrollbar->parent);


gtk_main();
return 0;
}












