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


/*****************************************************************/
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


///----------------------------------- Event BOX -----------------------------------------------------------------------
///****************************************************************************************************************
///************************************************************************************************************
///************************************************************************************************************

typedef struct
{
    widg eventbox;        // le box
    gint bordure_taille; //taille de bordure dans le box
    color_widg *color; //couleur du box
    dimension D;
}MonEventBox;

/*************************************************************
  La fonction : Init_Event_box
*************************************************************/
MonEventBox*Init_Event_box(GtkWidget*pere,gchar*titre,dimension dim,color_widg *couleur)
{
    MonEventBox*B=NULL; //declaration du pointeur de type MonEventBox
    //allocation de la memoire de B
    B=(MonEventBox*) malloc(sizeof (MonEventBox));
    //verifier l'allocation
    test_allocation(B,"eventbox");

    if(titre)//titre no vide
    {//allocation de la memoire du titre du box
        B->eventbox.titre = (gchar *) malloc(100*sizeof(titre));
        //verifier l'allocation
        test_allocation(B->eventbox.titre,"titre Event Box");
        strcpy(B->eventbox.titre, titre);//affecter le titre
    }
    else B->eventbox.titre=NULL;

    if(pere) {B->eventbox.conteneur=pere;} //affectation de conteneur
    else B->eventbox.conteneur=NULL;

    B->color=(color_widg*)malloc(sizeof(color_widg));
    test_allocation(B->color,"allocation_couleur");
    if(couleur){
        B->color=couleur;
        }
        else{
            (B->color)=NULL;
        }
        B->D=dim;

    return ((MonEventBox*)B);

}//fin


/********************creer Event_box**************************
*************************************************************/
MonEventBox*creer_Event_Box(MonEventBox*B,gboolean above_child)
{
    //creation Event Box
    B->eventbox.elem = gtk_event_box_new ();
    /* Set the order in which widgets will receive notification of events. */
    gtk_event_box_set_above_child (GTK_EVENT_BOX (B->eventbox.elem), above_child);
    //affecter le titre
    gtk_widget_set_name(B->eventbox.elem,B->eventbox.titre);
    if(B->eventbox.conteneur)
    gtk_container_add(GTK_CONTAINER(B->eventbox.conteneur),B->eventbox.elem);
    if(B->color)
    add_bgcolor(B->eventbox.elem,B->color->color,B->color->opacity);
    gtk_widget_set_size_request(B->eventbox.elem,B->D.width,B->D.height);

    return ((MonEventBox*)B);
}//fin


/*************************************************************
 La fonction : ajouter_Event_Box
*************************************************************/

void ajouter_Event_Box(GtkWidget*B,GtkWidget*fils)
{
    
    gtk_container_add (GTK_CONTAINER(B),fils);


}//fin


//prototype
static gboolean button_pressed (GtkWidget*, GdkEventButton*, GtkLabel*);


void ADD_Event_To_Box(MonEventBox*B,gchar*name,gpointer * function_name , GtkWidget *child, int num_event)
{
   //add signal
   g_signal_connect (G_OBJECT (B->eventbox.elem), name ,G_CALLBACK (function_name), (gpointer)child);

  /*  GdkEventMask Values:
      1:GDK_BUTTON_PRESS_MASK    //Accept mouse button press events.
      2:GDK_BUTTON_MOTION_MASK    //Accept pointer motion events while any button is pressed.
      3:GDK_BUTTON1_MOTION_MASK   //Accept pointer motion events while button 1 is pressed.
      4:GDK_BUTTON2_MOTION_MASK   //Accept pointer motion events while button 2 is pressed.
      5:GDK_BUTTON3_MOTION_MASK   //Accept pointer motion events while button 3 is pressed.
      6:GDK_EXPOSURE_MASK         //Accept events when a widget is exposed.
      7:GDK_POINTER_MOTION_MASK   //Accept all pointer motion events.
      8:GDK_POINTER_MOTION_HINT_MASK  //Limit the number of GDK_MOTION_NOTIFY events.
      9:GDK_BUTTON_RELEASE_MASK Accept mouse button release events.
      10:GDK_KEY_PRESS_MASK Accept key press events from a keyboard.
      11:GDK_KEY_RELEASE_MASK Accept key release events from a keyboard.*/

    switch(num_event)
  {
      case 1 : gtk_widget_set_events (B->eventbox.elem, GDK_BUTTON_PRESS_MASK);break;
      case 2 : gtk_widget_set_events (B->eventbox.elem, GDK_BUTTON_MOTION_MASK);break;
      case 3 : gtk_widget_set_events (B->eventbox.elem, GDK_BUTTON1_MOTION_MASK);break;
      case 4 : gtk_widget_set_events (B->eventbox.elem, GDK_BUTTON2_MOTION_MASK);break;
      case 5 : gtk_widget_set_events (B->eventbox.elem, GDK_BUTTON3_MOTION_MASK);break;
      case 6 : gtk_widget_set_events (B->eventbox.elem, GDK_EXPOSURE_MASK);break;
      case 7 : gtk_widget_set_events (B->eventbox.elem, GDK_POINTER_MOTION_MASK);break;
      case 8 : gtk_widget_set_events (B->eventbox.elem, GDK_POINTER_MOTION_HINT_MASK);break;
      case 9 : gtk_widget_set_events (B->eventbox.elem, GDK_BUTTON_RELEASE_MASK);break;
      case 10 : gtk_widget_set_events(B->eventbox.elem, GDK_KEY_PRESS_MASK);break;
      case 11 : gtk_widget_set_events(B->eventbox.elem, GDK_KEY_RELEASE_MASK);break;
  }

  gtk_widget_realize(B->eventbox.elem);
}



//affichage Function
void Afficher_widget(GtkWidget *F)
{
  gtk_widget_show_all(GTK_WINDOW(F));

}


int main(int argc, char *argv[])
{


//initialisation du main
gtk_init(&argc, &argv);

POS p;
p.pos='C';
dimension d={600,700},d2={20,40};

coordonnees c0={5,1},c1={30,1},c2={30,180},c3={30,140},c4={30,230},c5={30,280},c6={30,330},c7={30,380},
             c8={30,430},c9={300,480},c10={300,530},c11={300,600},c12={5,680},c13={30,830};

color_widg couleur1={"white",99},couleur2={"#dcdada",60},couleur3={"green",90};

/// window
Fenetre *F=NULL;
F=init_window("Test Des Fonction GTK+",p,d,1,"index.jpeg",&couleur1,0);
F=creer_Window(F);

//creat and init event box
MonEventBox *eventbox=NULL;
eventbox = Init_Event_box(F->window,"eventbox1",d2,&couleur3);
eventbox = creer_Event_Box(eventbox,FALSE);

//test with label
GtkWidget *label;
label = gtk_label_new ("Double-Click Me!");
//////////////////////////////////////////

//add to event box
ajouter_Event_Box(eventbox->eventbox.elem,label);


//add signal
ADD_Event_To_Box(eventbox,"button_press_event",button_pressed , label, 1);



//afficher              
Afficher_widget(F->window);
gtk_main();

}


/* This is called every time a button-press event occurs on the GtkEventBox. */
static gboolean button_pressed (GtkWidget *eventbox,GdkEventButton *event,GtkLabel *label)
{
  if (event->type == GDK_BUTTON_PRESS)
 {
    const gchar *text = gtk_label_get_text (label);
    if (text[0] == 'D')
      gtk_label_set_text (label, "I Was Double-Clicked!");
    else
       gtk_label_set_text (label, "Double-Click Me Again!");
 }

return FALSE;
}











