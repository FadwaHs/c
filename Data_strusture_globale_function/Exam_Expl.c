#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

#include "Tabl.h"
#include "listes.h"
#include "piles.h"
#include  "files.h"
#include "filestab.h"
#include  "arbre.h"


Cellule* tansfermer_table_liste(Tableau*Tab)
{
   if(!Tab) return((Cellule*)NULL);
   Cellule *L=NULL;
   int ind=0;
//   for(int i=0;i<23;i++)
//   {
//      L=InsererFin(L,Tab->tab[i]);
//   }
  while(ind!=Tab->n)
  {
    L=InsererFin(L,Tab->tab[ind]);
    ind++;
  }
  return((Cellule*)L);
}


PPile* tansfermer_liste_pile(Cellule * L)
{
   if(!L) return((PPile*)NULL);
   Cellule*tmp=L;
   PPile *pile=NULL;
   while(tmp)
   {
      pile=PP_Empiler(pile,tmp->val);
      tmp=tmp->suiv;
   }

  return((PPile*)pile);
}

PFile* transferer_pile_file(PPile*pile)
{
   if(!pile) return((PFile*)NULL);
   //creer file vide
   PFile*file=NULL;
   file = CreerPFile();
   //parcoure de la pile avec le principe des piles
   int ind=PP_Taille_PPile(pile);
   while(ind>0)
   {
     //remplire la file
     EnfilerOrdreFile(file,pile->val);
     pile=PP_Depiler(pile);
     ind--;
   }

   return((PFile*)file);
}


tree* transferer_file_arbre_ord(PFile*file)
{
   if(!file) return((tree*)NULL);

   int indice1 =TaillePFile(file);
   tree*Ar=NULL;
   while(indice1>0)
   {

     Ar=inserer_hor(Ar,file->tete->val);
     DefilerPFile(file);
     indice1--;

   }
  return((tree*)Ar);
}

Tableau* transferer_arbre_tab(tree* Ar)
{
   Tableau* Tab2=Creer_Tableau();
   if(!Ar) return((Tableau*)NULL);
   if(Ar)
   {
       TableauBonPlace(Tab2,Ar->info);
       transferer_arbre_tab(Ar->tleft);
       transferer_arbre_tab(Ar->tright);

   }
     return((Tableau*)Tab2);
}

Cellule* transferer_arbre_liste(tree* Ar,Cellule*L2)
{
   if(!Ar) return((Cellule*)NULL);

       transferer_arbre_liste(Ar->tleft,L2);
       L2=InsererFin(L2,Ar->info);
      transferer_arbre_liste(Ar->tright,L2);
      

     return((Cellule*)L2);
}

tree* transferer_arbre_arbreOR(tree* Ar2,tree*Arord)
{
   if(Ar2)
   {
     Arord = inserer_hor(Arord,Ar2->info);
     transferer_arbre_arbreOR(Ar2->tright,Arord);
     transferer_arbre_arbreOR(Ar2->tleft,Arord);

   }
   return((tree*)Arord);
}


int main()
{
    Tableau *Tab = Creer_Tableau();


    insert_elmnt_Queue(Tab,9);
    insert_elmnt_Queue(Tab,4);
    insert_elmnt_Queue(Tab,18);
    insert_elmnt_Queue(Tab,5);
    insert_elmnt_Queue(Tab,12);
    insert_elmnt_Queue(Tab,6);
    insert_elmnt_Queue(Tab,10);
    insert_elmnt_Queue(Tab,7);
    insert_elmnt_Queue(Tab,14);
    insert_elmnt_Queue(Tab,8);
    insert_elmnt_Queue(Tab,11);
    insert_elmnt_Queue(Tab,0);
    insert_elmnt_Queue(Tab,15);
    insert_elmnt_Queue(Tab,-1);
    insert_elmnt_Queue(Tab,22);
    insert_elmnt_Queue(Tab,3);
    insert_elmnt_Queue(Tab,19);
    insert_elmnt_Queue(Tab,1);
    insert_elmnt_Queue(Tab,23);
    insert_elmnt_Queue(Tab,2);
    insert_elmnt_Queue(Tab,17);
    insert_elmnt_Queue(Tab,20);
    insert_elmnt_Queue(Tab,21);

    aficher_tab(Tab);
    printf("\n");

    delete_elmnt(Tab,11);
    delete_elmnt(Tab,0);
    delete_Queue(Tab);

    printf("\nQ2:le tabelau apres les supressions : fin debut milieu\n");
    aficher_tab(Tab);
    printf("\n");

    printf("\nQ3:le tabelau apres les insertion:\n");
    insert_elmnt_Debut(Tab,10);
    insert_elmnt_Queue(Tab,-3);
    aficher_tab(Tab);
    printf("\n");

    printf("\nQ4:transformer les element de tabelau au liste:\n");
    //Cellule* tansfermer_table_liste(Tableau*Tab)
    Cellule* L =tansfermer_table_liste(Tab);
    affichePListe(L);
    printf("\n");

    printf("\nQ5:\n");
    L=InsererTetePListe(L,15);
    L=InsererTetePListe(L,-1);
    L=InsererFin(L,15);
    L=InsererFin(L,-1);

    affichePListe(L);
    printf("\n");

    printf("\nQ6:\n");
    L=Supprimer_Occurence(L,10);
    affichePListe(L);
    printf("\n");

     printf("\nQ7:\n");
    //PPile* tansfermer_liste_pile(Cellule * L)
    PPile*pile=tansfermer_liste_pile(L);
    PP_Afficher_PPile(pile);
    printf("\n");


    printf("\nLa pile apres empiler 7 a la position: 6");
    pile = PP_Empiler_Elem_Pos(pile, 6, 7);
    PP_Afficher_PPile(pile);
    printf("\n");

    printf("\nApres delete -1 occurence la pile: ");
    pile = PP_Supp_Occ(pile,-1);
    PP_Afficher_PPile(pile);
    printf("\n");


   //PFile* transferer_pile_file(PPile*pile)
   printf("\ntransferer la pile vers une file:");
   PFile* file=transferer_pile_file(pile);
   AffichePFile(file);
   printf("\n");


   SupprimerOccurenceFile(file,7);
   AffichePFile(file);
   printf("\n");

   //tree* transferer_file_arbre_ord(PFile*file)
    tree*Ar =transferer_file_arbre_ord(file);
    printf("affichage infixe de l'arbre :\n");
    infix(Ar);
    printf("\n");
    printf("affichage en largeur de l'arbre :\n");
    ParcoursLargeur(Ar);
    printf("\n");

    printf("l'arbre apres la suppression de 4:\n");
    delete_arbre(Ar,4);
    infix(Ar);
    printf("\n");

    //Tableau* transferer_arbre_tab(tree* Ar)
    printf("le tabelau avec les element de larbre:\n");
    Tableau* Tab2=transferer_arbre_tab(Ar);
    aficher_tab(Tab2);
    printf("\n");

    //Cellule* transferer_arbre_liste(tree* Ar)
    Cellule *L2=NULL;
    L2=transferer_arbre_liste(Ar,L2);
    affichePListe(L2);
     printf("\n");



    return 0 ;
}

