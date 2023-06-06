#ifndef PILES_H_INCLUDED
#define PILES_H_INCLUDED

//PILES_H_INCLUDED

#define MaxLength 100

/** ****************** PILES  TABLEAUX  ****************** **/
typedef struct {
    int Tab[MaxLength];
    int sommet;
}TPile;

///1-Création de Pile Y
TPile * TP_Creer_TPile(){
    TPile *pile = (TPile*)malloc(sizeof(TPile));
    if(!pile){
        printf("\Erreur d'allocation...");
        exit(0);
    }
    pile->sommet=0;
    return ((TPile*)pile);
}

///2-Initialisation de pile
int TP_Init_TPile(TPile * pile){
    //si la pile n'existe pas
    if(!pile) return((int)0);
    pile->sommet=0;
    return ((int)1);
}

///3-Pour tester si la pile est vide Y
int TP_Est_Vide(TPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    if((pile->sommet)==0) return((int)1);
    return((int)0);
}

///4-pour tester si la pile est saturée Y
int TP_Est_Saturee(TPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    return((int)((pile->sommet)==MaxLength));
}

///5-Insértion Y
int TP_Empiler(TPile * pile, int v){

    if(!pile) return((int)-1);
    
    if(TP_Est_Saturee(pile)) return((int)0);
    pile->Tab[pile->sommet]=v;
    (pile->sommet)++;
    
    return ((int)1);
}

///6-Insértion a une position donnée Y
int TP_Empiler_Elem_Pos(TPile * pile, int pos, int v){
    //si la pile n'existe pas
    if(!pile) return((int)-1);
    //Si la position n'est pas valide
    if(TP_Est_Saturee(pile)) return((int)0);
    if((pos>((pile->sommet)+1)) || (pos<1)) return((int)0);
    if(pos==((pile->sommet)+1)) return ((int)(TP_Empiler(pile, v)));
    int indice = (pile->sommet);
    pos = pos-1;
    while(indice!=pos){
        pile->Tab[indice]=pile->Tab[indice-1];
        indice--;
    }
    pile->Tab[pos] = v;
    (pile->sommet)++;
    return ((int)1);
}

///7-Insértion apres un element Y
int TP_Empiler_Apres_Elem(TPile * pile, int elem, int v){
    //si la pile n'existe pas
    if(!pile) return((int)-1);
    if(TP_Rechercher_Elem(pile, elem)) TP_Empiler_Elem_Pos(pile, TP_Rechercher_Elem(pile, elem)+1, v);
    return ((int)1);
}

///7-Insértion bonne position
int TP_Inserer_Ordre_TPile(TPile * pile, int elem){
    //si la pile n'existe pas
    if(!pile) return((int)-1);
    int indice = (pile->sommet);
    while(indice){
        if(pile->Tab[indice-1]<elem){
            TP_Empiler_Elem_Pos(pile, indice+1, elem);
            break;
        }
        indice--;
    }
    return ((int)1);
}

///8-Suppression Y
int TP_Depiler(TPile * pile){
    //si la pile n'existe pas
    if(!pile) return((int)-1);
    
    //si la pile est vide
    //if(!(pile->sommet)) return((int)0);
    if(TP_Est_Vide(pile)) return((int)0);
    
    (pile->sommet)--;
    return((int)1);
}

///9-Suppression à une position donnée Y
int TP_Depiler_Elem_Pos(TPile * pile, int pos){
    //si la pile n'existe pas
    if(!pile) return((int)-1);
    //si la pile est vide
    if(!(pile->sommet)) return((int)0);
    //si la position est invalide
    if(pos>(pile->sommet) || pos<1) return((int)0);
    int indice=(pile->sommet);
    while(indice != pos){
        indice--;
    }
    indice--;
    while(indice!=(pile->sommet)-1){
        pile->Tab[indice] = pile->Tab[indice+1];
        indice++;
    }
    (pile->sommet)--;
    return((int)1);
}

