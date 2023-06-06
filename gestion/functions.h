#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


char *module[48]={"algorithmique" , "bdd" , "logique","tec" ,"droit","reseau","se","programmation",
					"analyse et conception","sgbd oracle","projet et systeme d'information","web",
					"cryptographie","compilation","gestion","anglais","poo","java","android","pj2ee",
					"economie","integration web","a","b","c","d","e" ,"f","g","h","i","j","k","l",
					"m","n","o","p","q","r","s","t","u","v","w","stage1","stage2","stage3"};

typedef struct
{
    int numPromo;
    char nom[26];//le nom
    char prenom[26];//le prénom
    char cne[11];//le cne
    char date_n[10];//la date de naissance
    float note[48];//les notes des modules
    float moyenne[3];//la moyenne de l’année
    int anneeReserve;//est ce qu il a le droit pour une anne de reserve 0 oui 1 non
    
}etudiant;

typedef struct cel
{
    etudiant Etud;
    struct cel *suiv;
    
}LEtud;

/*C'est un tableau de deux dimentions de type LEtud (La liste des étudiants) :
Ce tableau se constitue de 3 promotions (2019-2020-2021), et se base sur 26 lettres.*/
LEtud *promo[3][26];

/********************************************************************************/
/*Fonction:initpromo
Entrée: __
Sorties: __
Description:Cette fonction permet d'initialiser les listes des étudiants par null
*/
void initpromo()
{
	int i,j;
    for(i=0 ; i<3 ;i++)
        for(j=0 ; j<26 ; j++)
            promo[i][j]=NULL;
}

