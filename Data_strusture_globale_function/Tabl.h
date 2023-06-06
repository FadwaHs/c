#ifndef TABL_H_INCLUDED
#define MAX 100


//LISTES_INCLUDED

/** ****************** LISTES TABLEAUSX  ****************** **/

typedef struct {

 int tab[MAX];
 int n;// nombre d'enregistrements de la liste

}Tableau;


//fonction qui permet de faire l' allocation dynamique de la liste et l'initialisation
Tableau *Creer_Tableau()
{
    Tableau *PT;

	PT=(Tableau *)malloc(sizeof(Tableau));
	//si l'adresse est vide (NULL)
	if(!PT)
	{
		printf("Erreur d'allocation");
		exit(0);
	}

	PT->n =0;
	return (Tableau*)PT;
}

int Remlire_Tab( Tableau * Tab ,int nbr)
{
   if(!Tab) return((int)-1); //existance de la liste
   int i;
   for(i=0;i<nbr;i++)
   {
    printf("T[%d]=  \n",i);
    scanf("%d",&Tab->tab[i]);
   }
  return((int)1);
}

void aficher_tab(Tableau * Tab )
{
   int i;
   for(i=0;i<Tab->n;i++)
   {
    printf("%d ",Tab->tab[i]);

   }

}

//une fonction qui permet de tester si le tableau est saturer ou non
bool Saturer(Tableau * Tab)
{
   if(MAX == Tab->n)
   {
      printf("le tableau est saturé");
      return true;
   }
   else if(Tab->n < MAX)
   {
       return false;
   }

}

//fonction permet d' inserer un  element dans la fin de la liste
int insert_elmnt_Queue(Tableau * Tab,int val)
{
   if(!Tab)
   {
     return((int)-1);
   }

   if(Saturer(Tab))
   {
        printf("Liste Saturee");
		return((int)0);
   }

   Tab->tab[Tab->n++]=val;//ajouter dans la fin de tabelau la valeur
   //aficher_tab(Tab); //réafficher le tableau après l'insertion
}

//permet d'inserer un element a une position donner
int insert_elmnt_position(Tableau * Tab,int ind , int val)
{
   int i;
   //si la liste n'existe pas
   if(!Tab)
	{
		printf("Liste n existe pas");
		return((int)-1);
	}
   //si l'indice est incorrecte
   if((ind<0) || (ind>Tab->n)) return ((int)0);
   //si la liste est saturer
   if(Saturer(Tab))
   {
        printf("Liste Saturee");
		return((int)0);
   }
  for(i =Tab->n++ ;i>ind ; i--)
  {
      Tab->tab[i] = Tab->tab[i-1];//faire un decalage de tableau

  }
   Tab->tab[i] = val;
   //aficher_tab(Tab); //réafficher le tableau après l'insertion

   return((int)1);
}

//inserer un element au Debut de la liste
int insert_elmnt_Debut(Tableau * Tab,int val)
{
  if(!Tab)
	{
		printf("Liste n existe pas");
		return((int)-1);
	}

   if(Saturer(Tab))
   {
        printf("Liste Saturee");
		return((int)0);
   }

  for(int i =Tab->n++ ;i>=0 ; i--)
  {
      Tab->tab[i] = Tab->tab[i-1];//décalage

  }
   Tab->tab[0] = val;
   //aficher_tab(Tab);
}

void TableauBonPlace(Tableau * Tab,int elem)
{
	int compt=0;
	if(Tab)
	{
		if(Tab->n==0)
		{
		   insert_elmnt_position(Tab,0,elem);
		}

		else
		{
           for(compt=0;compt<Tab->n;compt++)
           {
               if(Tab->tab[compt]>elem)
                {
           		 insert_elmnt_position(Tab,compt,elem);
           		return;
           	  }

           }
           
          insert_elmnt_position(Tab,Tab->n,elem);
          
		}
	}
}


