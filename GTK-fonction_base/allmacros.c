#include <gtk/gtk.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    gint height; //longueur
    gint width; //largeur

}dimension;


typedef struct

{

    gint x; //abscisse

    gint y;//ordonne

}coordonnees;


typedef struct

{

    GtkWidget *elem; //l'element lui meme

    gchar *titre; //titre du widget

    GtkWidget *conteneur;//le pere conteneur 

}widg;  

typedef struct
{
    widg buton; // le bouton

    GtkWidget * pere; // pour les boutons radios

    gchar *url; // path

    gint type; // 1 :normale /2 :radio/3 :check/4 :spin

    coordonnees ImCrd;//position du bouton

    dimension dim; //dimension du bouton

    gint mnemo; //la creation du button(mnemonic/label)

                                       
}MonBouton;

typedef struct

{

    GtkWidget *entry; //widget d'une entree.

    dimension dim; //dimension du zone d?entree

    gboolean visible; //le texte est visible ou pas.

    gboolean editable; //on peut saisir par clavier.

    const char* text_to_set; //le texte a saisir.

    const char* text_to_get;//le texte a recuperer.

    gchar *titre;

}MonEntry;


typedef struct

{
    widg label; // objet label

    gchar * texte;//texte du label

    coordonnees Crd;//position de de la zone texte

    dimension dim; //dimension de la zone texte

}Monlabel;




/**********************************************************
La fonction : test allocation
-Entrees : pointeur :
-nom:le nom de l element

-Description: Cette fonction permet de tester l allocation
s'elle est bien faite
***********************************************************/


void test_allocation(void *pointeur, char*nom)
{

    if(!pointeur) {

        printf("erreur d'allocation du %s\n", nom);
        exit(-1);

    }

}


//label

Monlabel *init_label(gchar *tit,gchar *texte,GtkWidget *conten,coordonnees C,dimension D)
{

     Monlabel* L;
    //allocation de la memoire pour l element

    L=(Monlabel*)malloc(sizeof(Monlabel));
    test_allocation(L,"lable");

    if(tit){
        //allocation de la memoire pour le titre
        L->label.titre= (gchar*)malloc(30*sizeof(gchar));
        test_allocation( L->label.titre,"titre lable");
       //initialisation du titre
        strcpy(L->label.titre,tit);
    }

    if(tit)
     {
       // allocation de la memoire pour le texte
        L->texte=(gchar*)malloc(300*sizeof (gchar));

        test_allocation(  L->texte,"text lable");
        //initialisation du texte
        strcpy(L->texte,texte);

    }

    //initialisation du coordonnees
    L->Crd=C;
    // initialisation du dimention
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

    return ((Monlabel*)L);



}


//Entry

MonEntry *init_MonEntry(dimension D,gboolean visibilite,gboolean edit,gchar *txt_set,gchar *txt_get,gchar *tit)

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

    E->text_to_set=(gchar*)malloc(100*sizeof(gchar));

    test_allocation(E,"entry text set");

    if(txt_set) strcpy(E->text_to_set,txt_set);

    E->titre=(gchar*)malloc(30*sizeof(gchar));

    test_allocation(E,"entry titre");

    if(tit) strcpy(E->titre,tit);


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

    gtk_entry_set_text(GTK_ENTRY(E->entry),E->text_to_set);

    gtk_entry_get_text(GTK_ENTRY(E->entry));

    gtk_entry_get_visibility(GTK_ENTRY(E->entry));

    gtk_widget_set_size_request(E->entry,E->dim.width,E->dim.height);

    gtk_widget_set_name(E->entry,E->titre);

    E->entry=gtk_search_entry_new();

    return ((MonEntry*)E);

}


//Buttons


MonBouton *init_Button(GtkWidget *pere, gchar *urll,coordonnees C,dimension D,gchar* tit, GtkWidget* conte,gint type, gint mnemo)
{

     MonBouton*B;

    //allocation de la memoire pour le bouton

    B=(MonBouton*)malloc(sizeof(MonBouton));

    test_allocation(B,"bouton");

    //initialisation du widg

    if(tit){

        B->buton.titre = (gchar*)malloc(30*sizeof(gchar));

        test_allocation( B->buton.titre,"titre");

        strcpy( B->buton.titre,tit);

    }
    if(conte)
    {
        B->buton.conteneur=conte;
    }

    if(urll){

        //allocation de la memoire pour l'url
        B->url=(gchar*)malloc(100*sizeof(gchar));

        test_allocation(B->url,"url bouton");
       //initialisation de l url
        strcpy(B->url,urll);
    }

    //initialisation du coordonnees

    B->ImCrd=C;

    //initialisation du dimention

    B->dim=D;

    //initialisation du widget pere

    B->pere=pere;

    //initialisation du type de bouton

    B->type=type;

    B->mnemo=mnemo;

    // return le bouton

    return ((MonBouton*)B);
}


/**********************************************************
La fonction : creer_normal_button
-Entrees : B : objet bouton initialisé
-Sortie : B : Objet bouton créé
-Description:Cette fonction permet la creation d'un boutton
normal en fct des paramètres récuperés de la structure
 ButtonObject initialisée.
***********************************************************/