/********************************************************************************/
/*Fonction:CreerCellule
Entrée: Etudiant
Sorties: listeEtud
Description:Cette fonction permet de créer une cellule Etudiant
*/
LEtud *CreerCellule(etudiant donnee)
{
    LEtud *Ne;
    Ne = (LEtud*)malloc(sizeof(LEtud));
    if(!Ne)
    {
        printf("Erreur d'allocation");
        return (NULL);
    }
    Ne->Etud=donnee;
    Ne->suiv=NULL;
    return((LEtud*)Ne);
}
/********************************************************************************/
/*Fonction:InsererBonnePlace
Entrées: Etudiant, listeEtud
Sorties: listeEtud
Description:Cette fonction permet d'insérer à la bonne place l'étudiant
selon l'ordre alphabétique
*/
LEtud *InsererBonnePlace(LEtud *Pliste , etudiant Elem)
{
    LEtud *NE;
    LEtud *ptc;
    NE = (LEtud*)CreerCellule(Elem);
    if(!Pliste)
        return((LEtud*)NE);
    ptc=Pliste;
    if(strcmp(Elem.nom , ptc->Etud.nom) == -1)
    {
        NE->suiv= Pliste;
        return ((LEtud*)NE);
    }
    while(ptc->suiv)
    {
        if(strcmp(Elem.nom , ptc->suiv->Etud.nom) == -1)
            break;
        ptc=ptc->suiv;
    }
    NE->suiv= ptc->suiv;
    ptc->suiv=NE;
    return ((LEtud*)Pliste);

}
/********************************************************************************/
/*Fonction:lecture_fich_trans_bdd
Entrée: __
Sorties: __
Description:Cette fonction de transférer les données depuis le fichier vers la structure
*/
void lecture_fich_trans_bdd()
{
    FILE *f;///pointeur sur le fichier
    etudiant e,e1;
    char c;
    f=fopen("bdd.txt","r+");
    if(!f)
    {
        printf("l'overture du fichier a echoue");
        exit(-1);
    }
    do
    {
        int j,i;
        fscanf(f,"%d ,",&e.numPromo);
        fscanf(f,"%[^,] ,%[^,] ,%s ,%s ",e.nom,e.prenom,e.cne,e.date_n);
        switch(e.numPromo)
        {
            case 2021 : j=16 ; break;
            case 2020 : j=32 ; break;
            case 2019 : j=48 ; break;
        }
        for(i=0 ; i<j ; i++)
        {
            fscanf(f,",%f ",&e.note[i]);
        }
        fscanf(f,",%d \n",&e.anneeReserve);
        promo[2021-e.numPromo][(int)(e.nom[0]-'A')] = InsererBonnePlace(promo[2021-e.numPromo][(int)(e.nom[0]-'A')],e);
        
    }while (!feof(f));
    fclose(f);
}
/********************************************************************************/
/*Fonction:affichePListe
Entrée: ListeEtud
Sorties: __
Description:Cette fonction d'afficher les informations sur les étudiants d'une
liste donnée.
*/
void affichePListe(LEtud *Pliste)
{
    LEtud *ptc;
    ptc=Pliste;
    while(ptc)
    {
        printf("%s , %s , %s\n",ptc->Etud.cne ,ptc->Etud.nom , ptc->Etud.prenom);
        ptc=ptc->suiv;
    }
}
/********************************************************************************/
/*Fonction:AvgE
Entrées: Etudiant,indice i et indice j, indiquent l'intervalle des notes à calculer
Sorties: float moyenne
Description:Cette fonction permet de calculer la moyenne des notes d'un étudiant
*/
float AvgE(etudiant e ,int i , int j)
{
    int k,S=0;
    for(k=i ; k<j ; k++)
        S+=e.note[k];
    return((float)(S)/16);
}
/********************************************************************************/
/*Fonction:MoyenneAnnee
Entrée: Etudiant
Sorties: __
Description:Cette fonction permet de calculer la moyenne des années qu'il a étudiée
*/
void MoyenneAnnee(etudiant *e)
{
    switch(e->numPromo)
    {
        case 2019 : e->moyenne[2]=AvgE(*e , 32 , 48);
        case 2020 : e->moyenne[1]=AvgE(*e , 16 , 32);
        case 2021 : e->moyenne[0]=AvgE(*e , 0 , 16);break;
    }
}
/********************************************************************************/
/*Fonction:Module10et12
Entrées: Etudiant,année
Sorties: entier = nombre des modules entre 10 et 12
Description:Cette fonction permet de compter le nombre des notes des modules
qui sont entre 10 et 12.
*/
int Module10et12(etudiant e , int annee)
{
    int k,S=0,i,j;
    switch(annee)
    {
        case 2021 : {i=0 ; j=16;};break;
        case 2020 : {i=16 ; j=32;};break;
        case 2019 : {i=32 ; j=48;};break;
    }
    for(k=i ; k<j ; k++)
        if((e.note[k]>=10)&&(e.note[k]<12))
            S++;
    return((int)S);
}
/********************************************************************************/
/*Fonction:ModuleInf10
Entrées: Etudiant,année
Sorties: entier = nombre des modules inférieur à 10
Description:Cette fonction permet de compter le nombre des notes des modules
qui sont inférieur à 10.
*/
int ModuleInf10(etudiant e , int annee)
{
    int k,S=0,i,j;
    switch(annee)
    {
        case 2021 : {i=0 ; j=16;};break;
        case 2020 : {i=16 ; j=32;};break;
        case 2019 : {i=32 ; j=48;};break;
    }
    for(k=i ; k<j ; k++)
        if(e.note[k]<10)
            S++;
    return((int)S);
}
/********************************************************************************/
/*Fonction:affecterMoyenne
Entrée: Numero Promo
Sorties: __
Description:Cette fonction permet d'affecter la moyenne à tout les étudiant de la promo
donnée
*/
void affecterMoyenne(int Numpromo)
{
    LEtud *ptc;
    int i;
    for(i=0 ; i<26 ; i++)
    {
        ptc = promo[2021-Numpromo][i];
        while(ptc)
        {
            MoyenneAnnee(&ptc->Etud);
            ptc=ptc->suiv;
        }
    }
}
/********************************************************************************/
/*Fonction:Valide
Entrées: ListeETud, Annee
Sorties: __
Description:Cette fonction permet d'afficher les informations des étudiants qui
ont validé pour une liste donnée
*/
void Valide(LEtud *liste , int annee)
{
    if(!liste) return;
    LEtud *ptc;
    ptc=liste;
    while(ptc)
    {
        if((ptc->Etud.moyenne[annee-ptc->Etud.numPromo] >=12)&&(Module10et12(ptc->Etud , annee)<=4)&&(ModuleInf10(ptc->Etud,annee)==0))
            printf("\n%s %s moyenne = %.4f",ptc->Etud.nom , ptc->Etud.prenom , ptc->Etud.moyenne[annee-ptc->Etud.numPromo]);
        ptc=ptc->suiv;
    }
}
/********************************************************************************/
/*Fonction:Echoue
Entrées: ListeETud, Annee
Sorties: __
Description:Cette fonction permet d'afficher les informations des étudiants qui
ont échoué pour une liste donnée et vérifie l'année de réserve
*/
void Echoue(LEtud *liste , int annee)
{
    if(!liste) return;
    LEtud *ptc;
    ptc=liste;
    while(ptc)
    {
        if((ptc->Etud.moyenne[annee-ptc->Etud.numPromo] < 12)||(Module10et12(ptc->Etud , annee)>4)||(ModuleInf10(ptc->Etud,annee)!=0))
            {
                printf("\n%s %s moyenne = %.4f",ptc->Etud.nom , ptc->Etud.prenom , ptc->Etud.moyenne[annee-ptc->Etud.numPromo]);
                if(ptc->Etud.anneeReserve==0)
                    printf("\tannee de reservre possible");
                else
                    printf("\tannee de reservre pas possible");

            }
        ptc=ptc->suiv;
    }
}

