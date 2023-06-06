#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED


typedef struct arbre
{
    int info; // la valeur contenue dans un noeud
    struct arbre* tleft; // pointeur sur le fils gauche
    struct arbre* tright;// pointeur sur le fils droit

} tree;


// creation d'un noeud contient la valeur : elm
tree* arbre_creer_noeud(int elm)
{
    tree*pt;// declaration d'un pointeur
    pt=(tree*)malloc(sizeof(tree));// allocation dynamique
      // si l'allocation a echoue
     if(!pt)
     { printf("\n erreur d'allocation ");
       exit(0);
     }

    pt->info=elm;// la valeur de pt est elm qu'on a declare
    pt->tleft=pt->tright= NULL;

    return((tree*)pt);

}

// affiche prefix
void prefix(tree*Ar)
{
    if(Ar)
    {   // affichage de la valeur de la racine
        printf("%d \t",Ar->info);
        // appel de la fonction pour l'affichage de la valeur du fils gauche
        prefix(Ar->tleft);
        // appel de la fonction pour l'affichage de la valeur du fils gauche
        prefix(Ar->tright);
    }
}


// affiche infix
void infix(tree*Ar)
{
    if(Ar)
    {   // appel de la fonction pour l'affichage de la valeur du fils gauche
        infix(Ar->tleft);
        // affichage de la valeur de la racine
        printf("%d \t",Ar->info);
        // appel de la fonction pour l'affichage de la valeur du fils gauche
        infix(Ar->tright);
    }
}

 // affiche posfix
void posfix(tree*Ar)
{
    if(Ar)
    {   // appel de la fonction pour l'affichage de la valeur du fils gauche
        posfix(Ar->tleft);
        // appel de la fonction pour l'affichage de la valeur du fils gauche
        posfix(Ar->tright);
        // affichage de la valeur de la racine
        printf("%d \t",Ar->info);
    }
}


int arbre_taille(tree*Ar)
{   int t=0;
    if(Ar)
    {
       return(1+arbre_taille(Ar->tright)+arbre_taille(Ar->tleft));
    }
}

int arbre_EstVide (tree*Ar) {

	return (Ar == NULL);
}

int arbre_EstFeuille(tree*Ar) {

	return (Ar != NULL && arbre_EstVide(Ar->tleft) && arbre_EstVide(Ar->tright));
}

/*Nombre des feuilles*/
int arbre_NbFeuilles (tree*Ar) {

	if (!arbre_EstVide(Ar))
	 {
		if (arbre_EstFeuille(Ar))
			return 1 ;	/* racine est une feuille */
		else
			/* somme des feuilles des sous-arbres gauche et droit */
			return (arbre_NbFeuilles(Ar->tleft) +
					arbre_NbFeuilles(Ar->tright)) ;
	}
    return 0 ; /*un arbre vide n'a pas de feuille */
}

/*Nombre des noeuds internes*/
int Nb_Noeuds_Internes(tree*Ar){

    if(!Ar) return((int)0);
    return((int) arbre_taille(Ar)-arbre_NbFeuilles(Ar));
}

/*Tester si l'arbre est parfait*/
int Est_Parfait(tree*Ar){
    if((arbre_NbFeuilles(Ar) - Nb_Noeuds_Internes(Ar)) == 1) return((int)1);
    return((int)0);
}

//Hauteur arbre = la pronfondeur Maximal = distance max entre un noeud et la racine
int max (int h1, int h2) {
	if (h1>h2)
		return h1 ;
	else
       return h2 ;
}
int arbre_Hauteur(tree*Ar)
 {

	if (!arbre_EstVide(Ar))
	 {
		if (arbre_EstFeuille(Ar))
		      return 1 ;	/* une feuille, arbre de hauteur 1 */
		else
		      /* 1 + max des hauteurs des sous-arbres gauche et droit */
		      return 1 + max(arbre_Hauteur(Ar->tleft), arbre_Hauteur(Ar->tright));
	}
    return 0 ; /* un arbre vide est de hauteur 0 */

} ;

