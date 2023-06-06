#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

//fILES_H_INCLUDED


/** ****************** File pointeur  ****************** **/

typedef struct cell
{
    int val;
    struct cell *suiv;
}PCellule;

typedef struct
{
    PCellule *tete;
    PCellule *queue;
}PFile;


PCellule *CreerPCellule(int donnee)
{
    PCellule *Ne;
    Ne = (PCellule*)malloc(sizeof(PCellule));
    if(!Ne)
    {
        printf("Erreur d'allocation");
        return (NULL);
    }
    Ne->val=donnee;
    Ne->suiv=NULL;
    return((PCellule*)Ne);
}
PFile *CreerPFile()
{
    PFile *lafile;
     lafile=(PFile *)malloc(sizeof(PFile));
     if(!lafile)
     {
         printf("\nERREUR D'allocation");
         exit(0);
     }
     lafile->tete=lafile->queue=NULL;
     return ((PFile*)lafile);
}

/*Fonction:EstVidePfile
Entrée:File
Sorties:Retourne la valeur 1 si la file est vide, sinon 0
Description: Fonction de type int, qui permet de tester si la liste est vide ou non
*/
int EstVidePfile(PFile *lafile)
{
    return ((int)(lafile->queue==NULL));
}

/*Fonction:EnfilerPFile
Entrée:File
Sorties:Valeur 1 si l'enfilement s'est bien passée, sinon -1 s'il était saturé
Description: Fonction qui enfile un élément dans une file
*/
int EnfilerPFile(PFile *lafile , int Elem)
{
    PCellule *Ne;
    if(!lafile)
	{
		printf("\nFile nexiste pas");
		return ((int)-1);
	}
    Ne=CreerPCellule(Elem);
    if(EstVidePfile(lafile)) //si la file est vide
    {
        lafile->tete=lafile->queue=Ne;
    }
    else //sinon on insere a la fin
    {
    	lafile->queue->suiv=Ne;
        lafile->queue=Ne;
    }
    return ((int)1);
}

/*Fonction:DefilerPFile
Entrée:File
Sorties:Valeur 1 si la suppression s'est bien passé
Description: Fonction de type int qui défile un élément de la file.
*/
int DefilerPFile(PFile *lafile)
{
    PCellule *Ne;
   if(!lafile)
	{
		printf("\nFile nexiste pas");
		return ((int)-1);
	}
    if(EstVidePfile(lafile)) return((int)0);
    if(lafile->tete==lafile->queue)//un seul element dans la file
    {
        Ne=lafile->tete;
        lafile->tete=lafile->queue=NULL;
        free(Ne);
    }
    else
    {
        Ne=lafile->tete;
        lafile->tete=lafile->tete->suiv;
        free(Ne);
    }
    return ((int)1);
}

/*Fonction:EnfilerOrdreFil
Entrée:File, élément à enfiler
Sorties:Valeur 1 si l'enfilement d'élément s'est bien passée, sinon 0
Description: fonction de type int qui enfile un élément dans une file, en gardant l'ordre de la file
*/

/*Fonction:AffichePFile
Entrée:File
Sorties:
Description:Fonction de type void qui affiche les éléments de la file
*/
int AffichePFile(PFile *lafile)
 {
     PFile *tmp;
     int e,d;
     tmp=CreerPFile();
     if(!lafile)
     {
     	printf("\nFile n'existe pas");
     	return((int)-1);
	 }
      if(EstVidePfile(lafile))
     {
     	printf("\n File vide");
     	return((int)0);
	 }
	 printf("\nvotre file est :\n");
     while(lafile->tete)
     {
         printf("%d\t",lafile->tete->val);
         e=EnfilerPFile(tmp,lafile->tete->val);
         d=DefilerPFile(lafile);
     }
     while(tmp->tete)
     {
         e=EnfilerPFile(lafile,tmp->tete->val);
         d=DefilerPFile(tmp);
     }
     return((int)1);
 }

