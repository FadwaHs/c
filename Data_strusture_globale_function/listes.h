#ifndef LISTES_H_INCLUDED
#define LISTES_H_INCLUDED

/** ****************** LISTES pointeur  ****************** **/
typedef struct cel
{
    int val;
    struct cel *suiv;
}Cellule;

/*******************************************************POINTEUR****************************************************************/
/*Fonction:CreerCellule
Entrée:donnee
Sorties:un pointeur sur la cellule créée
Description:Cette fonction permet la création d'une cellule et la retourner
*/
Cellule *CreerCellule(int donnee)
{
    Cellule *Ne;
    Ne = (Cellule*)malloc(sizeof(Cellule));
    if(!Ne)
    {
        printf("Erreur d'allocation");
        return (NULL);
    }
    Ne->val=donnee;
    Ne->suiv=NULL;
    return((Cellule*)Ne);
}

/*Fonction:TaillePListe
Entrée:Liste
Sorties:-1 si la liste n'existe pas sinon le nombre des elements de la liste
Description:Cette fonction retourne le nombre des elements de la liste
*/
int TaillePListe(Cellule *Pliste)
{
    Cellule *ptc;
    int ind=0;
    if(!Pliste) return((int)-1); //existance de la liste
    ptc = Pliste;
    while(ptc)
    {
        ind++;
        ptc=ptc->suiv;
    }
    return ((int)ind);
}

/*Fonction:InsererTetePListe
Entrée:liste , element
Sorties:la liste apres insertion de la cellule
Description:Cette fonction insère dans en tete de la liste une nouvelle cellule
*/
Cellule *InsererTetePListe(Cellule *Pliste , int Elem)
{
    Cellule *NE;
    NE = (Cellule*)CreerCellule(Elem);
    NE->suiv= Pliste;
    return ((Cellule*)NE);
}

Cellule *InsererFin(Cellule *Pliste ,int Elem)
{
    Cellule *NE,*temp;
    NE = (Cellule*)CreerCellule(Elem);
    if(!Pliste) return ((Cellule*)NE);

    temp = Pliste;
    while(temp->suiv != NULL)
    {
       temp=temp->suiv;
    }
    temp->suiv=NE;
    return((Cellule*)Pliste);

}
Cellule *InsererApresVal(Cellule *Pliste ,int Elem,int valeur)
{
    Cellule *NE,*temp;
    NE = (Cellule*)CreerCellule(Elem);

    if(!Pliste) return ((Cellule*)NULL);
    temp=Pliste;
    while(temp->val != valeur && temp->suiv!=NULL)
    {
        temp=temp->suiv;
    }
    if(temp->val==valeur)
    {
        NE->suiv = temp->suiv;
        temp->suiv=NE;
        return((Cellule*)Pliste);
    }
    printf("\nValeur non trouvee");
    return((Cellule*)Pliste);
}

/*Fonction:InsererPosPListe
Entrée:liste , position, element
Sorties:NULL si la liste n'existe pas ou la position est non valide sinon la liste apres insertion
si l'insertion est bien passée
Description:Cette fonction insère dans la position indiquée d'une liste une nouvelle cellule
*/
Cellule *InsererPosPListe(Cellule *Pliste , int Elem , int pos)
{
    Cellule *ptc, *NE;
    int cmp;
    //insertion en tete de la liste
    if(pos ==1 )
        return ((Cellule*)InsererTetePListe(Pliste,Elem));
    NE=NULL;
    //Liste n'existe pas
    if(!Pliste)
    {
        printf("\nERREUR : Liste n'existe pas .");
        return((Cellule*)NULL);
    }
    //Position non valide
    if((pos<1) || (pos > (TaillePListe(Pliste)+1)))
    {

        printf("\nERREUR : Position non valide .");
        return((Cellule*)Pliste);
    }
    cmp=1;
    ptc = Pliste;
    while(cmp<pos-1)
    {
        ptc = ptc->suiv;
        cmp++;
    }
    NE = (Cellule*)CreerCellule(Elem);
    NE->suiv =ptc->suiv;
    ptc->suiv = NE;
    return ((Cellule*)Pliste);
}

/*Fonction:affichePListe
Entrée:liste
Sorties:affichage des element de la liste ou bien message d'erreur
Description:Cette fonction affiche tous les elements de la liste
*/
int affichePListe(Cellule *Pliste)
{
    Cellule *ptc;
    if(!Pliste)
    {
        printf("\Erreur : liste n'existe pas");
        return((int)-1);
    }
    ptc=Pliste;
    printf("\n");
    while(ptc)
    {
        printf("%d ->",ptc->val);
        ptc=ptc->suiv;
    }
    return((int)1);
}