/********************************************************************************/
/*Fonction:affichePromo
Entrée: Numero Promo
Sorties: __
Description:Cette fonction permet d'afficher les informations des étudiants qui
appartient à une promo donnée
*/
void affichePromo(int numPromo)
{
	int i;
    for(i=0 ; i<26 ; i++)
        affichePListe(promo[2021-numPromo][i]);
}
/********************************************************************************/
/*Fonction:afficheValide
Entrées: Numero Promo,Annee
Sorties: __
Description:Cette fonction permet d'afficher les informations des étudiants qui
ont validé l'année à une promo donnée
*/
void afficheValide(int numPromo , int annee)
{
	int i;
    printf("\n\nLes etudiants qui ont valide l'annee %d:",annee);
    for(i=0 ; i<26 ; i++)
    {
        Valide(promo[2021-numPromo][i],annee);
    }
}
/********************************************************************************/
/*Fonction:afficheEchoue
Entrées: Numero Promo,Annee
Sorties: __
Description:Cette fonction permet d'afficher les informations des étudiants qui
ont échouee l'année à une promo donnée
*/
void afficheEchoue(int numPromo , int annee)
{
	int i;
    printf("\n\nLes etudiants qui ont echoue l'annee %d:",annee);
    for(i=0 ; i<26 ; i++)
    {
        Echoue(promo[2021-numPromo][i],annee);
    }

}
/********************************************************************************/
/*Fonction:NbEtudValid
Entrées: Promo,année
Sorties: entier = nombre des étudiants uqi ont validé
Description:Cette fonction permet de compter le nombre des étudiants qui ont
validé l'année pour cette promo
*/
int NbEtudValid(int numPromo , int annee )
{
    LEtud *ptc;
    int i,N=0;
    for(i=0 ; i<26 ; i++)
    {
        ptc=promo[2021-numPromo][i];
        while(ptc)
        {
            if((ptc->Etud.moyenne[annee-ptc->Etud.numPromo] >=12)&&(Module10et12(ptc->Etud , annee)<=4)&&(ModuleInf10(ptc->Etud,annee)==0))
                N++;
            ptc=ptc->suiv;
        }
    }
    return((int)N);
}
/********************************************************************************/
/*Fonction:NbEtudEchoue
Entrées: Promo,année
Sorties: entier = nombre des étudiants uqi ont validé
Description:Cette fonction permet de compter le nombre des étudiants qui ont
échoué l'année pour cette promo
*/
int NbEtudEchoue(int numPromo , int annee )
{
    LEtud *ptc;
    int i,N=0;
    for(i=0 ; i<26 ; i++)
    {
        ptc=promo[2021-numPromo][i];
        while(ptc)
        {
            if((ptc->Etud.moyenne[annee-ptc->Etud.numPromo] <12)||(Module10et12(ptc->Etud , annee)>4)||(ModuleInf10(ptc->Etud,annee)!=0))
                N++;
            ptc=ptc->suiv;
        }
    }
    return((int)N);
}
/********************************************************************************/
/*Fonction:NbEtudParPromo
Entrée: Promo
Sorties: entier = nombre des étudiants par promo
Description:Cette fonction permet de compter le nombre total des étudiants qui
appartient à une promo
*/
int NbEtudParPromo(int numPromo)
{
    LEtud *ptc;
    int i,N=0;
    for(i=0 ; i<26 ; i++)
    {
        ptc=promo[2021-numPromo][i];
        while(ptc)
        {
            N++;
            ptc=ptc->suiv;
        }
    }
    return((int)N);
}
/********************************************************************************/
/*Fonction:ChercherResuEtud
Entrées: Numero Promo, Aanne, CNE d'étudiant cherché
Sorties: __
Description:Cette fonction permet de cherche l'étudiant par son CNE et afficher
ses différentes résultats par la suite.
*/
void ChercherResuEtud(int numPromo , int annee ,char *cne)
{
    LEtud *ptc;
    int i,N=0;
    for(i=0 ; i<26 ; i++)
    {
        ptc=promo[2021-numPromo][i];
        while(ptc)
        {
            if(strcmp(ptc->Etud.cne , cne)==0)
            {
                printf("\n%s\t%s\t moyenne=%f",ptc->Etud.nom , ptc->Etud.prenom , ptc->Etud.moyenne[annee-ptc->Etud.numPromo]);
                printf("\nNombre de module valide : %d",(16-Module10et12(ptc->Etud,annee)-ModuleInf10(ptc->Etud,annee)));
                printf("\nNombre de module dont la note est entre 10 et 12 : %d",Module10et12(ptc->Etud,annee));
                printf("\nNombre de module dobt la note est inferieur a 10 : %d",ModuleInf10(ptc->Etud,annee));
                return;
            }
            ptc=ptc->suiv;
        }
    }
    printf("\nEtudiant n'existe pas");
}
/********************************************************************************/
/*Fonction:StatistModule
Entrées: Numero Promo, Aanne, module sur laquelle on va faire des statistiques
Sorties: __
Description:Cette fonction permet d'afficher les statistique sur le module
entré.
*/
void StatistModule(int numPromo , int annee ,char *mdl)
{
    int i,k,V=0,C=0,NV=0;
    LEtud *ptc;
    for(k=0 ;k<48 ;k++)
        if(strcmp(mdl,module[k])==0) break;
    for(i=0 ; i<26 ; i++)
    {
        ptc=promo[2021-numPromo][i];
        while(ptc)
        {
            if(ptc->Etud.note[k]>=12) V++;
            else
                if ((ptc->Etud.note[k]<12)&&(ptc->Etud.note[k]>=10)) C++;
                else
                    NV++;
            ptc=ptc->suiv;
        }
    }
    printf("\nLe nombre d'eleves qui ont valide le module : %d ils representent %.2f%% des etudiants",V,(float)((V*100)/NbEtudParPromo(numPromo)));
    printf("\nLe nombre d'eleves qui peuvent compenser le module : %d ils representent %.2f%% des etudiants",C,(float)((C*100)/NbEtudParPromo(numPromo)));
    printf("\nLe nombre d'eleves qui n'ont pas valide le module : %d ils representent %.2f%% des etudiants",NV,(float)((NV*100)/NbEtudParPromo(numPromo)));
}
/********************************************************************************/
/*Fonction:MoyenneGen
Entrée: listeEtud
Sorties: nombre réel indiquant la moyenne générale
Description:Cette fonction permet de calculer la moyenne générale des 3 années
*/
float MoyenneGen(LEtud *e)
{
    return((float)((e->Etud.moyenne[0]+e->Etud.moyenne[1]+e->Etud.moyenne[2])/3));
}

