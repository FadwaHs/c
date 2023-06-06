#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int NBL=4,NBC=4;
//les prototype des fonctions
int**alloc_tab2D(int,int);
void init_tab2D(int**,int,int );
void aff_tabl2d(int**,int,int);
int som_tabl(int**,int,int);
int pgelm_tabl(int**,int,int);
void ppg_tabl(int**,int,int,int*vpgn,int*vppgn);
int occ_x_tabl(int**,int,int,int x);
void sompn_tabl(int**,int,int);
void nbp_tabl(int**,int,int);
int sup_moy(int**,int,int);

int main()
  {
      int **t,NBL=4,NBC=4,vpgn,vppgn,x;

      t = alloc_tab2D(NBL,NBC);//faire une allocation dynamique d'un tabelau de 2D , la fonction return @tableau
      init_tab2D(t,NBL,NBC);// remplire le tabelau avec random (aleatoir)
      aff_tabl2d(t,NBL,NBC);// afficher le tabelau

      printf("\n\t la somme est :%d",som_tabl(t,NBL,NBC));//calculer la somme
      printf("\n\t le plus grand nombre est :%d",pgelm_tabl(t,NBL,NBC));
      ppg_tabl(t,NBL,NBC,&vpgn,&vppgn);
      printf("\n\t le plus grand nbr est %d et sa position est :%d",vpgn,vppgn);

      printf("\n\t tenter un nombre x :");
      scanf("%d",&x);
      printf("\n\t le nombres des occurances est :%d",occ_x_tabl(t,NBL,NBC,x)); // calcule occurence d'un nombre dans le tableau 2D

      sompn_tabl(t,NBL,NBC);
      nbp_tabl(t,NBL,NBC);
      printf("\n\t les sup du moyenne est :%d",sup_moy(t,NBL,NBC));

    return 0;


  }


int**alloc_tab2D(int NBL,int NBC)
{
  int **p,i;
  p=(int**)calloc(NBL,sizeof(int*));
  for (i=0;i<NBL;i++)
    p[i]=(int*)calloc(NBC,sizeof(int));
    init_tab2D(p,NBL,NBC);
    return p;
  }

void init_tab2D(int**tableau,int NBL,int NBC)
{
  int i,j;
  srand(time(NULL));
 for (i=0;i<NBL;i++)
   for(j=0;j<NBC;j++)
     tableau[i][j]=(rand()%2?1:-1)*rand()%21;

}

void aff_tabl2d(int**tableau,int NBL,int NBC)
{
  int i,j;
  for (i=0;i<NBL;i++)
 {   printf("\n\t |");
     for(j=0;j<NBC;j++)
       printf("%d\t",tableau[i][j]);
       printf(" | \n");
  }


 }

int som_tabl(int**tableau,int NBL,int NBC)
  {
     int i,j,somme=0;
       for (i=0;i<NBL;i++)
       {  for(j=0;j<NBC;j++)
             somme += tableau[i][j];
       }
         return somme;
  }


int pgelm_tabl(int**tableau,int NBL,int NBC)
{
  int i,j,pgn=tableau[0][0];// faire une prédiction de le plus grand element

  for (i=0;i<NBL;i++)
  { for(j=0;j<NBC;j++)
      if(tableau[i][j]>pgn)
         pgn=tableau[i][j];
  }

 return pgn;
}

void ppg_tabl(int**tableau,int NBL,int NBC,int*vpgn,int*vppgn)
{
    int i,j,pgn=tableau[0][0],ppg=0; //faire une prédiction

  for (i=0;i<NBL;i++)
    for(j=0;j<NBC;j++)
    { if(tableau[i][j]>pgn)
        pgn=tableau[i][j];
        ppg=i*NBC+j;//je calcule sa position dans un table 2d
     }

*vpgn=pgn; *vppgn=ppg;

}

int occ_x_tabl(int**tableau,int NBL,int NBC,int x)
{
  int i,j,occ=0;
  for (i=0;i<NBL;i++)
    for(j=0;j<NBC;j++)
       if(tableau[i][j]==x)
         occ++;

return occ;
}
void sompn_tabl(int**tableau,int NBL,int NBC)
{   int i,j,spos=0,sneg=0;

for (i=0;i<NBL;i++)
  for(j=0;j<NBC;j++)
    if(tableau[i][j]>0)
    {
      spos +=tableau[i][j];
    }
printf("\n\t la spos est :%d",spos);

  for (i=0;i<NBL;i++)
    for(j=0;j<NBC;j++)
    if(tableau[i][j]<0)
    {
      sneg +=tableau[i][j];
    }

    printf("\n\tla sneg est :%d",sneg);

}
void nbp_tabl (int**tableau,int NBL,int NBC)
{
  int i,j,nbp=0;
  for (i=0;i<NBL;i++)
    for(j=0;j<NBC;j++)
      if(tableau[i][j]>0)
         nbp++;

printf("\n\t le nombre des elmns positis:%d",nbp);

}
int sup_moy(int**tableau,int NBL,int NBC)
{
   int i,j,supmoy=0;

double moy=som_tabl(tableau,NBL,NBC)/(NBL*NBC);//calcule la moy d'un tableau 2d

  for (i=0;i<NBL;i++)
    for(j=0;j<NBC;j++)
      if(tableau[i][j]>moy)
         supmoy++;

return supmoy;

}