/*Fonction:SupprimerTetePListe
Entrée:liste
Sorties:NULL si la liste n'existe pas, sinon la liste apres suppression
Description:Cette fonction supprime une cellule de la tete de la liste
*/
Cellule *SupprimerTetePListe(Cellule *Pliste)
{
    Cellule *ptc;
    //Liste n'existe pas
    if(!Pliste)
    {
        printf("\nERREUR : Liste n'existe pas .");
        return((Cellule*)NULL);
    }
    ptc = Pliste->suiv;
    free(Pliste);
    return ((Cellule*)ptc);
}

/*Fonction:SupprimerQueuPListe
Entrée:liste
Sorties:NULL si la liste n'existe pas, sinon la liste apres suppression
Description:Cette fonction supprime une cellule de la queu de la liste
*/
Cellule *SupprimerQueuPListe(Cellule *Pliste)
{
    Cellule *ptc , *ptcc;
    //Liste n'existe pas
    if(!Pliste)
    {
        printf("\nERREUR : Liste n'existe pas .");
        return((Cellule*)NULL);
    }
    //la liste contient un seul element
    if(!Pliste->suiv)
    {
        free(Pliste);
        return((Cellule*)NULL);
    }
    ptc = Pliste;
    ptcc = Pliste;
    while(ptc->suiv)
    {
        ptcc=ptc;
        ptc=ptc->suiv;
    }
    ptcc->suiv=NULL;
    free(ptc);
    return ((Cellule*)Pliste);
}

/*Fonction:SupprimerPosPListe
Entrée:liste , position
Sorties:NULL si la liste n'existe pas, sinon la liste apres suppression
Description:Cette fonction supprime une cellule de la position indiquée de la liste
*/
Cellule *SupprimerPosPListe(Cellule *PListe , int pos)
{
    if(!PListe) return ((Cellule*)NULL);
    Cellule *temp;
    if(pos<=0 || pos>TaillePListe(PListe))
    {
        printf("\nPosition non valide");
        return ((Cellule*)PListe); //supprimer erronee
    }
    if(pos==1)
    {
        PListe=SupprimerTetePListe(PListe);
        return ((Cellule*)PListe);
    }
    if(pos==TaillePListe(PListe))
    {
        PListe=SupprimerQueuPListe(PListe);
        return ((Cellule*)PListe);  //supprimer a la fin
    }
    else
    {

    int compteur=2;
    temp=PListe;
    while(compteur<pos)
    {
        compteur++;
        temp=temp->suiv;
    }
    temp->suiv=temp->suiv->suiv;
    //free(temp->suiv);
    return ((Cellule*)PListe);
    }
}

/*Fonction:SupprimerElemPListe
Entrée:liste , element
Sorties:NULL si la liste n'existe pas, sinon la liste apres suppression
Description:Cette fonction supprime une cellule indiquée de la liste
*/
Cellule *SupprimerElemPListe(Cellule *Pliste , int Elem)
{
    Cellule *ptc;
    int cmp=1;
    //Liste n'existe pas
    if(!Pliste)
    {
        printf("\nERREUR : Liste n'existe pas .");
        return((Cellule*)NULL);
    }
    ptc=Pliste;
    while((ptc->suiv)&&(ptc->val!=Elem))
    {
        cmp++;
        ptc=ptc->suiv;
    }
    if(ptc->val==Elem)
    {
         return ((Cellule*)SupprimerPosPListe(Pliste,cmp));
    }
    else
    {
        printf("\nPosition non valide");
        return((Cellule*)Pliste);
    }


}

int NbrOccurences(Cellule *Pliste,int valeur)
{
   Cellule *TMP=Pliste;
   int nbr=0;
    if(!Pliste)
    {
        printf("\nListe n existe pas");
        return((int)-1);
    }
   while(TMP != NULL)
   {
      if(TMP->val== valeur)
      {
        nbr++;
      }

    TMP= TMP->suiv;
   }
   return ((int)nbr);
}
Cellule *Supprimer_Occurence(Cellule *Pliste,int Elem)
{
    if(!Pliste)
    {
        printf("\nERREUR : Liste n'existe pas .");
        return((Cellule*)NULL);
    }
    else
    {
        int i;
        int nbr=NbrOccurences(Pliste,Elem);
        for(i=0;i<nbr;i++)
        {
            Pliste=SupprimerElemPListe(Pliste,Elem);
        }
        return((Cellule*)Pliste);
    }
}
/*Fonction:insererordrePListeTrie
Entrée:liste , element
Sorties:Nouvel element si la liste est vide sinon la liste apres insertion
Description:Cette fonction insere un element dans une liste triée et le positionne bien
dans son ordre*/
Cellule *insererordrePListeTrie(Cellule *liste , int elem)
{
    Cellule *Ne,*ptc;
    Ne=CreerCellule(elem);
    if(!liste) return ((Cellule*)Ne);
    if(elem<liste->val)
    {
        Ne->suiv=liste;
        liste=Ne;
        return ((Cellule*)liste);
    }
    ptc=liste;
    while(ptc->suiv)
    {
        if(elem<ptc->suiv->val) break;
        ptc=ptc->suiv;
    }
    Ne->suiv=ptc->suiv;
    ptc->suiv=Ne;
    //liste=ptc;
    return ((Cellule*)liste);
}
int RechercherElement(Cellule *liste,int valeur)
{
   if(!liste)
   {
        printf("\nListe n existe pas");
        return((int)-1);
   }
    Cellule *temp;
    temp=liste;
    int pos=0;
    while(temp!= NULL)
    {
      if(temp->val==valeur)
      {
            pos++;
            return((int)pos);
      }
      else
      {
        pos++;
        temp=temp->suiv;
      }
   }
   return ((int)-2);
}

