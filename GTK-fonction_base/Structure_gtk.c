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
    gchar*color; //color
    gfloat opacity; // opacity
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


/*
 * structure du widget GTK_BOX
 * Expend: n'est utile que si la GtkBox en question n'est pas definie comme homogene (homogeneous=FALSE lors de la creation).
 * Dans ce cas, tous les widgets qui auront ete inseres avec la valeur expand=TRUE se partageront tout l'espace libre de la GtkBox
 * (les widgets avec expand=FALSE n'utiliseront que l'espace qui leur est necessaire).
 */
typedef struct
{
    widg box;        // le box
    gchar type;    // type horizontal ou vertical
    gint homogene; // l'homogeneite des fils du box ( true or false)
    gint spacing; // nombre de pixles entre les fils du box
    gint bordure_taille; //taille de bordure dans le box
    color_widg *color; //couleur du box
    dimension D;
    coordonnees C;

}MonBox;

 /* structure du widget GtkGrid */

typedef struct
{
    widg Grid; // la Grid
    coordonnees C; // les coordonnees de Grid
    dimension D;  // la dimension de Grid
    color_widg *couleur; // la couleur de Grid

}Mongrid;


/*
 * structure d'un boutton
 */
typedef struct
{
    widg button;        // le boutton
    GtkWidget * pere;  // pour les bouttons radios
    gchar *url_im;     // path pour image
    gchar *url_ic ;     // path pour icon
    gint type;       //radio/check/nomale
    dimension dim; //dimension du bouton
    gint mnemo;//la creation du button(mnemonic/label)
    color_widg *color; //couleur de button
    coordonnees C; // les coordonnees de button
}MonBouton;


/*

*  structure D'un SPIN BUTTON

*/

typedef struct
{
    GtkWidget *SpinButton;//SpinButton
    gdouble min;//la valeur minimale
    gdouble max;//la valeur maximale
    gdouble step;//le pas
    gdouble value;//valeur par defaut
    dimension D;
    gint wrap;//0:FALSE , 1:TRUE
    gint digits;//nombre de chiffres en partie decimale
    gint numeric;//0:FALSE(tapez de caracteres en generale) , 1:TRUE(juste les chiffres)
    gint arrondissement;//0:FALSE , 1:TRUE
    color_widg *bgcolor;//background color
    coordonnees C; //les coordonnees de button 
    GtkWidget *conteneur; // le conteneur

}MonSpin;

 /*
 * structure de scale
 */

typedef struct
{
    widg scale;             // objet scale
    GtkOrientation type;    // type de scale : H ou V
    GtkPositionType posDig;// le position dans laquelle la valeur actuelle est afficher
    gdouble Min;          // valeur minimale
    gdouble Max;         //valeur maximale
    gdouble step;       //le pas de deplacement
    gint domDig;        // domain des valeur (1:reels,0:entiers)
    coordonnees C;
    dimension D;

}MonScale;

/**  Structure du fixed   **/

typedef struct
{
    widg fix; // le fixed
    dimension d; // la dimension de fixed 
    coordonnees C; // les coordonnees de fixed

}Monfixed;



/** Structure de Menu   **/
typedef struct
{
    GtkWidget *barre; ///la barre de menu elle-meme
    GtkWidget *menu; ///la partie deroulante qui contient les differentes elements
    GtkWidget *ptr_menu;///c'est sur ce widget que l'utilisateur clique pour lancer une action
    gchar* titre; // le titre
}MonMenu;


/*
* structure de gtk Entry
*/
typedef struct
{

    GtkWidget *entry; //widget d'une entree.
    dimension dim; //dimension du zone d entree
    gboolean visible; //le texte est visible ou pas.
    gboolean editable; //on peut saisir par clavier.
    gboolean frame;//on peut ajouter frame au gtk_entry
    const char* text_to_set; //le texte a saisir.
    const char* text_to_get;//le texte a recuperer.
    gint placeholder; /*0:pas de place holder
                       1:avec place holder*/
    gchar *titre;   // le titre 
    color_widg *couleur; // la couleur 
    coordonnees C;       // les coordonnees
    GtkWidget *conteneur;  // le conteneur 

}MonEntry;

/* 

*  structure l'ABEL
*/

typedef struct

{
    widg label; // objet label
    gchar * texte;//texte du label
    dimension dim; //dimension de la zone texte
    coordonnees C; // les coordonnees
    
}Monlabel;

/* structure du dialgue */

typedef struct
{
    GtkWidget *dialog;//dialog
    GtkWidget *content_area;//espace de la fenetre dialogue ou on peut ajouter des widgets
    GtkWindow *tran;//transitoire de la fenetre dialogue
    gchar *titre;//Le titre de la fenetre dialogue
    gchar *icon;//icon de la fenetre dialogue
    gint modal;//1 s'il est modal:(dialogue s'affiche une seule fois),0 sinon
    dimension dim;//dimention de la fenetre dialogue
    coordonnees crd; // les coordonnees
    color_widg *couleur; // le couleur
    
}MonDialog;