MonBouton *creer_normal_Bouton(MonBouton *B)
{
    if(B->buton.titre)
    {

        switch(B->mnemo)
        {

            case 0:// creation du bouton with label

                B->buton.elem=gtk_button_new_with_label(B->buton.titre);break;

            case 1: // creation du bouton with mnemonic

                B->buton.elem=gtk_button_new_with_mnemonic(B->buton.titre);break;

        }
         // donner un nom au bouton
        gtk_widget_set_name(B->buton.elem,B->buton.titre);
    }

   // creation du bouton sans titre
    else

    {
        B->buton.elem = gtk_button_new();
    }

    gtk_widget_set_size_request(B->buton.elem,B->dim.width,B->dim.height);

    //retourner le bouton
    return ((MonBouton*)B);
}


/**********************************************************
La fonction : creer_radio_button
-Entrees : B : objet bouton initialisé
-Sortie : B : Objet bouton créé
-Description:Cette fonction permet la creation d'un boutton
radio en fct des paramètres récuperés de la structure
 ButtonObject initialisée.
***********************************************************/


MonBouton *creer_radio_Bouton(MonBouton *B)
{
    if(B->buton.titre)
    {
        switch(B->mnemo)

        {

            case 0:// creation du bouton with label

                //si le bouton a un pere
                if(B->pere)

                {
                    B->buton.elem=gtk_radio_button_new_with_label(
                       //affecter le bouton au group du bouton pere
                      gtk_radio_button_get_group(GTK_RADIO_BUTTON(B->pere)),B->buton.titre);
                }
                else
                {
                    B->buton.elem=gtk_radio_button_new_with_label(NULL,B->buton.titre);
                }

                break;

            case 1:// creation du bouton with mnemonic

                if(B->pere)

                    B->buton.elem=gtk_radio_button_new_with_mnemonic(

                     gtk_radio_button_get_group(GTK_RADIO_BUTTON(B->pere)),B->buton.titre);

                else B->buton.elem=gtk_radio_button_new_with_mnemonic(NULL,B->buton.titre);

                break;

        }
         // donner un nom au bouton
        gtk_widget_set_name(B->buton.elem,B->buton.titre);
    }

     //creation du bouton sans titre
     else B->buton.elem = gtk_button_new();

    gtk_widget_set_size_request(B->buton.elem,B->dim.width,B->dim.height);

    return ((MonBouton*)B);

}





/**********************************************************
La fonction : creer_check_button
-Entrees : B : objet bouton initialisé
-Sortie : B : Objet bouton créé
-Description:Cette fonction permet la creation d'un boutton
check en fct des paramètres récuperés de la structure
 ButtonObject initialisée.
***********************************************************/



MonBouton *creer_check_Bouton(MonBouton *B)

{
    if(B->buton.titre)
    {
        switch(B->mnemo)
        {
            case 0:// creation du bouton with label

                B->buton.elem=gtk_check_button_new_with_label(B->buton.titre);break;

            case 1:// creation du bouton with mnemonic

                B->buton.elem=gtk_check_button_new_with_mnemonic(B->buton.titre);break;

        }
     //donner un nom au bouton
        gtk_widget_set_name(B->buton.elem,B->buton.titre);
    }
     // creation du bouton sans titre
    else B->buton.elem = gtk_button_new();

    gtk_widget_set_size_request(B->buton.elem,B->dim.width,B->dim.height);


    return ((MonBouton*)B);

}

/**********************************************************
La fonction : creer_toggle_button
-Entrees : B : objet bouton initialisé
-Sortie : B : Objet bouton créé
-Description:Cette fonction permet la creation d'un boutton
toggle en fct des paramètres récuperés de la structure
 ButtonObject initialisée.
***********************************************************/

MonBouton *creer_toggle_Bouton(MonBouton *B)

{
    if(B->buton.titre)
    {
        switch(B->mnemo)
        {
            case 0:// creation du bouton with label

                B->buton.elem=gtk_toggle_button_new_with_label(B->buton.titre);break;

            case 1:// creation du bouton with mnemonic

                B->buton.elem=gtk_toggle_button_new_with_mnemonic(B->buton.titre);break;
        }
        gtk_widget_set_name(B->buton.elem,B->buton.titre);
    }

    //creation du bouton sans titre
    else B->buton.elem = gtk_button_new();

    gtk_widget_set_size_request(B->buton.elem,B->dim.width,B->dim.height);

    return ((MonBouton*)B);

}


/**********************************************************
La fonction : creer_button
-Entrees : B : objet bouton initialisé
-Sortie : B : Objet bouton créé
-Description:Cette fonction permet la creation d'un boutton
 en fct des paramètres récuperés de la structure
 ButtonObject initialisée.
***********************************************************/