/********************************************************************************/
/*Fonction:TriBulle
Entrée: listeEtud
Sorties: listeetud triée par moyenne général
Description:Cette fonction permet de trier une liste des étudiants selon leurs
moyennes général
*/
LEtud * TriBulle(LEtud *l)
{
    int arr;
    etudiant tmp;
    LEtud *ptr2,*ptr;
    ptr2=NULL;
    do
    {
        arr=0;
        ptr=l;
        while(ptr->suiv!=NULL)
        {
            if(MoyenneGen(&ptr->Etud) < MoyenneGen(&ptr->suiv->Etud))
            {
                tmp=ptr->Etud;
                ptr->Etud=ptr->suiv->Etud;
                ptr->suiv->Etud=tmp;
                arr=1;
            }
            ptr=ptr->suiv;
        }
        ptr2=ptr;
        //affichePListe(l);
    }while(arr);
    return((LEtud*)l);
}


/********************************************************************************/
/*Fonction:AffichageLaureat
Entrée: __
Sorties: __
Description:Cette fonction permet d'afficher les lauréats selon l'ordre de mérite
*/
void AffichageLaureat()
{
    int i;
    LEtud *liste,*ptc;
    liste=promo[2][0];
    ptc=liste;
    for(i=1;i<26;i++)
    {
        while(ptc->suiv)
        {
            ptc=ptc->suiv;
        }
        ptc->suiv=promo[2][i];

    }
    liste=TriBulle(liste);
    while(liste)
    {
        printf("\n%s%20s%20f",liste->Etud.nom,liste->Etud.prenom,MoyenneGen(&liste->Etud));
        liste=liste->suiv;
    }
}
/********************************************************************************/
/*Fonction:estValidAnnee
Entrée: Annee, Num Promo
Sorties: 1 si l'année est valide, 0 sinon
Description:Cette fonction permet de vérifier si l'année entré est valide ou pas
*/
int estValidAnnee(int annee , int NumPromo)
{
    if(annee-NumPromo >= 0) return((int)1);
    return((int)0);
}
/********************************************************************************/
/*Fonction:choixAnnee
Entrée: Num Promo
Sorties: __
Description:Cette fonction permet de choisir une année pour le traitement
*/
void choixAnnee(int Numpromo)
{
    printf("\n\tEntrer une annee valide (");
    switch(Numpromo)
    {
        case 2019 : printf("2019 - ");
        case 2020 : printf("2020 - ");
        case 2021 : printf("2021) :");break;
    }
}

int EstValideModule(int numpromo , char *mdl)
{
	int i;
    for(i=0 ; i<48 ; i++)
        if(strcmp(mdl , module[i])==0)
        {
            switch(numpromo)
            {
                case 2019 : if(i>=48) return((int)0);break;
                case 2020 : if(i>=32) return((int)0);break;
                case 2021 : if(i>=16) return((int)0);break;
            }
            return((int)1);
        }
    return((int)0);
}

#endif // FUNCTIONS_H_INCLUDED