/* Parcour d'une arbre en Largeur */
void ParcoursLargeur(tree* Ar)
{
    int H = arbre_Hauteur(Ar);
    for(int i=1;i<H+1;i++)
    {
        printf("\n\n");
        afficher_niveau(Ar,i);
    }
}

int afficher_niveau(tree*Ar,int nv)
{
    if(!Ar) return((int)NULL);
    if(nv==1)
    {
       printf("%d || ",Ar->info);
    }
    else if(nv >1)
    {
       afficher_niveau(Ar->tleft,nv-1);
       afficher_niveau(Ar->tright,nv-1);
    }
}


/* nombre d occurence*/
int arbre_nbOccurence_(tree*Ar,int val){
	if(arbre_EstVide(Ar)) return 0;
	if(Ar->info==val)
		return 1+arbre_nbOccurence_(Ar->tright,val)+arbre_nbOccurence_(Ar->tleft,val);
	return(arbre_nbOccurence_(Ar->tright,val)+arbre_nbOccurence_(Ar->tleft,val));
}

void arbre_occurence_vall(tree*Ar,int *Tab)
{
  int i;
  for(i=0;i<10;Tab[i++]=0);
  //parcour larbre en INC tableau
  arbre_compteur(Ar,Tab);
  for(int i=0;i<10;i++)
    {
       printf("\nla valeur %d se repetes %d fois dans larbre:",i,Tab[i]);

    }

}
void arbre_compteur(tree*Ar,int *Tab)
{
    if(Ar)
    {
      Tab[Ar->info]++;
      arbre_compteur(Ar->tleft,Tab);
      arbre_compteur(Ar->tright,Tab);
    }
}

/*Somme des Noeuds*/
int sommeNoeuds_(tree*Ar){
	if(arbre_EstVide(Ar)) return 0;
	return Ar->info+sommeNoeuds_(Ar->tright)+sommeNoeuds_(Ar->tleft);
}


/* ***********************************NON____ORDONNER___*********************************************** */

/*Inserer un noeud dans un Arbre Binaire Non Ordonné
  Entreés : Pointeur Ar vers l'arbre Binaire, la valeur inserer
  Sortie: l'arbre apres l'insertion de noued
*/
tree* Inserer_Noeud_Non_OR(tree * Ar, int val){

    if(!Ar) return((tree*)arbre_creer_noeud(val));
    //si la taille des sous arbres gauche et droit identique , inserer dans la gauche
    if(arbre_taille(Ar->tleft) == arbre_taille(Ar->tright)) Ar->tleft=Inserer_Noeud_Non_OR(Ar->tleft,val);

    else if(arbre_taille(Ar->tleft) > arbre_taille(Ar->tright))
    {
        if(Est_Parfait(Ar->tleft)) Ar->tright = Inserer_Noeud_Non_OR(Ar->tright,val);
        else Ar->tleft=Inserer_Noeud_Non_OR(Ar->tleft,val);
    }
    return((tree*)Ar);
}

/* calculer le Max d'un arbre Binaire Non Ordonné
  Entreés : Pointeur Ar vers l'arbre Binaire
  Sortie: Le Max de l'arbre
*/
int Max_Non_Ord(tree*Ar)
{
   if (arbre_EstVide(Ar)) return((int)NULL);/* arbre vide n'a pas de Max */
   if (arbre_EstFeuille(Ar)) return ((int)Ar->info);/* l'arbre avec un seule element , donc le max est la racine*/
   //sinon
   int Max_val = Ar->info;

   if(!arbre_EstVide(Ar->tleft))
   {
    Max_val=max(Max_Non_Ord(Ar->tleft),Max_val);
   }
   if(!arbre_EstVide(Ar->tright))
   {
    Max_val=max(Max_Non_Ord(Ar->tright),Max_val);
   }

   return((int)Max_val);
}


int min (int h1, int h2) {
	if (h1<h2)
		return h1 ;
	else
       return h2 ;
}

