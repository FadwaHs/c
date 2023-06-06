#ifndef Tritab_H_INCLUDED
#define Tritab_H_INCLUDED
#include <stdbool.h>
#define MAX 100


/// tri par  sélection-échange/////

int Indice_Min(Tableau *Tab,int i,int j)
{
    if(!Tab) return ((int)-1);// -1 si la liste n'existe pas
    if(i>j) return((int)-3); // -3 si i > j

    int Min=Tab->tab[i]; // affectation de la premiere valeur
    int ind_Min = i; // affectation du premier indice

    for (int ind = i+1; ind < j+1; ind++) // boucler sur les elements entre i et j
    {
        if(Tab->tab[ind] < Min)  // si elemen en cours de traitement > Max
        {
            Min = Tab->tab[ind]; // affectation de la valeur
            ind_Min = ind;// affectation de l'indice
        }
    }
    return((int)ind_Min); // retourner l'indice du max
}

// Fonction qui echange deux elements(permutation)
int Echanger_Pos(Tableau *Tab,int ind1,int ind2)
{
    if(!Tab) return((int)-1);
    int tmp; // initialiser une variable

    tmp = Tab->tab[ind1]; // stocker l'element du premier indice dans var
    Tab->tab[ind1] = Tab->tab[ind2]; // inserer le 2eme elem a la place du premier
    Tab->tab[ind2] = tmp; // inserer le 1 elem a la place du 2eme
    return((int)1); // 1 si l'echange est bien fait
}

int Trier_Selection(Tableau *Tab)
{
    if(!Tab) return((int)-1);
    for (int ind = 0; ind <Tab->n; ind++)
    {

        Echanger_Pos(Tab,ind,Indice_Min(Tab,ind,Tab->n-1));
    }

    return((int)1);
}


/// tri par INSERTION

int tri_Insertion(Tableau * Tab)
{
   int i,j,tmp;
   for (int i = 0; i <Tab->n; i++)
    {
        //tmp=Tab->tab[i];
        j=i;

        while(j>0 && Tab->tab[j-1]>Tab->tab[j])
        {

         //echange
          tmp=Tab->tab[j];
          Tab->tab[j]=Tab->tab[j-1];
          Tab->tab[j-1]=tmp;

           j--;

        }
        
          aficher_tab(Tab);
          printf("\n");
          printf("\n");
    }

    return 1;
}


/// tri par bulles
int Trier_A_bulles(Tableau* Tab)
{
  if(!Tab) return((int)-1);
  int cmp = Tab->n;

  while(cmp>0)
  {

    for (int i = 0; i <Tab->n-1; i++)
    {
        int j=i+1;
      // echanger sans ajouter un autre element
      if(Tab->tab[i]>Tab->tab[j])
      {
         Tab->tab[j]=Tab->tab[j]+Tab->tab[i];
         Tab->tab[i]=Tab->tab[j]-Tab->tab[i];
         Tab->tab[j]=Tab->tab[j]-Tab->tab[i];
      }
    }
      cmp--;
  }

  return((int)1);
}


///tri rapide
int partition(Tableau *Tab,int d,int f)
{
  int pivot,i,j;

  pivot = Tab->tab[f];
  printf("<%d>",pivot);
  i=d-1;

  for(j=d;j<f;j++)
  {
    if(Tab->tab[j] <= pivot)
    {
        i++;
        Echanger_Pos(Tab,i,j);
    }
  }
  Echanger_Pos(Tab,i+1,j);
  return((int)i+1);

}

void triRapide(Tableau *Tab,int i,int j)
{
    int s;

    if(i<j)
    {
        ///la partition.
        s=partition(Tab,i,j);
         aficher_tab(Tab);
          printf("\n");
           printf("\n");

        /// trier le tableau gauche.
        triRapide(Tab,i,s-1);
        ///trie le tableau droit.
        triRapide(Tab,s+1,j);
        
         
    }
}


/// Extraction algo

int echange(int *a,int *b)
{
   int tmp;

   tmp = *a;
   *a=*b;
   *b=tmp;

 return 1;
}

void construireHeap(Tableau *T,int n, int i)
{
    int indMax=i,
        gche =2*i+1,
        dt=2*i+2;

    /// chercher le max.
    if (gche<n && (T->tab[gche] > T->tab[indMax]))
          indMax=gche;

    if (dt<n && T->tab[dt] > T->tab[indMax])
        indMax = dt;


    if (indMax != i)
    {
        echange(&T->tab[i],&T->tab[indMax]);

        // on construit recursivement.
        construireHeap(T, n, indMax);
    }
}

void heapSort(Tableau *T, int n)
{
    int i,j=n-1;

    ///on construit le heap pour tous les noeuds.
    for (i=(n/2)-1;i>=0;i--)
    {
        //aficher_tab(T);
        construireHeap(T,n,i);
        //aficher_tab(T);
    }
    ///on tri.
    for(i=n-1;i>0;i--)
    {
        //on echange l’indice avec le debut.
        echange(&T->tab[0],&T->tab[i]);
        //on reconstruit le heap.
        construireHeap(T,i,0);
    }
}

#endif // LISTES_H_INCLUDED