int rechercher_element_ind(Cellule *liste,int ind)
{
   if(!liste)
   {
        printf("\nListe n existe pas");
        return((int)-1);
   }

   Cellule *temp;
   temp=liste;
   int i=1;
   while(temp->suiv != NULL && i != ind)
   {
      i++;
      temp=temp->suiv;
   }
   if(i==ind)
   {
      return((int)temp->val);
   }
   return ((int)0);
}





int max_liste(Cellule *liste)
{
   if(!liste)
   {
        printf("\nListe n existe pas");
        return((int)-1);
   }

   Cellule *tmp= liste; //head
   int Max =tmp->val;
   while(tmp != NULL)
   {
     if(tmp->val > Max)
     {
        Max = tmp->val;
     }
     tmp=tmp->suiv;
   }

   return((int)Max);
}
int min_liste(Cellule *liste)
{

   if(!liste)
   {
        printf("\nListe n existe pas");
        return((int)-1);
   }

   Cellule *tmp = liste; //head
   int min=tmp->val;
   while(tmp != NULL)
   {
     if(tmp->val < min)
     {
        min = tmp->val;
     }
     tmp=tmp->suiv;
   }

   return((int)min);
}
//calculer la moyenne de la liste
int moyenne_liste(Cellule *liste)
{
  if(!liste)
   {
        printf("\nListe n existe pas");
        return((int)-1);
   }

    Cellule *tmp = liste;
    int somme =0;
    int nbrElement=0;
    int moyenneliste;

   while(tmp != NULL)
    {
     //calcule la somme des element
     somme += tmp->val;
     //calcul le nbr des element
     nbrElement++;
     tmp=tmp->suiv;
    }
    if (nbrElement != 0)
   {
    //calculer la moyenne
     moyenneliste = somme/nbrElement;
   }
  return ((int)moyenneliste);
}
int sommeListe(Cellule *liste)
{
  if(!liste)
   {
        printf("\nListe n existe pas");
        return((int)-1);
   }

    Cellule *tmp = liste;
    int somme =0;
   while(tmp != NULL)
    {
     //calcule la somme des element
     somme += tmp->val;
     tmp=tmp->suiv;
    }

  return ((int)somme);
}
Cellule * fusionnerPListe(Cellule *l1 , Cellule *l2)
{
    Cellule *tmp , *liste;
    tmp = NULL ; liste=NULL;
    if(!l1) return((Cellule*)l2);
    if(!l2) return((Cellule*)l1);

    while(l1 && l2)
    {
        tmp = l1;
        l1 = l1->suiv;
        tmp->suiv=liste;
        liste=tmp;
        tmp = l2;
        l2 = l2->suiv;
        tmp->suiv=liste;
        liste=tmp;
    }
    while(l1)
    {
        tmp = l1;
        l1 = l1->suiv;
        tmp->suiv=liste;
        liste=tmp;
    }
    while(l2)
    {
        tmp = l2;
        l2= l2->suiv;
        tmp->suiv=liste;
        liste=tmp;
    }
    return ((Cellule*)liste);
}

Cellule * renverser_liste(Cellule*liste)
{
  if(!liste)
   {
        printf("\nListe n existe pas");
        return((Cellule *)-1);
   }

  Cellule * tmp = liste;// define head
  Cellule * l3= NULL; //la creation d'une liste vide

   while(tmp != NULL)
   {
      l3=InsererTetePListe(l3,tmp->val);//insertion au debut
      tmp=tmp->suiv;
   }

   return ((Cellule*)l3);
}



#endif // LISTES_H_INCLUDED
