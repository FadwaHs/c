#include<stdio.h>
#include<stdlib.h>
#include<time.h>

double*alloc_tab(int nbr);
void remplir_tab(double*T,int nbr);
void afficher_tab(double*T,int nbr);
void inverser(double*T,int nbr,int i,int j);
void renverser(double*T,int nbr);
int verify (double*T,int nbr);
double *alloc_tabE(int nbr1);
void remplir_tabE(double*E,int nbr);
void cancatenation (double*T,double *E,int nbr);

int main()
{
 double* T;
 int nbr,i=0,j=0,croissant=0;
 printf("entrez le nombre des elements : \n");
 scanf("%d",&nbr);

T=alloc_tab(nbr);
remplir_tab(T,nbr);
afficher_tab(T, nbr);

renverser(T,nbr);// renverser les elements d'un tabelau avec deux methode

croissant = verify (T,nbr); // fonction qui verifier si le tableau est croissant ou bien non
printf("si le tableau croissant return 1 sinon return 0,\n %d\n",croissant);

//creer un autre tableau
double*E;
E=alloc_tabE(nbr);
remplir_tabE(E, nbr);
cancatenation (T,E,nbr);// la concatenation de deux tableau E et T de meme taille
return 0;
}


double*alloc_tab(int nbr)
{
 double*T=NULL;

 T=(double*)calloc(nbr,sizeof(double));

 return T;
}


void remplir_tab(double*T,int nbr){

int i;
for(i=0;i<nbr;i++)
{
 printf("T[%d]=  \n",i);
 scanf("%lf",&T[i]);
}

}

void afficher_tab(double*T,int nbr)
{
   int i;
  for(i=0;i<nbr;i++)
  {
     printf("\n %.2lf\n",T[i]);
  }
 }

 void inverser(double*T,int nbr,int i,int j)
 {

// inverser avec un autre element
  double elm;
  elm=T[i];
  T[i]=T[j];
  T[j]=elm;

// inverser sans ajouter un autre element
  T[j]=T[j]+T[i];
  T[i]=T[j]-T[i];
  T[j]=T[j]-T[i];

 }

void renverser(double*T,int nbr)
 {
 printf("\n***** renverser lordre****\n");

 int i;
 for(i=0;i<nbr/2;i++)
  {
     int j = nbr-1-i;
     T[j]=T[j]+T[i];
     T[i]=T[j]-T[i];
     T[j]=T[j]-T[i];
     //inverser(T, nbr, i, (nbr-1-i));
  }
  afficher_tab(T, nbr);
 }

// void renverser(double*T,int nbr)
// {
//
//   int i,j;
//   printf("\n***** renverser lordre****\n");
//
//   for(i=0,j=nbr-1; i<nbr,j<nbr;i++,j--)
//   {
//     inverser(T,nbr,i,j);
//   }
//
// afficher_tab(T, nbr);
// }

int verify (double*T,int nbr)
{
  int i,croissant=0;

  for (i=0;i<nbr-1;i++){
   if(T[i]<T[i+1]) //comparaison des elements
   {
     croissant=1;
   }
  else
   croissant =0;
  }

return croissant;


}

double *alloc_tabE(int nbr)
{

 double*E=NULL;

 E=(double*)calloc(nbr,sizeof(double));

 return E;
}

 void remplir_tabE(double*E,int nbr){

 int j;
 printf("******le 2eme tableau******\n");
  for(j=0;j<nbr;j++)
  {
    printf("E[%d]= \n",j);
    scanf("%lf",&E[j]);
  }

   for(j=0;j<nbr;j++)
   printf("\n%.2lf\n",E[j]);
}

void cancatenation (double*T,double *E,int nbr)
{

 double*tabc;

 tabc=(double*)calloc(nbr,sizeof(double));

  int i,j;
  printf("\*****concatenation*****\n");

  for(i=0,j=0;i<nbr,j<nbr;i++,j++){

    tabc[i]=T[i]+E[j];

    printf("%.2lf\n",tabc[i]);
  }
}