///10-Rechercher un élément et le dépiler Y
int TP_Depiler_Elem(TPile * pile, int v){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    //si la pile est vide
    if(TP_Est_Vide(pile)) return((int)0);
    
    int indice = (pile->sommet);
    while((pile->Tab[indice-1])!=v && (indice>0)) indice--;
    if(indice){
        while(indice!=(MaxLength)){
            pile->Tab[indice-1] = pile->Tab[indice];
            indice++;
        }
        (pile->sommet)--;
        return ((int)1);
    }
    return ((int)0);
}

///11-Retourne Max Element Y
int TP_Max_Elem(TPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    if(TP_Est_Vide(pile)) return((int)0);
    int m=pile->Tab[(pile->sommet)-1], indice=(pile->sommet)-1;
    while(indice>=0){
        if((pile->Tab[indice])>m) m=pile->Tab[indice];
        indice--;
    }
    return((int)m);
}

///12-Retourne Min Element Y
int TP_Min_Elem(TPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    if(TP_Est_Vide(pile)) return((int)0);
    int m=pile->Tab[(pile->sommet)-1], indice=(pile->sommet)-1;
    while(indice>=0){
        if((pile->Tab[indice])<m) m=pile->Tab[indice];
        indice--;
    }
    return((int)m);
}

///13-Retourne Somme Y
int TP_Somme_TPile(TPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    if(TP_Est_Vide(pile)) return((int)0);
    int m=0, indice=(pile->sommet)-1;
    while(indice>=0){
        m+=pile->Tab[indice];
        indice--;
    }
    return((int)m);
}

///14-Rechercher Element Y
int TP_Rechercher_Elem(TPile * pile,int v){
    if(!pile) return((int)-1);
    if(TP_Est_Vide(pile)) return((int)0);
    int indice=(pile->sommet)-1;
    while(indice>=0){
        if((pile->Tab[indice])==v) return((int)indice+1);
        indice--;
    }
    return((int)0);
}

///15-Compter nombre des occurences d'une valeur dans la pile Y
int TP_Compter_Occ(TPile * pile, int v){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    if(TP_Est_Vide(pile)) return((int)0);
    int indice=(pile->sommet)-1, c=0;
    while(indice>=0){
        if((pile->Tab[indice])==v){
            c++;
        }
        indice--;
    }
    return((int)c);
}

///16-Supprimer Occurences Y
int TP_Supp_Occ(TPile * pile, int v){
     //Si la pile n'existe pas
    if(!pile) return((int)-1);
    //si la pile est vide
    if(!(pile->sommet)) return((int)0);
    while(TP_Compter_Occ(pile, v)){
        TP_Depiler_Elem(pile, v);
    }
    return((int)1);
}

///17-Pour vider la pile Y
int TP_Vider_TPile(TPile * pile){
    if(!pile) return((int)-1);
    if(TP_Est_Vide(pile)) return((int)0);
    (pile->sommet)=0;
    return((int)1);
}

///18-Retourner la taille de la pile Y
int TP_Taille_TPile(TPile * pile){
    return ((int)(pile->sommet));
}

///19-Affichage de pile Y
void TP_Afficher_TPile(TPile * pile){
    //Si la pile n'existe pas
    if(!pile) printf("\nLa pile n'existe pas");
    //Si la pile est vide
    if(TP_Est_Vide(pile)) printf("\nLa pile est vide, rien a afficher!");
    
    if(!TP_Est_Vide(pile)){
        int indice = (pile->sommet);
        printf("\n Votre pile: \n");
        while(indice){
            indice--;
            printf("%d \t", pile->Tab[indice]);
        }
    }
}

///20-Inverser pile
TPile * TP_Inverser_Pile(TPile * pile){
     //Si la pile n'existe pas
    if(!pile) return((TPile*)NULL);
    //si la pile est vide
    if(TP_Est_Vide(pile)) return((TPile*)NULL);
    int indice=TP_Taille_TPile(pile)-1;
    TPile * tmp = TP_Creer_TPile();
    while(indice>=0){
        //empiler la pile temporaire
        TP_Empiler(tmp, pile->Tab[indice]);
        //Depiler la pile
        TP_Depiler(pile);
        indice--;
    }
    return((TPile*)tmp);
}

/** ************************************************** **/

/** ********************************************  PILES Pointeur  ******************************************************************** **/

typedef struct cel2{
    int val;
    struct cel2 * svt;
}PPile;