//supprimer a la fin de la liste
int delete_Queue(Tableau * Tab)
{
   //verifier si le tableau est n'existe pas
   if(!Tab)
	{
		printf("Liste n existe pas");
		return((int)-1);
	}

   for(int i = Tab->n-1 ; i <Tab->n ; i++)
   {
           Tab->tab[i] = Tab->tab[i-1];//faire un décalage de tableau
   }

   Tab->n--; //décrémentez la taille du tableau de un.
   //printf("\nla liste après la suppression de la fin : \n");
   //aficher_tab(Tab);
}

//supprimer un element de la liste par son indice
int delete_elmnt(Tableau * Tab,int ind)
{
   if(!Tab)
	{
		printf("Liste n existe pas");
		return((int)-1);
	}
   //verifier l'indice si c'est valide
   if((ind<0) || (ind>=Tab->n)) return ((int)0);

   for(int i = ind ; i <Tab->n ; i++)
   {
        Tab->tab[i] = Tab->tab[i+1]; // Copiez l'élément suivant dans l'élément actuel du tableau
   }
   Tab->n--; //décrémentez la taille du tableau de un.

}

//supprimer un element de la liste par sa valeur
int delete_elmnt_val(Tableau * Tab,int val)
{
   if(!Tab)
	{
		printf("Liste n existe pas");
		return((int)-1);
	}
   for(int i = 0 ; i <Tab->n ; i++)
   {
       if(Tab->tab[i] == val)
       {
           return((int)delete_elmnt(Tab,i));
       }
   }
}

//fonction qui permet de supprimer la val qui se répète plusieur fois
void delete_occ(Tableau * Tab,int val)
{

  while(compter_occurence(Tab,val))
  {
     delete_elmnt_val(Tab,val);
  }
     printf("la liste après la suppression des occurrences : \n");
     //aficher_tab(Tab);
}



///10-insertion apres une valeur d'une liste
int InsererApresElemTListe(Tableau * Tab,int val,int Elem)
{
    if(!Tab) return((int)-1); //existance de la liste
    int ind;
    int pos = search_by_Val(Tab,Elem);
    return((int) insert_elmnt_position(Tab,pos+1,val) );
}


//fonction qui permet de reverser les element de la liste avec deux methode
void reverser_tab(Tableau * Tab )
{
 int i;
 for(i=0 ;i<Tab->n/2;i++)
  {
     int j = Tab->n-1-i;
     // inverser sans ajouter un autre element
     Tab->tab[j]=Tab->tab[j]+Tab->tab[i];
     Tab->tab[i]=Tab->tab[j]-Tab->tab[i];
     Tab->tab[j]=Tab->tab[j]-Tab->tab[i];

//     inverser avec un autre element 'permutation'
//     double elm;
//     elm=Tab->tab[i];
//     Tab->tab[i]=Tab->tab[j];
//     Tab->tab[j]=elm;
  }
 printf("la liste renverser : \n");
 aficher_tab(Tab); // réafficher le tableau après la suppression
}

//permet de compter le nbr d'occurence d'une valeur
int compter_occurence(Tableau *Tab , int val)
{
     int i;
     int occ =0;
     for(i=0 ; i<Tab->n ; i++)
     {
        if(Tab->tab[i] == val)//a chaque fois en trouve l'egalité
        {
          occ++;

        }
     }
  return((int)occ);
}

//chercher un element de la liste par sa valeur est revoyer son indice
int search_by_Val(Tableau *Tab , int val)
{
   int i,ind;
   //si la liste n'existe pas
   if(!Tab)
	{
		printf("Liste n existe pas");
		return((int)-1);
	}
	//sinon
	for(i=0; i<Tab->n ; i++)
	{
	   if(Tab->tab[i] == val)
	   {
	      ind=i;//récuperer l'indice de l'ement
	      return((int)ind);
	   }
	}
}

