#ifndef FILESTAB_H_INCLUDED
#define FILESTAB_H_INCLUDED

#define MaxLength 100

//Files : Tableaux

typedef struct {
    int Tab[MaxLength];
    int tete;
    int queu;
}TFile;

//Création de File: Allocation de mémoire Y
TFile * TF_Creer_TFile(){
    TFile *file = (TFile*)malloc(sizeof(TFile));
    if(!file){
        printf("\Erreur d'allocation...");
        exit(0);
    }
    (file->tete)=(file->queu)=-1;
    return ((TFile*)file);
}

//Pour tester si la file est vide Y
int TF_Est_Vide(TFile * file){
    //Si la file n'existe pas
    if(!file) return((int)-1);
    if(((file->queu)==-1) && ((file->tete)==-1)) return((int)1);
    return((int)0);
}

//Retourner la taille de la file Y
int TF_Taille_TFile(TFile * file){
    //Si la file n'existe pas
    if(!file) return((int)-1);
    //Si la file est vide
    if(TF_Est_Vide(file)) return 0;
    return ((int)((file->queu)-(file->tete)+1));
}

//pour tester si la file est saturée Y
int TF_Est_Saturee(TFile * file){
    //Si la file n'existe pas
    if(!file) return((int)-1);
    return((int)(TF_Taille_TFile(file)==MaxLength));
}

//Tasser la file Y
int TF_Tasser_File(TFile * file){
   //Si la file est saturée
   if(TF_Est_Saturee(file)) return ((int)1);
   int indice;
   for(indice=(file->tete);indice<=(file->queu);indice++)
        file->Tab[indice-(file->tete)] = file->Tab[indice];
   file->queu = indice - (file->tete) -1;
   file->tete=0;
   return ((int)1);
}

int TF_Defiler_Elem_TFile(TFile *file , int Elem)
{
    if(!file) return((int)-1); //existance de la liste
    if(TF_Est_Vide(file)) return((int)0);
    int ind;
    for(ind=0;ind<file->queu;ind++)
        if(file->Tab[ind] == Elem) return ((int)TF_Defiler_Elem_Pos(file, ind+1));
    (file->queu)--;
    TF_Tasser_File(file);
    return((int)-3);
}

//Empiler une valeur dans la file passée en argument Y
int TF_Enfiler(TFile * file, int v){
    //Si la file n'existe pas
    if(!file) file = TF_Creer_TFile();
    //Si la file est saturée
    if(TF_Est_Saturee(file)) return((int)0);
    //Si la file n'est pas tasser
    if((file->queu)==MaxLength-1) TF_Tasser_File(file);
    //Si la file est vide
    if(TF_Est_Vide(file)) (file->tete)++;
    (file->queu)++;
    file->Tab[(file->queu)] = v;
    return ((int)1);
}

//Défiler une valeur de la file Y
int TF_Defiler(TFile * file){
    //si la file n'existe pas
    if(!file) return((int)-1);
    //si la file est vide
    if(TF_Est_Vide(file)) return((int)0);
    if((file->queu)==(file->tete)) (file->queu)=(file->tete)=-1;
    else (file->tete)++;
    TF_Tasser_File(file);
    return((int)1);
}

//Retourne la valeur de tete Y
int TF_Retourner_Tete(TFile * file){
    if(file) return((int)file->Tab[file->tete]);
}

//Retourne la valeur de queue Y
int TF_Retourner_Queue(TFile * file){
    if(file) return((int)file->Tab[file->queu]);
}

//Vider la  Y
int TF_Vider_TFile(TFile * file){
    //Si la file n'existe pas
    if(!file) return((int)-1);
    //Si la file est vide
    (file->tete)=(file->queu)=-1;
    return((int)1);
}

//Insértion a une position donnée Y
int TF_Enfiler_Elem_Pos(TFile * file, int pos, int v){
    //si la file n'existe pas
    if(!file) return((int)-1);
    //Si la file est saturée
    if(TF_Est_Saturee(file)) return((int)0);
    //Si la position n'est pas valide
    if((pos>((file->queu)+1)) || (pos<1)) return((int)0);
    if(pos==((file->queu)+1)) return ((int)(TF_Enfiler(file, v)));
    int indice = (file->queu);
    pos= pos-1;
    while(indice!=(pos-1)){
        file->Tab[indice+1]=file->Tab[indice];
        indice--;
    }
    file->Tab[pos] = v;
    (file->queu)++;
    return ((int)1);
}

//Insértion apres une valeur
int TF_Enfiler_Apres_Elem(TFile * file, int elem, int v){
    //si la file n'existe pas
    if(!file) return((int)-1);
    //Si la file est saturée
    if(TF_Est_Saturee(file)) return((int)0);
    if(TF_Rechercher_Elem(file, elem)) return((int)TF_Enfiler_Elem_Pos(file, TF_Rechercher_Elem(file, elem)+1, v));
}

