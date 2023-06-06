
typedef struct
{
    gchar *nom;
    gchar *prenom;
    gchar *cne;
    gchar *titre;

}Etatcivil;


typedef struct
{

	 gboolean diabete;
	 gboolean asthmatiques;


    

}Etatmedical;



// liste chainée qui contient le chemin d'une personne 
typedef struct cel
{

	gint codechemin; ./* [0..3]   0: forward  1 : right  2 :back  3: left */ 
	cel * svt;

}Away;


typedef struct
{

	Etatcivil * EC; // l'etat civile de la personne 
	Etatmedical * EM; //l'etat medical de la personne

	gboolean viruspropage ;//un boolean qui indique si la personne est porteuse du virus qui se propage 

    gchar * mouvement ; // type de mouvement : left , right , back , forward

    Away * chemin; // une liste qui enregistre le chemin de chaque personne
	 
  
}personne;