/* calculer le Main d'un arbre Binaire Non Ordonné
  Entreés : Pointeur Ar vers l'arbre Binaire
  Sortie: Le Min de l'arbre
*/
int Min_Non_Ord(tree*Ar)
{
   if (arbre_EstVide(Ar)) return((int)NULL);/* arbre vide n'a pas de Max */
   if (arbre_EstFeuille(Ar)) return ((int)Ar->info);/* l'arbre avec un seule element , donc le max est la racine*/
   //sinon
   int Min_val = Ar->info;

   if(!arbre_EstVide(Ar->tleft))
   {
    Min_val=min(Min_Non_Ord(Ar->tleft),Min_val);
   }
   if(!arbre_EstVide(Ar->tright))
   {
    Min_val=min(Min_Non_Ord(Ar->tright),Min_val);
   }

   return((int)Min_val);
}

/*chercher un element dans une arbre binaire non ord
  Entreés : Pointeur Ar vers l'arbre Binaire , l'element chercher
  Sortie: 1 si l'element rechercher existe

*/
int Rechercher_Non_Ord(tree*Ar,int elm)
{
      if(!Ar) return((int)0);//si l'arbre est vide
      //sinon
      if(Ar->info == elm)
       {
          printf("\n l'element rechercher %d existe\n",elm);
          return((int)1);
       }
      if(Rechercher_Non_Ord(Ar->tleft,elm))
       {
          return((int)1);
       }

     return Rechercher_Non_Ord(Ar->tright,elm);
}


/* Nœud le plus profond dans une arbre binaire non ord
  Entreés : Pointeur Ar vers l'arbre Binaire
  Sortie: Nœud le plus profond de Ar
*/
tree* Deepest_Node(tree* Ar)
{
  if (arbre_EstVide(Ar)) return((tree*)NULL);

  if (arbre_EstFeuille(Ar)) return((tree*)Ar);

    /* chercher Deepest Node Droit*/
    return Deepest_Node(Ar->tright);

}

/**
Supprimer un element dans un arbre binaire non ord
Entreés : Pointeur Ar vers l'arbre Binaire , l'element a supprimer
Sortie: l'arbre apres la suppression
*/
tree* delete_arbre_non_ord(tree*Ar,int elm)
{
   if(arbre_EstVide(Ar)) return((tree*)NULL);
   if(Rechercher_Non_Ord(Ar->tleft,elm))
   {
     Ar->tleft = delete_arbre_non_ord(Ar->tleft,elm);
   }
   else if(Rechercher_Non_Ord(Ar->tright,elm))
   {
     Ar->tright = delete_arbre_non_ord(Ar->tright,elm);
   }
   else /* sinon Ar->info == val */
   {
      if (arbre_EstFeuille(Ar)) return ((tree*)NULL);
      if(Ar->tleft == NULL) /*noeud a un fils unique gauche ou droit */
      {
            tree*tmp = Ar->tright;
            Ar = NULL;
            return((tree*)tmp);
      }
      else if(Ar->tright == NULL)
      {
            tree*tmp = Ar->tleft;
            Ar = NULL;
            return((tree*)tmp);
      }
      /*sinon le noeud Ar a deux enfants , je le remplace par le nœud le plus profond à l'extrême droite*/
        tree* dp = Deepest_Node(Ar);
        Ar->info = dp->info;
        Ar->tright = delete_arbre_non_ord(Ar->tright,dp->info);
   }
    return((tree*)Ar);
}


tree* inserer_gauche(tree*Ar,int elm)
{
   tree*ne;
   ne=arbre_creer_noeud(elm);
   // si l'arbre n'existe pas
   if(!Ar) return((tree*)ne);

   if(arbre_EstFeuille(Ar))
    {
       Ar->tleft=inserer_gauche(Ar->tleft,elm);
    }
  else if(!Ar->tright)
    {
       Ar->tleft=inserer_gauche(Ar->tleft,elm);
    }
  else if(!Ar->tleft)
    {
       Ar->tleft=inserer_gauche(Ar->tleft,elm);
    }
 else
        Ar->tleft=inserer_gauche(Ar->tleft,elm);

  return((tree*)Ar);

}

tree* inserer_droite(tree*Ar,int elm)
{
   tree*ne;
   ne=arbre_creer_noeud(elm);
   // si l'arbre n'existe pas
   if(!Ar) return((tree*)ne);

   if(arbre_EstFeuille(Ar))
    {
       Ar->tright=inserer_droite(Ar->tright,elm);
    }
  else if(!Ar->tright)
    {
       Ar->tright=inserer_droite(Ar->tright,elm);
    }
  else if(!Ar->tleft)
    {
        Ar->tright=inserer_droite(Ar->tright,elm);
    }
 else
         Ar->tright=inserer_droite(Ar->tright,elm);

  return((tree*)Ar);

}

