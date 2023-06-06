#ifndef Trilist_H_INCLUDED
#define Trilist_H_INCLUDED
#include <stdlib.h>
#include<stdio.h>

typedef struct celldouble
{
    int val;
    struct cell *suiv;
    struct cell *prec;

}DCellule;



DCellule *CreerDCellule(int donnee)
{
    DCellule *Ne;
    Ne = (DCellule*)malloc(sizeof(DCellule));
    if(!Ne)
    {
        printf("Erreur d'allocation");
        return (NULL);
    }
    Ne->val=donnee;
    Ne->suiv=NULL;
    Ne->prec=NULL;
    return((DCellule*)Ne);
}


DCellule *InsererTetePListeDouble(DCellule *Pliste , int Elem)
{
    DCellule *NE;
    NE = (DCellule*)CreerDCellule(Elem);

    NE->suiv= Pliste;
   	if(Pliste) Pliste->prec = NE;
    return ((DCellule*)NE);
}


int affichePListeDouble(DCellule *Pliste)
{
    DCellule *ptc;
    if(!Pliste)
    {
        printf("\Erreur : liste n'existe pas");
        return((int)-1);
    }
    while(Pliste)
    {
    	printf("\t %d", Pliste->val);
		Pliste=Pliste->suiv;
	}
    return((int)1);
}

int TaillePListe_double(DCellule * Pliste)
{

    DCellule *ptc;
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


/// tri par selection
DCellule* min_liste_double(DCellule *liste)
{

   if(!liste)
   {
        printf("\nListe n existe pas");
        return((int)-1);
   }

   DCellule *tmp = liste; //head
   DCellule* min=liste;

   while(tmp != NULL)
   {
     if(tmp->val < min->val)
     {
        min = tmp;
     }
     tmp=tmp->suiv;
   }

  return((DCellule*)min);
}

int Trier_Selection_liste(DCellule *liste)
{
    if(!liste) return((int)-1);

     DCellule *crt;
     DCellule *min = NULL;
     int tmp;

    for(crt=liste;crt;crt=crt->suiv)
    {

        min=min_liste_double(crt);

        if(min!=crt)
        {
            tmp=min->val;
            min->val=crt->val;
            crt->val=tmp;
        }

        affichePListeDouble(liste);
        printf("\n");

    }

    return((int)1);
}


/// tri par Insertion
int tri_Insertion_liste(DCellule *Pliste)
{
   int tmp;
   DCellule *crt1,*crt2;

   for (crt1=Pliste->suiv;crt1;crt1=crt1->suiv)
    {

        crt2=crt1;
        while(crt2->prec->val > crt2->val)
        {
         //echange
          tmp=crt2->val;
          crt2->val=crt2->prec->val;
          crt2->prec->val=tmp;

          crt2=crt2->prec;
          if(!crt2->prec)  break;

        }
       affichePListeDouble(Pliste);
        printf("\n");
    }

    return 1;
}

///tri a bulles

int Trier_A_bulles_liste(DCellule *liste)
{
  if(!liste) return((int)-1);

  int cmp = TaillePListe_double(liste);

  while(cmp>0)
  {


    DCellule *crt;
    DCellule * crt2;

    int tmp;

    for (crt=liste;crt->suiv;crt=crt->suiv)
    {
        crt2 = crt->suiv;
      // echanger
      if(crt->val > crt2->val)
      {
         tmp=crt->val;
         crt->val = crt2->val;
         crt2->val=tmp;
      }
    }
      cmp--;

     affichePListeDouble(liste);
     printf("\n");
  }

  return((int)1);
}


/// tri Rapide
DCellule * partition_liste(DCellule*tete, DCellule*queue, int pivot)
{
    int trier = 1;
    int tmp;
    DCellule*gauche = tete, *droit = queue;
    while (gauche != droit)
    {
        while (gauche->val < pivot) gauche = gauche->suiv;
        while ((droit->val >= pivot) && (droit != gauche)) droit = droit->prec;
        if (gauche != droit)
        {
            //echange(gauche,droit);
             tmp=gauche->val;
             gauche->val=droit->val;
             droit->val=tmp;

            trier = 0;
        }

    }
    if (trier == 1)return((DCellule*)tete->suiv);
    return((DCellule*)gauche);
}


void triRapide_liste(DCellule*tete, DCellule*queue)
{
    DCellule*ptcrt;
    int pivot;
    if (tete != queue)
    {
        if (tete->val < tete->suiv->val)

          pivot = tete->suiv->val;

        else
          pivot = tete->val;

        ptcrt = partition_liste(tete, queue, pivot);

        triRapide_liste(tete, ptcrt->prec);
        triRapide_liste(ptcrt, queue);


    }
}

#endif // LISTES_H_INCLUDED
