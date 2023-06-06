#include <gtk/gtk.h>
#include<string.h>
#include<stdlib.h>



/*

* structure d'un bouton

*/

/*

* structure de dimension d'un widget

*/

typedef struct

{

    gint height; //longueur
    gint width; //largeur

}dimension;

/*

* structure des coordonn?es

*/

typedef struct

{

    gint x; //abscisse

    gint y;//ordonne

}coordonnees;

/*


* structure d'un widget fils

*/

typedef struct

{

    GtkWidget *elem; //l'?l?ment lui m?me

    gchar *titre; //titre du widget

    GtkWidget *conteneur;//le p?re conteneur du widget

}widg;


/***** Structure du bouton  *******/
typedef struct

{
    widg buton; // le bouton

    GtkWidget * pere; // pour les boutons radios

    gchar *url; // path

    gint type; // 1 :normale/2 :radio/3 :check/4 :spin

    coordonnees ImCrd;//position du bouton

    dimension dim; //dimension du bouton

    gint mnemo;/*la creation du button(mnemonic/label)

                                       1    /  0*/
}MonBouton;



/*

* Le label est un objet qui permet la craation dun champ texte.

*/

typedef struct

{
    widg label; // objet label

    gchar * texte;//texte du label

    coordonnees Crd;//position de de la zone texte

    dimension dim; //dimension de la zone texte

}Monlabel;



///*************structure de menue***************///

typedef struct
{
GtkWidget *barre; //la barre de menu elle-même
gchar *titre; // titre du menu
GtkWidget *menu; /*la partie déroulante qui contient les différentes
 éléments*/
GtkMenuItem *ptr_menu;/*c'est sur ce widget que l'utilisateur clique
 pour lancer une action*/
 coordonnees Crd; //position du menu
 dimension dim; //dimension du menu
}MonMenu;


///** structure de gtk_entry **///

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


///** structure du frame  **///

typedef struct {
 widg frame; // le cadre
 GtkShadowType shadow_type;//le type de l’ombre
 gfloat label_xalign; /*l’alignement x de l’étiquette le long du bord
 supérieur du widget*/
 gfloat label_yalign; //l’alignement y de l’étiquette
 dimension dim; //dimension du cadre

}MonFrame;


///****** initialiser une frame  ******///

MonFrame *init_frame(GtkShadowType shadow_t,gfloat label_x,gfloat label_y,dimension d )
{
    MonFrame *F=NULL;
   // test_allocation(F,"frame");
   F=(MonFrame*)malloc(sizeof(MonFrame));
   if(!F)
   {
       printf("ygfhgvhhg\n");
       exit(0);
   }
    F->shadow_type=shadow_t;
    F->label_xalign=label_x;
    F->label_yalign=label_y;
    F->dim=d;
    return((MonFrame*)F);
}



///*****************initialiser un menue*******************///


MonMenu *initialiser_menue(gchar *tit,coordonnees C,dimension D)
{

    MonMenu *M=NULL;
    M=(MonMenu*)malloc(sizeof(MonMenu));
    test_allocation(M,"menue");
    M->Crd=C;
    M->dim=D;
    M->titre=(gchar*)malloc(30*sizeof(gchar));
    test_allocation(M->titre,"titre menu");
    return ((MonMenu*)M);
}



///*********************creer menue**********************///

MonMenu *creer_menue(MonMenu*M)
{

  M->barre=gtk_menu_bar_new();
  M->menu=gtk_menu_new();
  M->ptr_menu=gtk_menu_item_new_with_label(M->titre);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM (M->ptr_menu), M->menu);
  gtk_menu_shell_append (GTK_MENU_SHELL(M->barre),M->ptr_menu);

  return((MonMenu*)M);

}



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