/* ***********************************ORDONNER___*********************************************** */

// insertion d'un element dans une arbres ordonné
tree* inserer_hor(tree*Ar,int elm)
{
   tree*ne;
   ne=arbre_creer_noeud(elm);
   // si l'arbre n'existe pas
   if(!Ar) return((tree*)ne);
   //si non
   else
   {   // si elm est superieur a la valeur de la racine
       if(elm > Ar->info)
        Ar->tright=inserer_hor(Ar->tright,elm);
       // si non
       else
         Ar->tleft=inserer_hor(Ar->tleft,elm);
   }// fin else
    return((tree*)Ar);
}

/*chercher un element dans une arbre binaire ord*/
int rechercher_hor(tree*Ar,int elm)
{
  if(Ar)
   {
       if(Ar->info == elm)
       {
          printf("\n l'element rechercher %d existe\n",elm);
          return((int)1);
       }

       else if(elm < Ar->info)
       {
           return rechercher_hor(Ar->tleft,elm);
       }
       else
          return rechercher_hor(Ar->tright,elm);
   }
   printf("\n l'element rechercher %d n'existe pas\n",elm);
}

/* max d un arbre*/
int Max_ord(tree*Ar)
{
   if (!arbre_EstVide(Ar))
	 {
		if (arbre_EstFeuille(Ar))

		      return((int)Ar->info) ; /* Max est une feuille la plus droit*/
		else
		      /* chercher le Max dans la droit ,Noeud de droit >= Noeud Racine */
		      return Max_ord(Ar->tright);
	 }
    return((int)NULL) ; /* arbre vide n'a pas de Max */
}

/* min d un arbre*/
int Min_ord(tree*Ar)
{
   if (!arbre_EstVide(Ar))
	 {
		if (arbre_EstFeuille(Ar))

		      return((int)Ar->info) ; /* Min est une feuille la plus gauche*/
		else
		      /* chercher le Min dans la gauche ,Noeud de gauche <= Noeud Racine */
		      return Min_ord(Ar->tleft);
	 }
    return((int)NULL) ; /* arbre vide n'a pas de Max */
}

/*calculr le Successeur d'un Noued*/
tree* Successeur(tree* Nd)
{
   if(arbre_EstFeuille(Nd)) return((tree*)Nd);
   return ((tree*)Successeur(Nd->tleft));
}

/*la suppression dans une arbre binaire ord */
tree* delete_arbre(tree*Ar,int val)
{
   if(arbre_EstVide(Ar)) return((tree*)NULL);
   /*si cle est inférieure à la valeur du noeud, rechercher dans le sous-arbre gauche*/
   if(val < Ar->info)
   {
       Ar->tleft = delete_arbre(Ar->tleft,val);
   }
   /* si cle est supérieure à la valeur du noeud, rechercher dans le sous-arbre droit*/
   else if(val > Ar->info)
   {
       Ar->tright = delete_arbre(Ar->tright,val);
   }
   /* sinon Ar->info == val */
   else
   {
      if (arbre_EstFeuille(Ar)) return ((tree*)NULL);
      /*noeud a un fils unique gauche ou droit */
      if(Ar->tleft == NULL)
      {
            tree*tmp = Ar->tright;
            Ar = NULL;
            return((tree*)tmp);
      }
      else if(Ar->tright == NULL)
      {
            tree*tmp = Ar->tleft;
            Ar = NULL;
            return((tree*)tmp);
      }
      /*sinon le noeud Ar a deux enfants*/
        tree* succes = Successeur(Ar->tright);
        /*remplacer la valeur du noeud à supprimer avec la valeur du successeur*/
        Ar->info = succes->info;
        /* supprimer le successeur*/
        Ar->tright = delete_arbre(Ar->tright, succes->info);
   }
     return((tree*)Ar);
}

#endif // ARBRE_H_INCLUDED