//chercher un element de la liste par sa valeur est revoyer son indice
int search_by_pos(Tableau *Tab , int pos)
{
  int ind;
   for(ind=0;ind<Tab->n;ind++)
    if(ind==pos)
        return((int)Tab->tab[ind]);
   return((int)-1);
}


///16-Max d'une liste
int MaxListe(Tableau *Tab)
{
    int ind,max;
    if(!Tab) return((int)-1);//existance de la liste
    max=Tab->tab[0];
    for(ind=1;ind<Tab->n;ind++)
    {
        if(max< Tab->tab[ind]) max=Tab->tab[ind];
    }
   return ((int)max);
}

///17-Min d'une liste
int MinListe(Tableau *Tab)
{
    int ind,min;
    if(!Tab) return((int)-1);//existance de la liste
    min=Tab->tab[0];
    for(ind=1;ind<Tab->n;ind++)
    {
        if(min>Tab->tab[ind]) min=Tab->tab[ind];
    }
    return ((int)min);
}

// Valeur max entre 2 indices i et j
int Max_Liste_entre_ij (Tableau *Tab,int i,int j)
{
    if(!Tab) return ((int)-1); // -1 si la liste n'existe pas

    if ( i > j) return((int)-3);
    int Max=Tab->tab[i]; // initialiser Max par la prmeiere valeur
    for (int ind = i+1; ind < j+1; ind++) // boucler sur les elements entre i et j
    {
        if(Tab->tab[ind] > Max) Max = Tab->tab[ind]; // affectation de la valeur courante si > Max
    }
    return((int)Max); // retourner la valeur maximale
}

int Indice_Max_Liste_entre_ij (Tableau *Tab,int i,int j)
{
    if(!Tab) return ((int)-1);// -1 si la liste n'existe pas
    //if((Indice_Valide(liste,i) == -2)||(Indice_Valide(liste,j) == -2)) return((int)-2); // -2 si l'un des indices est invalide
    if(i>j) return((int)-3); // -3 si i > j
    int Max=Tab->tab[i]; // affectation de la premiere valeur
    int ind_Max = i; // affectation du premier indice
    for (int ind = i+1; ind < j+1; ind++) // boucler sur les elements entre i et j
    {
        if(Tab->tab[ind] > Max)  // si elemen en cours de traitement > Max
        {
            Max = Tab->tab[ind]; // affectation de la valeur
            ind_Max = ind;// affectation de l'indice
        }
    }
    return((int)ind_Max); // retourner l'indice du max
}

int Indice_Min_Liste_entre_ij (Tableau *Tab,int i,int j)
{
    if(!Tab) return ((int)-1);// -1 si la liste n'existe pas
    //if((Indice_Valide(liste,i) == -2)||(Indice_Valide(liste,j) == -2)) return((int)-2); // -2 si l'un des indices est invalide
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

// Fonction qui echange deux elements d'indices i et j(permutation)
int Echanger_Pos_Liste(Tableau *Tab,int ind1,int ind2)
{
    if(!Tab) return((int)-1); // -1 si la liste n'existe pas
    //if((Indice_Valide(liste,ind1) == -2 )||(Indice_Valide(liste,ind2) == -2 )) return ((int)-2); // si l'un des deux indices est non valide
    int var; // initialiser une variable
    var = Tab->tab[ind1]; // stocker l'element du premier indice dans var
    Tab->tab[ind1] = Tab->tab[ind2]; // inserer le 2eme elem a la place du premier
    Tab->tab[ind2] = var; // inserer le 1 elem a la place du 2eme
    return((int)1); // 1 si l'echange est bien fait
}

int Trier_Liste(Tableau *Tab,int i) /** A REVOIR **/
{
    if(!Tab) return((int)-1);
    if(i == 1)
    {
        for (int ind = 0; ind <Tab->n; ind++) Echanger_Pos_Liste(Tab,ind,Indice_Min_Liste_entre_ij(Tab,ind,Tab->n-1));
    }
    return((int)1);
}



#endif // LISTES_H_INCLUDED