MonBouton *creer_Bouton(MonBouton *B)
{
    switch(B->type)

    {

        case 1: B=creer_normal_Bouton(B) ;  break;    /* normal button */

        case 2: B=creer_radio_Bouton(B);break;         /* radio button */

        case 3: B= creer_check_Bouton(B); break;    /* check button*/

        case 4: B= creer_toggle_Bouton(B); break;    /* toggle button*/
    }

    return ((MonBouton*)B);

}

///** fonction Pour  changer la couleur du bouton **///

void add_bgcolor(GtkWidget*widget,gchar*couleur,gfloat opc)
{

    GdkRGBA color;
    gdk_rgba_parse(&color,couleur);
    color.alpha=opc;
    gtk_widget_override_background_color(widget,GTK_STATE_FLAG_NORMAL,&color);

}

//Grid

/**********************************************************
La fonction : init_creer_grid
-Entrees : titre : titre du grid
 conteneur : conteneur du grid
-Sortie : grid
-Description: Cette fonction permet d'allouer de l'espace pour
 la structure de type widg, d'initialiser et de creer
 ses champs et de la retourner .
***********************************************************/

widg *init_creer_Grid(gchar*titre,GtkWidget*conteneur)

{

    //allocation pour l element
     widg *grid=(widg *) malloc(sizeof(widg));

    //allocation pour le titre
    grid->titre=(gchar*) malloc(sizeof (strlen(titre)));

   //initialisation du conteneur
    grid->conteneur=conteneur;

    //creation de l element
    grid->elem=gtk_grid_new();

    //initialisation du titre
    gtk_widget_set_name(grid->elem,titre);

    gtk_container_add(GTK_CONTAINER(grid->conteneur),grid->elem);

    return (widg*)grid;

}


// ajouter un element a un grid

widg *ajouter_Grid_pos(widg *grid,GtkWidget*fils,coordonnees filsCrd,dimension filsDim)

{

    gtk_grid_attach(GTK_GRID(grid->elem),fils,filsCrd.x,filsCrd.y,filsDim.width,filsDim.height);

    return (widg*)grid;
}

widg *ajouter_Grid_cote_de(widg *grid,GtkWidget*fils,GtkWidget *frere,GtkPositionType side,dimension filsDim)

{

    gtk_grid_attach_next_to(GTK_GRID(grid->elem),fils,frere,side,filsDim.width,filsDim.height);

    return (widg*)grid;

}



int main(int argc,char** argv)

{

    gtk_init(&argc,&argv);

    MonBouton*B=NULL,*B2=NULL,*B3=NULL,*radio1=NULL,*radio2=NULL,*radio3=NULL;
    coordonnees c1={0,0};
    dimension d1={0,0};
    dimension d={2,2};
    MonEntry *E=NULL;
    Monlabel *L=NULL;
    widg *grid;

    GdkPixbuf *pixbuf;
    pixbuf=gdk_pixbuf_new_from_file("images.jpeg",NULL);

    
    GtkWidget*window,*box,*box2,*box3,*window2;

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);
    gtk_window_set_icon(GTK_WINDOW(window),pixbuf);
 
    box = gtk_box_new(TRUE, 0);
    

   
    // le programme commence d'ici

    B=init_Button(NULL,NULL,c1,d1,"check1",box,3,0);
    B=creer_Bouton(B);

    B2=init_Button(B->buton.elem,NULL,c1,d1,"check2",box,3,0);
    B2=creer_Bouton(B2);


     B3=init_Button(NULL,NULL,c1,d1,"www",box,4,0);
     B3=creer_Bouton(B3);

    //radio
    radio1=init_Button(NULL,NULL,c1,d1,"radio1",box,2,0);
    radio1=creer_Bouton(radio1);

    radio2=init_Button(radio1->buton.elem,NULL,c1,d1,"radio2",box,2,0);
    radio2=creer_Bouton(radio2);


    radio3=init_Button(radio1->buton.elem,NULL,c1,d1,"radio3",box,2,0);
    radio3=creer_Bouton(radio3);


    //ajouter color
    add_bgcolor(B->buton.elem,"red",9999);
    add_bgcolor(B2->buton.elem,"green",9999);  

     // test des types des buttons
     gtk_box_pack_start(GTK_BOX(radio1->buton.conteneur),radio1->buton.elem,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(radio2->buton.conteneur),radio2->buton.elem,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(radio3->buton.conteneur),radio3->buton.elem,FALSE,FALSE,0);

     gtk_box_pack_start(GTK_BOX(B->buton.conteneur),B->buton.elem,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(B2->buton.conteneur),B2->buton.elem,FALSE,FALSE,0);

     gtk_box_pack_start(GTK_BOX(B3->buton.conteneur),B3->buton.elem,FALSE,FALSE,0);

     //tester GTKentry with icon
     E=init_MonEntry(d,FALSE,FALSE,"ecrire",NULL,"entry");
     E=creer_entry(E);
     gtk_box_pack_start(GTK_BOX(box), E->entry, TRUE, FALSE, 0);

     //tester label
      L=init_label("label","tester label",NULL,c1,d1);
      L=creer_label(L);
      gtk_box_pack_start(GTK_BOX(box), L->label.elem, TRUE, FALSE, 0);


    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;


}
