///1-Création de Pile: Allocation de mémoire
//+Initialisation de premier céllule

PPile * PP_Creer_PPile(int v){
    PPile *pile = (PPile*)malloc(sizeof(PPile));
    if(!pile){
        printf("\Erreur d'allocation...");
        exit(0);
    }
    pile->val=v;
    pile->svt=NULL;
    return ((PPile*)pile);
}

///2-Pour tester si la pile est vide
int PP_Est_Vide(PPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)1);
    return((int)0);
}

///3-Empiler une valeur dans la pile passée en argument
PPile * PP_Empiler(PPile * pile, int v){
    if(!pile) return((PPile*)PP_Creer_PPile(v));
    PPile * NE = PP_Creer_PPile(v);
    NE->svt = pile;
    return ((PPile*)NE);
}

///4-Dépiler une valeur de la pile
PPile * PP_Depiler(PPile * pile){
    //si la pile n'existe pas
    if(!pile) return((PPile*)NULL);
    //si la pile est vide
    if(PP_Est_Vide(pile)) return((PPile*)NULL);
    pile = pile->svt;
    return((PPile *)pile);
}


///5-Insértion a une position donnée
PPile * PP_Empiler_Elem_Pos(PPile * pile, int pos, int v){
    //si la pile n'existe pas
    if(!pile) return((PPile *)NULL);
    if((pos>(PP_Taille_PPile(pile)+1)) || (pos<1)) return((PPile *)NULL);
    if(pos==(PP_Taille_PPile(pile)+1)) return ((PPile *)(PP_Empiler(pile, v)));
    PPile * tmp = NULL;
    int indice = PP_Taille_PPile(pile);
    while(indice>=pos){
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    tmp = PP_Empiler(tmp, v);
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return ((PPile *)pile);
}

///6- Empiler apres un element
PPile * PP_Empiler_Apres_Elem(PPile * pile, int elem, int v){
    //si la pile n'existe pas
    if(!pile) return((PPile*)NULL);
    if(PP_Rechercher_Elem(pile, elem)) return((PPile*)PP_Empiler_Elem_Pos(pile, PP_Rechercher_Elem(pile, elem)+1, v));
    return((PPile*)pile);
}

///7-Suppression à une position donnée
PPile * PP_Depiler_Elem_Pos(PPile * pile, int pos){
    //si la pile n'existe pas
    if(!pile) return((PPile*)NULL);
    //si la position est invalide
    if((pos>(PP_Taille_PPile(pile)+1)) || (pos<1)) return((PPile *)NULL);
    if(pos==(PP_Taille_PPile(pile)+1)) return ((PPile *)(PP_Depiler(pile)));
    PPile * tmp = NULL;
    int indice = PP_Taille_PPile(pile);
    while(indice>pos){
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    pile = PP_Depiler(pile);
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return ((PPile *)pile);
}

///8-Rechercher un élément et le dépiler,delete by val
PPile * PP_Depiler_Elem(PPile * pile, int v){
    //si la pile n'existe pas
    if(!pile) return((PPile*)NULL);
    //si la pile est vide
    if(PP_Est_Vide(pile)) return((PPile*)NULL);
    PPile * tmp = NULL;
    int indice = PP_Taille_PPile(pile);
    while(indice){
        if((pile->val)==v) break;
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    pile = PP_Depiler(pile);
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return ((PPile *)pile);
}

///9-Retourne valeur maximale de pile
int PP_Max_Elem(PPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    int m=pile->val, indice=PP_Taille_PPile(pile)-1;
    pile=pile->svt;
    PPile * tmp = NULL;
    while(indice){
        if((pile->val)>m) m=(pile->val);
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return((int)m);
}

///10-Retourne valeur minimale de pile
int PP_Min_Elem(PPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    int m=pile->val, indice=PP_Taille_PPile(pile)-1;
    pile=pile->svt;
    PPile * tmp = NULL;
    while(indice){
        if((pile->val)<m) m=(pile->val);
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return((int)m);
}

///10- Somme
int PP_Somme_TPile(PPile * pile){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    int s=0, indice=PP_Taille_PPile(pile);
    PPile * tmp = NULL;
    while(indice){
        s+=(pile->val);
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return((int)s);
}

///11-Rechercher Element avec une valeur passée en argument
int PP_Rechercher_Elem(PPile * pile,int v){
    if(!pile){
        printf("\nLa pile n'existe pas!");
        return((int)-1);
    }
    if(PP_Est_Vide(pile)){
        printf("\nLa pile est vide!");
        return((int)0);
    }
    int indice=PP_Taille_PPile(pile)-1;
    PPile * tmp = NULL;
    while(indice){
        if((pile->val)==v){
            while(tmp){
                pile = PP_Empiler(pile, tmp->val);
                tmp = PP_Depiler(tmp);
            }
            return((int)indice+1);
        }
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return((int)0);
}

int PP_Rechercher_Elem_ind(PPile * pile,int pos)
{
  if(!pile){
        printf("\nLa pile n'existe pas!");
        return((int)-1);
    }
    if(PP_Est_Vide(pile)){
        printf("\nLa pile est vide!");
        return((int)0);
    }
    int indice=PP_Taille_PPile(pile);
    PPile * tmp = NULL;

    while (indice>pos) // tant qu'on a pas arriver a la position voulu
    {
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    int var = pile->val; // si la pos = 1 affecter la valeur a var

    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return((int)var); // retourner la valeur
}

///12-Compter nombre des occurences d'une valeur dans la pile
int PP_Compter_Occ(PPile * pile, int v){
    //Si la pile n'existe pas
    if(!pile) return((int)-1);
    int c=0, indice=PP_Taille_PPile(pile);
    PPile * tmp = NULL;
    while(indice){
        if((pile->val)==v) c++;
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return((int)c);
}

///13-Supprimer tout les occurences
PPile * PP_Supp_Occ(PPile * pile, int v){
     //Si la pile n'existe pas
    if(!pile) return((PPile*)NULL);
    while(PP_Compter_Occ(pile, v)) pile= PP_Depiler_Elem(pile, v);
    return((PPile*)pile);

}

///14-Inverser la pile
PPile * PP_Inverser_Pile(PPile * pile){
     //Si la pile n'existe pas
    if(!pile) return((PPile*)NULL);
    //si la pile est vide
    if(PP_Est_Vide(pile)) return((PPile*)NULL);
    int indice=PP_Taille_PPile(pile);
    PPile * tmp = NULL;
    while(indice){
        //empiler la pile temporaire
        tmp = PP_Empiler(tmp, pile->val);
        //Depiler la pile
        pile = PP_Depiler(pile);
        indice--;
    }
    return((PPile*)tmp);
}

///15-Pour vider la pile
PPile * PP_Vider_PPile(PPile * pile){
    if(!pile) return((PPile*)NULL);
    if(PP_Est_Vide(pile)) return((PPile*)NULL);
    while(!PP_Est_Vide(pile)) pile = PP_Depiler(pile);
    return((PPile*)pile);
}

///16-Retourner la taille de la pile
int PP_Taille_PPile(PPile * pile){
    if(!pile) return((int)0);
    int c=0;
    PPile *crt = pile;
    while(crt){
        c++;
        crt = crt->svt;
    }
    return ((int)c);
}

///Inserer Ordre
PPile * PP_Inserer_Ordre_PPile(PPile * pile, int v){
    //si la pile n'existe pas
    if(!pile) return((PPile *)NULL);
    PPile * tmp = NULL;
    int indice = PP_Taille_PPile(pile);
    while(indice){
        if(pile->val < v) break;
        tmp = PP_Empiler(tmp, pile->val);
        pile = PP_Depiler(pile);
        indice--;
    }
    pile = PP_Empiler(pile, v);
    while(tmp){
        pile = PP_Empiler(pile, tmp->val);
        tmp = PP_Depiler(tmp);
    }
    return ((PPile *)pile);
}

///17-Affichage de pile
void PP_Afficher_PPile(PPile * pile){
    //Si la pile est vide
    if(PP_Est_Vide(pile)) printf("\nLa pile est vide, rien a afficher!");
    if(pile){
        PPile * crt = pile;
        printf("\n Votre pile: \n");
        while(crt){
            printf(" %d  ", crt->val);
            crt = crt->svt;
        }
    }
}



#endif // PILES_H_INCLUDED