///7-Insértion bonne position
int TF_Inserer_Ordre_TFile(TFile * file, int elem){
    //si la pile n'existe pas
    if(!file) return((int)-1);
    if(TF_Est_Vide(file)) return((int)0);
    int indice = (file->queu);
    while(indice){
        if(file->Tab[indice-1]<=elem){
            TF_Enfiler_Elem_Pos(file, indice+1, elem);
            break;
        }
        indice--;
    }
    return ((int)1);
}


//Retourne valeur maximale de file Y
int TF_Max_Elem(TFile * file){
    //Si la file n'existe pas
    if(!file){
        printf("\nLa file n'existe pas!");
        return((int)-1);
    }
    if(TF_Est_Vide(file)){
        printf("\nLa file est vide!");
        return((int)0);
    }
    int m=file->Tab[file->queu], indice=(file->queu)-1;
    while(indice>=0){
        if((file->Tab[indice])>m) m=file->Tab[indice];
        indice--;
    }
    return((int)m);
}

//Retourne valeur minimale de file Y
int TF_Min_Elem(TFile * file){
    //Si la file n'existe pas
    if(!file){
        printf("\nLa file n'existe pas!");
        return((int)-1);
    }
    if(TF_Est_Vide(file)){
        printf("\nLa file est vide!");
        return((int)0);
    }
    int m=file->Tab[file->queu], indice=(file->queu)-1;
    while(indice>=0){
        if((file->Tab[indice])<m) m=file->Tab[indice];
        indice--;
    }
    return((int)m);
}

//Retourne valeur minimale de file Y
int TF_Somme_Elem(TFile * file){
    //Si la file n'existe pas
    if(!file) return((int)-1);
    if(TF_Est_Vide(file)) return((int)0);
    int s=0, indice=(file->queu)-1;
    while(indice>=0){
        s+=file->Tab[indice];
        indice--;
    }
    return((int)s);
}

//Rechercher Element Y
int TF_Rechercher_Elem(TFile * file,int v){
    if(!file){
        printf("\nLa file n'existe pas!");
        return((int)-1);
    }
    if(TF_Est_Vide(file)){
        printf("\nLa file est vide!");
        return((int)0);
    }
    int indice=file->queu;
    while(indice>=0){
        if((file->Tab[indice])==v)return((int)indice+1);
        indice--;
    }
    return((int)0);
}

//Suppression à une position donnée Y
int TF_Defiler_Elem_Pos(TFile * file, int pos){
    //si la file n'existe pas
    if(!file) return((int)-1);
    //si la file est vide
    if(TF_Est_Vide(file)) return((int)0);
    //Si la position n'est pas valide
    if((pos>((file->queu)+1)) || (pos<1)) return((int)0);
    if(pos==((file->tete))) return ((int)(TF_Defiler(file)));
    int indice = (file->queu);
    pos=pos-1;
    while(indice != pos){
        indice--;
    }
    while(indice!=(file->queu)){
        file->Tab[indice] = file->Tab[indice+1];
        indice++;
    }
    (file->queu)--;
    TF_Tasser_File(file);
    return((int)1);
}

///20-Inverser pile Y
TFile * TF_Inverser_File(TFile * file){
     //Si la pile n'existe pas
    if(!file) return((TFile*)NULL);
    //si la pile est vide
    if(TF_Est_Vide(file)) return((TFile*)NULL);
    int indice=TF_Taille_TFile(file)-1;
    TFile * tmp = TF_Creer_TFile();
    while(indice>=0){
        TF_Enfiler(tmp, file->Tab[indice]);
        indice--;
    }
    return((TFile*)tmp);
}

int TF_Compter_Occ(TFile * file, int v){
    if(!file) return((int)-1);
    if(TF_Est_Vide(file)) return((int)0);
    int c=0;
    int indice=TF_Taille_TFile(file)-1;
    while(indice>=0){
        if(file->Tab[indice] == v) c++;
        indice--;
    }
    return((int)c);
}

///16-Supprimer Occurences Y
int TF_Supp_Occ(TFile * file, int v){
     //Si la pile n'existe pas
    if(!file) return((int)-1);
    //si la pile est vide
    if(TF_Est_Vide(file)) return((int)0);
    while(TF_Compter_Occ(file, v)) TF_Defiler_Elem_TFile(file, v);
    return((int)1);
}

///16-Supprimer repetitions Y
int TF_Supp_Rep(TFile * file, int v){
     //Si la pile n'existe pas
    if(!file) return((int)-1);
    //si la pile est vide
    if(!(file->queu)) return((int)0);
    while(TF_Compter_Occ(file, v)>1){
        TF_Defiler_Elem_TFile(file, v);
    }
    return((int)1);
}

//Affichage de file Y
void TF_Afficher_TFile(TFile * file){
    //Si la file n'existe pas
    if(!file) printf("\nLa file n'existe pas");
    //Si la file est vide
    if(TF_Est_Vide(file)) printf("\nLa file est vide, rien a afficher!");
    else{
        int indice;
        printf("\n Votre file est: ");
        for(indice=(file->tete);indice<=(file->queu);indice++)
            printf("%d \t", file->Tab[indice]);
    }
}

#endif // FILESTAB_H_INCLUDED