int TaillePFile(PFile* file)
{
    PFile* file2=NULL;//une file temporelle
    file2=CreerPFile();//creation de la file temporelle
    int comp=0;//initialisation de la file
    if(!file)
	{
		printf("\nFile nexiste pas");
		return ((int)-1);
	}

    if(EstVidePfile(file))  return((int)comp);//si la file est vide
    //Tantque la file n'est pas vide compter ses éléments
    while(!EstVidePfile(file))
    {
        EnfilerPFile(file2,file->tete->val);
        DefilerPFile(file);
        comp++;
    }
    /*Tantque la file 2 n'est pas vide mettre les éléments de
    la pile 2 dans la 1ere pile*/
    while(!EstVidePfile(file2))
    {
	    EnfilerPFile(file,file2->tete->val);
        DefilerPFile(file2);
    }
    return(comp);
}

//Ajouter une valeur by pos
int EnfilerPFilePos(PFile* file,int valeur,int pos)
{
	pos=pos-1;

    PFile *file2=NULL;//une file temporelle
    file2=CreerPFile();//creation de la file temporelle

    int comp=0;//compteur

//Si la file n'existe pas
    if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}
//Si la position est incorrecte
    else if((pos>TaillePFile(file))||(pos<0))
    {
    	  printf("\n Position Incorrecte \n");
		  return((int)-2);
	}
//Si la position designe la queue de la file on enfile directement
    else if(pos==TaillePFile(file))
        EnfilerPFile(file,valeur);
//Sinon
    else
    {
//Tantque la file n'est pas vide j'enfile tous les valeurs dans
//une file temporelle
        while(!EstVidePfile(file))
        {
            EnfilerPFile(file2,file->tete->val);
            DefilerPFile(file);
        }
//Tantque la file 2 n'est pas vide et le compteur est
//inferieur à la position
        while((!EstVidePfile(file2))&&(comp<pos))
        {
            EnfilerPFile(file,file2->tete->val);
            DefilerPFile(file2);
            comp++;
        }
//Enfilement de la valeur
        EnfilerPFile(file,valeur);
//remettre les valeurs dans la file initiale
        while(!EstVidePfile(file2))
        {
            EnfilerPFile(file,file2->tete->val);
            DefilerPFile(file2);
        }
    }
}

//delete_val_by_pos_done
int DefilerPos(PFile* file,int pos)
{
	pos=pos-1;

    PFile *file2=NULL;//une file temporelle
    file2=CreerPFile();//creation de la file temporelle

    int comp=0;//compteur
//Si la file n'existe pas
    if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}

//Si la file est vide
    else if(EstVidePfile(file))
    {
		printf("\nLa file est vide");
		return((int)0);
	}
//Si la position est incorrecte
   else if((pos>=TaillePFile(file))||(pos<0))
   {
   	    printf("\n Position Incorrecte\n");
   	    return((int)-2);
   }
   else
    {
//Tantque la file initiale n'est pas vide et le compteur est inferieur
//à la postion j'enfile dans la file 2 et j'incremente
            while(!EstVidePfile(file)&&(comp<pos))
                {
                    EnfilerPFile(file2,file->tete->val);
                    DefilerPFile(file);
                    comp++;
                }
//Defilement de la valeur à supprimer
                DefilerPFile(file);
//je continue à enfiler le reste de la file dans la file 2
                while(!EstVidePfile(file))
                {
                    EnfilerPFile(file2,file->tete->val);

                    DefilerPFile(file);
                }
//transmettre les valeurs de la file 2 dans la file initiale
                while(!EstVidePfile(file2))
                {
                    EnfilerPFile(file,file2->tete->val);
                    DefilerPFile(file2);
                }
    }
}
int RazePFile(PFile* file)
{
	if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}

//Si la file est vide
    if(EstVidePfile(file))
    {
		printf("\nLa file est deja vide");
		return((int)0);
	}
    while(!EstVidePfile(file)) DefilerPFile(file);
    return((int)0);
}

//delete_by_val
int SupprimerValeurPFfile(PFile* file,int valeur)
{
    PFile* file2=NULL;//une file temporelle
    file2=CreerPFile();//creation de la file temporelle
//Si la file n'existe pas
    if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}

