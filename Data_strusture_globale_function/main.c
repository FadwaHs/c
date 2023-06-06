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

#include "tritab.h"
#include "trilist.h"


//liste
Cellule* transferer_arbre_liste(tree* Ar,Cellule*L2)
{
   if(!Ar) return((Cellule*)NULL);

      L2=InsererFin(L2,Ar->info);
      transferer_arbre_liste(Ar->tright,L2);
      transferer_arbre_liste(Ar->tleft,L2);

     return((Cellule*)L2);
}


//PIle
PPile* tansfermer_Tab_pile(Tableau*Tab)
{
   if(!Tab) return((PPile*)NULL);
   int ind=0;
  PPile *pile=NULL;

  while(ind!=Tab->n)
  {
     pile=PP_Empiler(pile,Tab->tab[ind]);
     ind++;
  }
  return((PPile*)pile);
}

//file
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
     EnfilerPFile(file,pile->val);
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



int main()
{


   Tableau *Tab = Creer_Tableau();
   insert_elmnt_Queue(Tab,1);
   insert_elmnt_Queue(Tab,6);
   insert_elmnt_Queue(Tab,9);
   insert_elmnt_Queue(Tab,8);
   insert_elmnt_Queue(Tab,2);
   insert_elmnt_Queue(Tab,4);
   insert_elmnt_Queue(Tab,10);
   insert_elmnt_Queue(Tab,2);
   insert_elmnt_Queue(Tab,15);
   insert_elmnt_Queue(Tab,8);
   insert_elmnt_Queue(Tab,3);
   insert_elmnt_Queue(Tab,20);

   printf("a : Le resultat de Tableau : \n");
   aficher_tab(Tab);
   printf("\n");

    printf("\n trier par le tri par insertion :\n");
    tri_Insertion(Tab);
      printf("\n");



   Tableau *Tab2 = Creer_Tableau();
   insert_elmnt_Queue(Tab2,1);
   insert_elmnt_Queue(Tab2,6);
   insert_elmnt_Queue(Tab2,9);
   insert_elmnt_Queue(Tab2,8);
   insert_elmnt_Queue(Tab2,2);
   insert_elmnt_Queue(Tab2,4);
   insert_elmnt_Queue(Tab2,10);
   insert_elmnt_Queue(Tab2,2);
   insert_elmnt_Queue(Tab2,15);
   insert_elmnt_Queue(Tab2,8);
   insert_elmnt_Queue(Tab2,3);
   insert_elmnt_Queue(Tab2,20);

     printf("\n liste trier par le tri rapide :\n");
     int f=Tab2->n-1;
     triRapide(Tab2,0,f);






// DCellule * p_list= NULL;
//
// p_list=InsererTetePListeDouble(p_list , 0);
// p_list=InsererTetePListeDouble(p_list , 3);
// p_list=InsererTetePListeDouble(p_list , 1);
// p_list=InsererTetePListeDouble(p_list , 10);
// p_list=InsererTetePListeDouble(p_list , 4);
// p_list=InsererTetePListeDouble(p_list , 8);
//
// printf("\n Avant le tri :\n");
// affichePListeDouble(p_list);
// ///selection echange
// printf("\nle tri par sélection-échange :\n");
// Trier_Selection_liste(p_list);
// printf("\n");


//   delete_elmnt(Tab,3);
//   delete_elmnt(Tab,0);
//   delete_Queue(Tab);
//
//   printf("b: Le resultat de Tableau apres la suppression des valeurs :\n");
//   aficher_tab(Tab);
//   printf("\n");
//
//    printf("\nb:le tabelau apres les insertions:\n");
//
//    insert_elmnt_Debut(Tab,5);
//    insert_elmnt_Queue(Tab,-15);
//    insert_elmnt_position(Tab,6,-5);
//    aficher_tab(Tab);
//    printf("\n");
//
//    //PPile* tansfermer_Tab_pile(Tableau*Tab)
//    printf("\nTraintement pile:\n");
//    printf("\ntransferer le tableau vers une pile:");
//    PPile* pile=tansfermer_Tab_pile(Tab);
//    PP_Afficher_PPile(pile);
//    printf("\n");
//
//    //delete pile
//    pile = PP_Depiler(pile);
//    PP_Afficher_PPile(pile);
//    printf("\n");
//    pile =  PP_Depiler_Elem_Pos(pile, 1);
//    PP_Afficher_PPile(pile);
//    printf("\n");
//    pile =  PP_Depiler_Elem_Pos(pile, 4);
//    PP_Afficher_PPile(pile);
//    printf("\n");
//
//    //insert_pile
//
//    printf("\nLa pile apres empiler -2 :");
//    pile = PP_Empiler(pile,-2);
//    PP_Afficher_PPile(pile);
//    printf("\n");
//
//    printf("\nLa pile apres empiler 22 a la position: 5");
//    pile = PP_Empiler_Elem_Pos(pile, 5, 22);
//    PP_Afficher_PPile(pile);
//    printf("\n");
//
//    printf("\nLa pile apres empiler 33 a la fin");
//    pile = PP_Empiler_Elem_Pos(pile, 1, 33);
//    PP_Afficher_PPile(pile);
//    printf("\n");
//
//
//    printf("\nTraintement File:\n");
//    //PFile* transferer_pile_file(PPile*pile)
//    printf("\ntransferer la pile vers une file:");
//    PFile* file=transferer_pile_file(pile);
//    AffichePFile(file);
//    printf("\n");
//
//    //defiler
//    printf("\nla file apres defiler:");
//    DefilerPFile(file);
//	AffichePFile(file);
//	 printf("\n");
//
//    //defiler
//    printf("\nla file apres enfiler -22:");
//    EnfilerPFile(file,-22);
//	AffichePFile(file);
//	printf("\n");
//
//    //tree* transferer_file_arbre_ord(PFile*file)
//    tree*Ar =transferer_file_arbre_ord(file);
//    printf("\naffichage en largeur de l'arbre :\n");
//    ParcoursLargeur(Ar);
//
//    printf("\n");
//    printf("\n affichage prefixé : \n");
//    prefix(Ar);
//    printf("\n affichage infixé : \n");
//    infix(Ar);
//    printf("\n affichage postfixé :\n");
//    posfix(Ar);
//
//    //delete arbre
//    printf("\n l'arbre apres la suppression de 9:\n");
//    delete_arbre(Ar,9);
//    infix(Ar);
//    printf("\n");
//    ParcoursLargeur(Ar);
//    printf("\n");
//
//
//    //delete arbre
////    printf("\n l'arbre apres la suppression de 9:\n");
////    delete_arbre(Ar,15);
////    infix(Ar);
////    printf("\n");
//
//    //Cellule* transferer_arbre_liste(tree* Ar,Cellule*L2)
//    printf("\n traitement des listes:\n");
//    Cellule *L2=NULL;
//    L2=transferer_arbre_liste(Ar,L2);
//    affichePListe(L2);
//    printf("\n");
//
//     printf("\n delete 1er element:\n");
//     L2=SupprimerTetePListe(L2);
//     affichePListe(L2);
//
//     printf("\n delete dernier element:\n");
//     L2=SupprimerQueuPListe(L2);
//     affichePListe(L2);
//
//     printf("\n delete le 5eme element:\n");
//     L2=SupprimerPosPListe(L2,5);
//     affichePListe(L2);


    return 0 ;
}