/* Structure COMBOBOX */
typedef struct {

    widg combo; // le COMBOBOX
    dimension dim;  // la dimension de COMBOBOX
    coordonnees Crd; // les coordonnees de COMBOBOX
    gint type;   // le type de COMBOBOX

}MonComboBox;


/* Structure Scroll bare */

typedef struct {

    GtkWidget *swin;
    GtkWidget *cont;     //generalement un window mais peut etre un box
    GtkWidget *contFils;// grid generalement ou fixed
    gint borderWidth;   // le borderWidth
    dimension dim;      // la dimension de scrol bare

}MonScroll;


/*
 * structure de frame
 */
typedef struct {

    widg frame; // le cadre
    GtkShadowType shadow_type;//le type de leombre
    float label_xalign; /*lealignement x de leetiquette le long du bord  superieur du widget*/
    float label_yalign; //lealignement y de leetiquette
    dimension dim; //dimension du cadre
    coordonnees C; // les coordonnees du cadre

}MonFrame;

/*
 * structure de l'image
 */
typedef struct
{
    widg image;         //l'objet image
    gchar *path;       //le chemin vers l'image
    coordonnees ImCrd;//position de l'image
}MonImage;


/*
 * structure de TOOLBARRE
 */
typedef struct toolbarre
{

    GtkWidget *toolbar ; // barre d’outil
    GtkToolItem *toolitem; // les buttons de la barre
    gchar* icon; // l’icon d’apres le stock
    color_widg *color; // la couleur 
    GtkWidget *cont;  // le conteneur

}Montool;

/* la structure  Event_box */

typedef struct
{
    widg eventbox;        // le box
    gint bordure_taille; //taille de bordure dans le box
    color_widg *color; //couleur du box
    dimension D;      // dimension du box

}MonEventBox;


/*** structure Expander*****/

typedef struct
{
    widg expander; // l'expander
    gchar *label;  // label du expander
    GtkWidget *button; // button du expander

}MonExpander;


/* Structure Header Barre */

typedef struct
{
    GtkWidget *hbar;// le header bar
    gchar *title;//titre de la barre
    gchar *subtitle;//sous-titre de la barre
    gint close;//pour fermer la fen�tre
    gint maximize;//pour agrandir la fen�tre
    gint reduire;//pour r�duire la fen�tre
    gchar* icone;//l'url de l'icone

}Monheadbar;



/* structure de Liste */

typedef struct element
{
    GtkWidget* Lval; // la valeur 
    struct element *suiv; // pointeur sur l'element suivant

}Dliste;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///***structure Bilan***///

typedef struct
{
    gint gn;//genetiquement
    gint ta;//tension arterielleaa
    gint db;//diabetique
    gint cr;//cardiaque
    gint pm;//poumon
    
}Bilan;


///***structure Virus***///

typedef struct {
    gint id;     //id de virus
    gchar nomVirus[20]; //Le Nom
    gint virulance;    //virulance
    gfloat letalite[5]; //letalite de virus
    gint distanceCont;  // distance Contamination 
    gint contagion;     // contagion
    
}Virus;

///***structure Etat d'Individu ***///

typedef union {

    gchar sein; //Individu sein 
    Virus virus[4]; // tableau des Virus
    
}etat;


///**  Structure de la personne **///
typedef struct
{
    gint genre; //Le genre 
    gint age;  //l'age d'Individu
    Bilan bl;  // le Bilan d'Individu
    gint vitesse; // la vitesse de deplacement
    etat etatInd; //l'etat d'Individu
    gint vivant;  
    
}Individu;


///**  Structure listObj **///

typedef struct ls
{
    Individu ind; //individu
    GtkWidget *im; 
    gint x,y;
    struct ls*next; //pointeur vers le next element
    struct ls*prev; ////pointeur vers le prev element
    
}listObj;



///**  Structure mov **///

typedef struct {

    MonEventBox *B[Nbcase][Nbcase];
    gint Map[Nbcase][Nbcase];
    GtkWidget *grid;
    listObj*elem;
    gint population;
    gint j;
    int count;
    gint i;
    guint t;
    GtkWidget *lablePop;
    
}mov;



///////////////////////////////////// Infection ////////////////////////////////

/*
 * structure des coordonnees
 */
typedef struct{
    int x; //abscisse
    int y; //ordonne
}coordonees;



/*
 * structure Liste
 */
typedef struct cel
{
    coordonees val;// la valeur de type coordonees
    struct cel *suivant; // pointeur qui pointe vers le suivant
    
}cellulePliste;