//Si la file est vide
    else if(EstVidePfile(file))
    {
		printf("\nLa file est vide");
		return((int)0);
	}
    else
	{
//Tantque la valeur de la tete est différente de la valeur recherché
//j'enfile dans la file 2
            while(!EstVidePfile(file)&&((file->tete->val)!=valeur))
            {
                EnfilerPFile(file2,file->tete->val);
                DefilerPFile(file);
            }
//Si la file n'est pas vide ça veut dire que la valeur à été trouvé
            if(!EstVidePfile(file))
                DefilerPFile(file);//Defilement de la valeur
            else
                printf("\n La valeur n'existe pas \n");
//je continue à enfiler le reste de la file dans la file 2
            while(!EstVidePfile(file))
            {
                EnfilerPFile(file2,file->tete->val);
                DefilerPFile(file);
            }
//remettre les valeurs de la file 2 dans la file initiale
            while(!EstVidePfile(file2))
            {
                EnfilerPFile(file,file2->tete->val);
                DefilerPFile(file2);
            }
            return((int)1);
    }
}
//delete occurence
int SupprimerOccurenceFile(PFile* file,int val)
{
    PFile* file2=NULL;//une file temporelle
    file2=CreerPFile();//creation de la file temporelle

    int drap=0;//Drapeau
//Si la file n'existe pas
    if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}

//Si la file est vide
    else if(EstVidePfile(file))
    {
		printf("\nLa file est vide");
		return((int)0);
	}
    else
        {
//Tantque la file n'est pas vide
            while(!EstVidePfile(file))
            {
//Tantque la valeur de la tete est différente de la valeur recherché
//j'enfile dans la file 2
                while(!EstVidePfile(file)&&((file->tete->val)!=val))
                {
                    EnfilerPFile(file2,file->tete->val);
                    DefilerPFile(file);
                }
//Si la file n'est pas vide ça veut dire que la valeur à été trouvé
                if(!EstVidePfile(file))
                {
                    DefilerPFile(file);
                    drap=1;
                }
            }
//remettre les valeurs de la file 2 dans la file initiale
            while(!EstVidePfile(file2))
            {
                EnfilerPFile(file,file2->tete->val);
                DefilerPFile(file2);
            }
//si drap =0 ca veut dire que la valeur n'existe pas
            if(!drap)
                printf("\nla valeur %d n'existe pas\n",val);
            else
                printf("\nTous les occurances de la valeur %d ont ete supprimees",val);
            }
            return((int)1);
}

int EstTrieePFile(PFile* file)
{
    int drap=1;
    PFile* file2=NULL;//une file temporelle
    file2=CreerPFile();//creation de la file temporelle
	if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}
    else if(EstVidePfile(file))
    {
		printf("\nLa file est vide");
		return((int)-2);
	}
//Si la file contient une seule valeur
    if(TaillePFile(file)==1)
        return ((int)drap);
//Tantque la file n'est pas vide et le drapeau n'est pas nul
    while(!EstVidePfile(file)&&(drap))
    {
//Enfiler dans la file 2
        EnfilerPFile(file2,file->tete->val);
        DefilerPFile(file);
//Si la file n'est pas vide et la valeur defilée(la queue de la file 2)
//est superieur à la valeur de la tete de la file initiale metttre
//le drapeau à zéro
        if(!EstVidePfile(file)&&((file2->queue->val)>(file->tete->val)))
            drap=0;
        }
//remettre les valeurs de la file 2 dans la file initiale
    while(!EstVidePfile(file2))
    {
        EnfilerPFile(file,file2->tete->val);
        DefilerPFile(file2);
    }
    return((int)drap);
}

//insert bonne position
int EnfilerOrdreFile(PFile *lafile , int Elem)
{
    PCellule *Ne;

    int e,d,i=0;

    if(!lafile) return ((int)-1);
    Ne=CreerPCellule(Elem);

    if(EstVidePfile(lafile))
    {
        lafile->queue=lafile->tete=Ne;
        return ((int)-2);
    }
    if(!EstTrieePFile(lafile))
    {
    	printf("\nLa file n est pas triee");
    	return((int)-2);
	}

    if((lafile->queue==lafile->tete)&&(Elem > lafile->tete->val))
    {
        e=EnfilerPFile(lafile,Elem);
        return ((int)1);
    }
    if(Elem > lafile->queue->val)
    {
        e=EnfilerPFile(lafile,Elem);
        return ((int)1);
    }

    PFile *tmp;
    tmp=CreerPFile();

    while(lafile->tete)
    {
        if((Elem < lafile->tete->val)&&(i<1))
        {
            e=EnfilerPFile(tmp,Elem);
            i++;
        }
        e=EnfilerPFile(tmp,lafile->tete->val);
        d=DefilerPFile(lafile);
    }
    while(tmp->tete)
    {
        e=EnfilerPFile(lafile,tmp->tete->val);
        d=DefilerPFile(tmp);
    }
    return ((int)1);
}

