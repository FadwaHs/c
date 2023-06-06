#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"functions.h"

void main()
{
    initpromo();
    lecture_fich_trans_bdd();
    int i,j,k,annee;
    char cne[11],mdl[26];

    printf("\t\t\t\tGestion des 3 promos ILISI 2019-2020-2021");
    printf("\n\n\t1- Une Gestion par promotion ilisi");
    printf("\n\t2-Afficher les etudiants de toutes les promos\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1:
        {
            do
            {
                printf("\n\tChoix de la promo:");
                printf("\n Promo 2019");
                printf("\n Promo 2020");
                printf("\n Promo 2021\n");
                scanf("%d",&j);
            }while((j!=2019)&&(j!=2020)&&(j!=2021));
            printf("\n\t\t***Promo %d***",j);
            do
            {
                affecterMoyenne(j);
                printf("\n\t1-Afficher tous les etudiants de la promo par ordre alphabetique.");
                printf("\n\t2-Afficher tous les etudiants qui ont reussi l'annee.");
                printf("\n\t4-Afficher tous les etudiants qui ont rate l'annee.");
                printf("\n\t7-Afficher les statistiques sur les modules.\n\t");
                if(j==2019) printf("8-Afficher tous les laureats par ordre de merite sur 3 annees\n\t");
                scanf("%d",&k);
                switch(k)
                {
                    case 1: affichePromo(j);break;
                    case 2:
                    {
                        do
                        {
                            choixAnnee(j);
                            scanf("%d",&annee);
                        }while(!estValidAnnee(annee,j));

                        afficheValide(j,annee);
                    };break;
                    case 3:
                    {
                        do
                        {
                            choixAnnee(j);
                            scanf("%d",&annee);
                        }while(!estValidAnnee(annee,j));
                        printf("le nombre des etudiants qui ont validé est %d",NbEtudValid(j,annee));
                        printf("\nIls represente %.2f%% des etudiants ",
                                        (float)((NbEtudValid(j,annee)*100)/NbEtudParPromo(j)));
                    }break;
                    case 4:
                    {
                        do
                        {
                            choixAnnee(j);
                            scanf("%d",&annee);
                        }while(!estValidAnnee(annee,j));
                        afficheEchoue(j,annee);
                    }break;
                    case 5:
                    {
                        do
                        {
                            choixAnnee(j);
                            scanf("%d",&annee);
                        }while(!estValidAnnee(annee,j));
                        printf("le nombre des etudiants qui ont echoue est %d",NbEtudEchoue(j,annee));
                        printf("\nIls represente %.2f%% des etudiants ",
                                    (float)((NbEtudEchoue(j,annee)*100)/NbEtudParPromo(j)));
                    }break;
                    case 6:
                    {
                        do
                        {
                            choixAnnee(j);
                            scanf("%d",&annee);
                        }while(!estValidAnnee(annee,j));
                        printf("\n\tEntrer le cne de l'etudiant");
                        scanf("%s",cne);
                        ChercherResuEtud(j,annee,cne);
                    }break;
                    case 7:
                    {
                        do
                        {
                            choixAnnee(j);
                            scanf("%d",&annee);
                        }while(!estValidAnnee(annee,j));
                        do
                        {
                            printf("\n\tEntrer le nom du module : ");
                            scanf("%s",mdl);
                        }while(!EstValideModule(j,mdl));
                        StatistModule(j,annee,mdl);
                    }break;
                    case 8: AffichageLaureat();break;
                }
            }while(k!=0);
        }break;
        case 2 :
        {
            printf("\n**Promo 2019**\n");
            affichePromo(2019);
            printf("\n**Promo 2020**\n");
            affichePromo(2020);
            printf("\n**Promo 2021**\n");
            affichePromo(2021);
        }
    }
}