Monlabel *init_label(gchar *tit,gchar *texte,GtkWidget *conten,

                     coordonnees C,dimension D)

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



    if(tit){
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




/**********************************************************
La fonction : init_button
-Entrees : mere : la mere du button
          url: chemin de l'icone du boutton
          C:les coordonnes du bouton
          D:la dimention du bouton
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



MonBouton *init_Button(GtkWidget *mere, gchar *urll,coordonnees C,

                       dimension D,gchar*tit, GtkWidget*conte,gint type, gint mnemo)
{

    MonBouton*B;

    //allocation de la memoire pour le bouton

    B=(MonBouton*)malloc(sizeof(MonBouton));

    test_allocation(B,"bouton");

    //initialisation du widg

    if(tit){

        B->buton.titre= (gchar*)malloc(30*sizeof(gchar));

        test_allocation( B->buton.titre,"titre");

        strcpy( B->buton.titre,tit);

    }
    if(conte)
    {
        B->buton.conteneur=conte;
    }

    if(urll){//allocation de la memoire pour l'url

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

    B->pere=mere;

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


///**  fonction de liaison avec css **///

void myCSS(void){

    GtkCssProvider *provider;

    GdkDisplay *display;

    GdkScreen *screen;

    provider = gtk_css_provider_new ();

    display = gdk_display_get_default ();

    screen = gdk_display_get_default_screen (display);

    gtk_style_context_add_provider_for_screen

    (screen, GTK_STYLE_PROVIDER (provider),

     GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "C:/Users/DELL/Desktop/GTK_CSS/theme.css";

    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);

    g_object_unref (provider);

}



///** fonction Pour  changer la couleur du bouton **///

void add_bgcolor(GtkWidget*widget,gchar*couleur,gfloat opc)

{

    GdkRGBA color;

    gdk_rgba_parse(&color,couleur);

    color.alpha=opc;

    gtk_widget_override_background_color(widget,GTK_STATE_FLAG_NORMAL,&color);

}



///** la fonction main  **///

int main(int argc,char** argv)

{

    gtk_init(&argc,&argv);

    //myCSS();

    GdkPixbuf *pixbuf;

    MonEntry *E=NULL;

    MonBouton*B=NULL,*B2=NULL,*B3=NULL;

    Monlabel *L=NULL;
    MonFrame *F=NULL;
    MonMenu *M=NULL;

    widg *grid;

    coordonnees c1={10,10};

    dimension d1={2,10};

    coordonnees c2={50,50};

    dimension d2={50,50};

    coordonnees c={20,20};

    dimension d={2,2};

    pixbuf=gdk_pixbuf_new_from_file("images.jpeg",NULL);

    GtkWidget*window,*box,*box2,*box3,*window2;

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

    window2=gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_icon(GTK_WINDOW(window),pixbuf);

    g_signal_connect(window,"delete_event",G_CALLBACK(gtk_main_quit),NULL);

    box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,50);

    box2=gtk_box_new(GTK_ORIENTATION_VERTICAL,50);

    box3=gtk_box_new(GTK_ORIENTATION_VERTICAL,50);

    grid=init_creer_Grid("grid",box);

    // le programme commence d'ici

    B=init_Button(NULL,NULL,c1,d1,"aaa",box,3,0);

    B=creer_Bouton(B);


    B2=init_Button(B->buton.elem,NULL,c1,d1,"bbb",box,3,0);

    B2=creer_Bouton(B2);


    B3=init_Button(NULL,NULL,c1,d1,"www",box,4,0);

    B3=creer_Bouton(B3);


     gtk_box_pack_start(B3->buton.conteneur,B3->buton.elem,FALSE,FALSE,100);

     GtkShadowType type=GTK_SHADOW_ETCHED_IN;
     F=init_frame(type,60,60,d);



    L=init_label("ser","3la molana",NULL,c2,d2);
    L=creer_label(L);



    E=init_MonEntry(d,FALSE,FALSE,"ecrire",NULL,"entry");
    E=creer_entry(E);

    M=initialiser_menue("menu1",c1,d1);
    M=creer_menue(M);

    add_bgcolor(B->buton.elem,"red",9999);
    add_bgcolor(B2->buton.elem,"green",9999);

     dimension ddd={300,300};
     coordonnees ccc={300,300};


    ajouter_Grid_pos(grid,B->buton.elem,B->ImCrd,B->dim);

    ajouter_Grid_cote_de(grid,B2->buton.elem,B->buton.elem,GTK_POS_RIGHT,B2->dim);

    ajouter_Grid_pos(grid,L->label.elem,ccc,ddd);
   // gtk_box_pack_start(GTK_BOX(box2),L->label.elem,FALSE,FALSE,50);
    
    gtk_box_pack_start(GTK_BOX(box2),M->barre,FALSE,FALSE,50);
    gtk_box_pack_start(GTK_BOX(box2),E->entry,FALSE,FALSE,50);

    gtk_box_pack_start(GTK_BOX(box),box2,FALSE,TRUE,50);

    gtk_box_pack_start(GTK_BOX(box),grid->elem,FALSE,TRUE,50);

   // gtk_box_pack_start(GTK_BOX(box3),M->menu,FALSE,FALSE,10);

    // gtk_box_pack_start(GTK_BOX(box),box3,TRUE,TRUE,0);


//    g_signal_connect(G_OBJECT(B->buton->elem), "clicked",
//
//                     G_CALLBACK(demande_confirmation), (gpointer) window2);

    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;



}