//insert boone position = trier file
int Triee_PFile(PFile* file)
{
    PFile *file2=NULL;
    file2=CreerPFile();

    if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}
    if(EstVidePfile(file))
    {
		printf("\nLa file est vide");
		return((int)-2);
	}
    if(EstTrieePFile(file))
    {
    	printf("\nLa file est deja triee");
    	return((int)0);
	}
    else
    {
	//Tantque la file n'est pas vide inserer les valeurs d'une façon
	// ordonnée dans la file 2
    while(!EstVidePfile(file))
    {
            EnfilerOrdreFile(file2,file->tete->val);
            DefilerPFile(file);
	}
//Tantque la file 2 n'est pas vide enfiler les valeurs dans
//la file initiale
    while(!EstVidePfile(file2))
        {
            EnfilerPFile(file,file2->tete->val);
            DefilerPFile(file2);
        }
    }
    return((int)1);
}

int InverserPFile(PFile* file)
{
    int comp1=TaillePFile(file),comp2;
    PFile* fileRes=NULL;//la file de la resultat
    PFile* file2=NULL;//file temporelle
    fileRes=CreerPFile();
    file2=CreerPFile();
    if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}
    if(EstVidePfile(file))
    {
		printf("\nLa file est vide");
		return((int)-2);
	}
    else
    {
//Tant que le compteur n'est pas nul
        while(comp1)
        {
//j'initialise mon 2eme compteur à la taille courante
//de la file moins un
            comp2=TaillePFile(file)-1;
            while(comp2)
            {
//j'enfile dans file2 et je decrimente
                EnfilerPFile(file2,file->tete->val);
                DefilerPFile(file);
                comp2--;
            }
//il reste une seule valeur dans la file initiale, je l'enfile dans
//la file resultat et je la defile de la file initiale
            EnfilerPFile(fileRes,file->tete->val);
            DefilerPFile(file);
//remettre les valeurs de la file 2 dans la file initiale
            while(!EstVidePfile(file2))
            {
                EnfilerPFile(file,file2->tete->val);
                DefilerPFile(file2);
            }
            comp1--;
        }
//j'enfile le contenue de la file resultat dans la file initiale
        while(!EstVidePfile(fileRes))
        {
            EnfilerPFile(file,fileRes->tete->val);
            DefilerPFile(fileRes);
        }
    }
}

int MaxPFile(PFile* file)
{
    PFile* file2=NULL;//file temporelle
    file2=CreerPFile();
    int max=0;
    if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}
    if(EstVidePfile(file))
    {
		printf("\nLa file est vide");
		return((int)-2);
	}
    max=file->tete->val;
//Tantque la file n'est pas vide j'enfile dans la file 2
    while(!EstVidePfile(file))
    {   EnfilerPFile(file2,file->tete->val);
        DefilerPFile(file);
        if(!EstVidePfile(file)&&((file->tete->val)>(max)))
            max=file->tete->val;//l'affectation du maximum
    }
//remettre les valeurs de la file 2 dans la file initiale
    while(!EstVidePfile(file2))
    {
        EnfilerPFile(file,file2->tete->val);
        DefilerPFile(file2);
    }

    return((int)max);
}

int MinPFile(PFile* file)
{
    PFile* file2=NULL;//file temporelle
    file2=CreerPFile();
    int min=0;
    if(!file)
    {
    	printf("\nLa file n'existe pas\n");
    	return((int)-1);
	}
    if(EstVidePfile(file))
    {
		printf("\nLa file est vide");
		return((int)-2);
	}
    min=file->tete->val;
//Tantque la file n'est pas vide j'enfile dans la file 2
    while(!EstVidePfile(file))
    {   EnfilerPFile(file2,file->tete->val);
        DefilerPFile(file);
        if(!EstVidePfile(file)&&((file->tete->val)<(min)))
            min=file->tete->val;//l'affectation du maximum
    }
//remettre les valeurs de la file 2 dans la file initiale
    while(!EstVidePfile(file2))
    {
        EnfilerPFile(file,file2->tete->val);
        DefilerPFile(file2);
    }

    return((int)min);
}




#endif // FILES_H_INCLUDED
