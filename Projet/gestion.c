#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2000
#define MAX_ETUDIANTS 1000
#define MAX_UNIVERSITIES 12
#define MAX_FACULTIES 10


typedef struct
{
    char dossier[50]; // numéro du dossier de l'étudiant
    char prenom[50]; // prénom de l'étudiant
    char nom[50]; // nom de famille de l'étudiant
    char email[50]; // adresse e-mail de l'étudiant
    char cne[50]; // code national de l'étudiant
    char cin[50]; // carte d'identité nationale de l'étudiant
    char date_naissance[50]; // date de naissance de l'étudiant
    char lieu_naissance[50]; // lieu de naissance de l'étudiant
    char nationalite[50]; // nationalité de l'étudiant
    char sexe[10]; // sexe de l'étudiant
    char telephone[50]; // numéro de téléphone de l'étudiant
    char adresse[100]; // adresse de l'étudiant
    char bac[50]; // type de baccalauréat de l'étudiant
    char mention_bac[50]; // mention au baccalauréat de l'étudiant
    int annee_bac; // année d'obtention du baccalauréat
    char lycee_bac[100]; // lycée d'obtention du baccalauréat
    char ville_bac[50]; // ville où se situe le lycée d'obtention du baccalauréat
    char niveau_diplome[50]; // niveau de diplôme de l'étudiant
    char type_diplome[50]; // type de diplôme de l'étudiant (Bac+2 ou Bac+3)
    char intitule_diplome[100]; // intitulé du diplôme de l'étudiant
    char option_diplome[50]; // option du diplôme de l'étudiant
    char universite[100]; // université où l'étudiant a obtenu son diplôme
    char faculte[100]; // faculté où l'étudiant a obtenu son diplôme
    int annee_diplome; // année d'obtention du diplôme de l'étudiant
    int ann_univ_diplome; // année universitaire d'obtention du diplôme de l'étudiant
    float notes[6]; // notes de l'étudiant
    float moyenne_s1_s2_s3_s4; // moyenne de l'étudiant pour les semestres S1, S2, S3 et S4
    float moyenne_s5_s6; // moyenne de l'étudiant pour les semestres S5 et S6

} Etudiant;



typedef struct cel
{
    Etudiant Etud;
    struct cel *suiv; /// pointeur vers le prochain Etudiant

} LEtud;


typedef struct diploma
{
    char name[100]; /// nom du diplôme
    struct LEtud* Etud; /// pointeur vers la liste des étudiants
    struct diploma* next;/// pointeur vers le prochain diplôme

} Diploma;

typedef struct faculty
{
    char name[100];     /// nom de la faculté
    struct diploma* diplomas; /// pointeur vers la liste des diplômes
    struct faculty* next; /// pointeur vers la prochaine faculté

} Faculty;

typedef struct university
{
    char name[100];     /// nom de l'université
    struct faculty* faculties; /// pointeur vers la liste des facultés
    struct university* next; /// pointeur vers la prochaine université

} University;

typedef struct database
{
    struct university* universities; /// pointeur vers la liste des universités

} Database;



const char universities_Faculty[MAX_UNIVERSITIES][MAX_FACULTIES][100] =
{
    // 0: UNIVERSITE HASSAN II DE CASABLANCA :
    {
        "FACULTE DES SCIENCES ET TECHNIQUES DE MOHAMMEDIA",
        "FACULTE DES SCIENCES AIN CHOCK CASABLANCA",
        "FACULTE DES SCIENCES BEN M`SIK CASABLANCA",
        "ECOLE SUPERIEURE DE TECHNOLOGIE CASABLANCA",
        "ECOLE NORMALE SUPERIEUR CASABLANCA"
    },

    // 1 : UNIVERSITE MOHAMMED V DE RABAT :
    {
        "FACULTE DES SCIENCES DE RABAT",
        "ECOLE SUPERIEURE DE TECHNOLOGIE SALE",
        "ECOLE NORMALE SUPERIEURE RABAT",
        "Ecole Normale Superieure de l'Enseignement Technique Rabat"
    },

    // 2: UNIVERSITE MOHAMMED 1ER OUJDA",
    {
        "FACULTE DES SCIENCES OUJDA",
        "ECOLE SUPERIEURE DE TECHNOLOGIE OUJDA",
        "FACULTE POLYDICIPLINAIRE DE NADOR",
    },
    // 3: UNIVERSITE ABDELMALEK ESSAADI TANGER
    {
        "FACULTE DES SCIENCES ET TECHNIQUES TANGER",
        "FACULTE DES SCIENCES TETOUAN",
        "ECOLE NORMALE SUPERIEURE TETOUAN",
        "FACULTE DES SCIENCES ET TECHNIQUES AL-HOCEIMA",
    },
    // 4 : UNIVERSITE CADI AYYAD MARRAKECH
    {
        "FACULTE DES SCIENCES SEMLALIA MARRAKECH",
        "FACULTE DES SCIENCES ET TECHNIQUES GUELIZ MARRAKECH",
        "ECOLE NORMALE SUPERIEUR MARRAKECH",
        "FACULTE PLOYDISCIPLINAIRE DE SAFI",
        "ECOLE SUPERIEURE DE TECHNOLOGIE SAFI",
        "ECOLE SUPERIEUR DE TECHNOLOGIE ESSAOUIRA"
    },
    // 5 : UNIVERSITE SIDI MOHAMMED BEN ABDELLAH FES
    {
        "FACULTE POLYDISCIPLINAIRE DE TAZA",
        "FACULTE DES SCIENCES FES",
        "FACULTE DES SCIENCES ET TECHNIQUES FES",
        "ECOLE SUPERIEURE DE TECHNOLOGIE FES",
        "ECOLE NORMALE SUPERIEURE FES"
    },
    // 6:UNIVERSITE HASSAN 1ER SETTAT
    {
        "FACULTE DES SCIENCES ET TECHNIQUES DE SETTAT",
        "ECOLE SUPERIEURE DE TECHNOLOGIE DE BERRECHID",
        "ECOLE NATIONALE DES SCIENCES APPLIQUEES BERRECHID"
    },
    // 7:UNIVERSITE IBN TOFAIL KENITRA
    {
        "FACULTE DES SCIENCES DE KENITRA",
        "ECOLE SUPERIEURE DE TECHNOLOGIE KENITRA",
    },
    // 8 : UNIVERSITE IBN ZOHR AGADIR
    {
        "FACULTE DES SCIENCES DE AGADIR",
        "ECOLE SUPERIEURE DES TECHNOLOGIES APPLIQUEES DE AGADIR",
        "ECOLE SUPERIEURE DE TECHNOLOGIE D'AGADIR",
        "FACULTE POLYDISCIPLINAIRE DE OUARZAZATE",
        "FACULTE POLYDISCIPLINAIRE DE TAROUDANTE",
        "ECOLE SUPERIEURE DE TECHNOLOGIE TAROUDANT",
        "ECOLE SUPERIEURE DE TECHNOLOGIE DE LAAYOUNE",
        "ECOLE SUPERIEURE DE TECHNOLOGIE DE GUELMIM",
        "FACULTE DES SCIENCES APPLIQUE AIT MELLOUL"
    },
    // 9 : UNIVERSITE MOULAY ISMAIL MEKNES
    {
        "FACULTE DES SCIENCES DE MEKNES",
        "FACULTE DES SCIENCES ET TECHNIQUES DE ERRACHIDIA",
        "ECOLE NATIONALE SUPERIEURE DES ARTS ET METIERS DE MEKNES",
        "ECOLE SUPERIEURE DE TECHNOLOGIE DE MEKNES"
    },
    // 10 : "UNIVERSITE CHOUAIB DOUKKALI EL JADIDA"
    {
        "FACULTE DES SCIENCES EL JADIDA",
        "ECOLE NATIONALE DES SCIENCES APPLIQUEES EL JADIDA",
        "ECOLE SUPERIEUR DE TECHNOLOGIE SIDI BENNOUR"
    },
    // 11 :  "UNIVERSITE SULTAN MOULAY SLIMANE BENI MELLAL"
    {
        "FACULTE DES SCIENCES ET TECHNIQUE DE BENI MELLAL",
        "ECOLE SUPERIEURE DE TECHNOLOGIE DE BENI MELLAL",
        "ECOLE SUPERIEURE DE TECHNOLOGIE DE KHENIFRA"
    }
};



void afficher()
{
    for(int i = 0; i < MAX_UNIVERSITIES; i++)
    {
        printf("Universite %d :\n", i);
        for(int j = 0; j < MAX_FACULTIES; j++)
        {
            if(strcmp(universities_Faculty[i][j], "") != 0)
            {
                printf("- %s\n", universities_Faculty[i][j]);
            }
        }
        printf("\n");
    }
}






char *replaceDoubleSemicolon(char *str) {

    int len = strlen(str);
    int i;

    for (i = 0; i < len - 1; i++) {
        if (str[i] == ',' && str[i + 1] == ',') {
            memmove(str + i + 2, str + i + 1, len - i);
            str[i + 1] = ' ';
            len++;
            i++;
        }
    }
    return str;
}



void lecture_fich_trans_bdd()
{
    FILE* fichier = fopen("Candidat.csv", "r"); // Ouverture du fichier en mode lecture
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char ligne[MAX_LINE_LENGTH];
    Etudiant e;
    Database db;
    db.universities = NULL;
    fgets(ligne, sizeof(ligne), fichier); // Ignorer la première ligne Header
    while( fgets(ligne, sizeof(ligne), fichier))
    {


        char* modified_line = replaceDoubleSemicolon(ligne);


        // pour chaque ligne:
        char* dossier = strtok(modified_line, ",");
        char* prenom = strtok(NULL, ",");
        char* nom = strtok(NULL, ",");
        char* email = strtok(NULL, ",");
        char* cne = strtok(NULL, ",");
        char* cin = strtok(NULL, ",");
        char* date_naissance = strtok(NULL, ",");
        char* lieu_naissance = strtok(NULL, ",");
        char* nationalite = strtok(NULL, ",");
        char* sexe = strtok(NULL, ",");
        char* telephone = strtok(NULL, ",");
        char* adresse = strtok(NULL, ",");
        char* bac = strtok(NULL, ",");
        char* mention_bac = strtok(NULL, ",");
        int annee_bac = atoi(strtok(NULL, ","));
        char* lycee_bac = strtok(NULL, ",");
        char* ville_bac = strtok(NULL, ",");
        char* niveau_diplome = strtok(NULL, ",");
        char* type_diplome = strtok(NULL, ",");
        char* intitule_diplome = strtok(NULL, ",");
        char* option_diplome = strtok(NULL, ",");
        char* universite = strtok(NULL, ",");
        char* faculte = strtok(NULL, ",");
        int annee_diplome = atoi(strtok(NULL, ","));
        int ann_univ_diplome = atoi(strtok(NULL, ","));




        ///Les champs extraits sont stockés dans une structure Etudiant
        strcpy(e.dossier, dossier);
        strcpy(e.prenom, prenom);
        strcpy(e.nom, nom);
        strcpy(e.email, email);
        strcpy(e.cne, cne);
        strcpy(e.cin, cin);
        strcpy(e.date_naissance, date_naissance);
        strcpy(e.lieu_naissance, lieu_naissance);
        strcpy(e.nationalite, nationalite);
        strcpy(e.sexe, sexe);
        strcpy(e.telephone, telephone);
        strcpy(e.adresse, adresse);
        strcpy(e.bac, bac);
        strcpy(e.mention_bac, mention_bac);
        e.annee_bac = annee_bac;
        strcpy(e.lycee_bac, lycee_bac);
        strcpy(e.ville_bac, ville_bac);
        strcpy(e.niveau_diplome, niveau_diplome);
        strcpy(e.type_diplome, type_diplome);
        strcpy(e.intitule_diplome, intitule_diplome);
        strcpy(e.option_diplome, option_diplome);
        strcpy(e.universite, universite);
        strcpy(e.faculte, faculte);
        e.annee_diplome = annee_diplome;
        e.ann_univ_diplome = ann_univ_diplome;

        int i;
        for (i = 0; i < 6; i++)
        {
            e.notes[i] = atof(strtok(NULL, ","));
        }
        e.moyenne_s1_s2_s3_s4 = atof(strtok(NULL, ","));
        e.moyenne_s5_s6= atof(strtok(NULL, ","));

        /// ajouter l'étudiant à la base de données.
        add_student_to_database(&db, e);


    }

    print_database_csv(db.universities);
}





int add_student_to_database(Database* db, Etudiant e)
{
    if(!db)
    {
        return((int)-1);
    }
    /// Vérifiez si le nom de l'université, le nom de la faculté et le nom du diplôme de l'étudiant saisi ne sont pas des chaînes nulles ou vides
    if (!e.universite || strlen(e.universite) == 0 || !e.faculte || strlen(e.faculte) == 0 || !e.niveau_diplome || strlen(e.niveau_diplome) == 0)
    {
        return ((int)-2);
    }
    /// Trouvez la bonne université ou créez-la si elle n'existe pas
    University* univ = db->universities;
    while (univ != NULL && strcmp(univ->name, e.universite) != 0)
    {
        univ = univ->next;
    }
    if (univ == NULL)
    {
        /// L'université n'existe pas, alors créez-la
        univ = (University*)malloc(sizeof(University));
        strcpy(univ->name, e.universite);
        univ->faculties = NULL;
        univ->next = db->universities;
        db->universities = univ;
    }

    /// Trouvez la bonne faculté au sein de l'université ou créez-la si elle n'existe pas
    Faculty* faculty = univ->faculties;
    while (faculty != NULL && strcmp(faculty->name, e.faculte) != 0)
    {
        faculty = faculty->next;
    }
    if (faculty == NULL)
    {
        /// Faculty n'existe pas, alors créez-la
        faculty = (Faculty*)malloc(sizeof(Faculty));
        strcpy(faculty->name, e.faculte);
        faculty->diplomas = NULL;
        faculty->next = univ->faculties;
        univ->faculties = faculty;
    }

    /// Trouver le bon diplôme au sein de la faculté ou le créer s'il n'existe pas
    Diploma* diploma = faculty->diplomas;
    while (diploma != NULL && strcmp(diploma->name, e.niveau_diplome) != 0)
    {
        diploma = diploma->next;
    }
    if (diploma == NULL)
    {
        /// Diploma n'existe pas, alors créez-la
        diploma = (Diploma*)malloc(sizeof(Diploma));
        strcpy(diploma->name, e.niveau_diplome);
        diploma->Etud = NULL;
        diploma->next = faculty->diplomas;
        faculty->diplomas = diploma;
    }

    /// Ajouter l'étudiant à la liste des étudiants pour ce diplôme
    LEtud* new_student = (LEtud*)malloc(sizeof(LEtud));
    new_student->Etud = e;
    new_student->suiv = diploma->Etud;
    diploma->Etud = new_student;

    return 1;
}



LEtud * TriBulle_Bac2(LEtud *l)
{
    int arr;
    Etudiant tmp;
    LEtud *ptr2,*ptr;
    ptr2=NULL;
    do
    {
        arr=0;
        ptr=l;
        while(ptr->suiv != NULL)
        {
            if(ptr->Etud.moyenne_s1_s2_s3_s4 <  ptr->suiv->Etud.moyenne_s1_s2_s3_s4 )
            {
                tmp=ptr->Etud;
                ptr->Etud=ptr->suiv->Etud;
                ptr->suiv->Etud=tmp;
                arr=1;
            }
            ptr=ptr->suiv;
        }
        ptr2=ptr;

    }
    while(arr);

    return((LEtud*)l);
}


LEtud * TriBulle_Bac3(LEtud *l)
{
    int arr;
    Etudiant tmp;
    LEtud *ptr2,*ptr;
    ptr2=NULL;
    do
    {
        arr=0;
        ptr=l;
        while(ptr->suiv != NULL)
        {
            if(ptr->Etud.moyenne_s5_s6 <  ptr->suiv->Etud.moyenne_s5_s6)
            {
                tmp=ptr->Etud;
                ptr->Etud=ptr->suiv->Etud;
                ptr->suiv->Etud=tmp;
                arr=1;
            }
            ptr=ptr->suiv;
        }
        ptr2=ptr;

    }
    while(arr);

    return((LEtud*)l);
}


int verification(char universite[100], char faculte[100])
{
    int i, j;
    char* universities[MAX_UNIVERSITIES] =
    {
        "UNIVERSITE HASSAN II DE CASABLANCA",
        "UNIVERSITE MOHAMMED V RABAT",
        "UNIVERSITE MOHAMMED 1ER OUJDA",
        "UNIVERSITE ABDELMALEK ESSAADI TANGER",
        "UNIVERSITE CADI AYYAD MARRAKECH",
        "UNIVERSITE SIDI MOHAMMED BEN ABDELLAH FES",
        "UNIVERSITE HASSAN 1ER SETTAT",
        "UNIVERSITE IBN TOFAIL KENITRA",
        "UNIVERSITE IBN ZOHR AGADIR",
        "UNIVERSITE MOULAY ISMAIL MEKNES",
        "UNIVERSITE CHOUAIB DOUKKALI EL JADIDA",
        "UNIVERSITE SULTAN MOULAY SLIMANE BENI MELLAL"
    };

    for (i = 0; i < MAX_UNIVERSITIES; i++)
    {
        if (strcasecmp(universite, universities[i]) == 0)
        {
            for (j = 0; j < MAX_FACULTIES; j++)
            {
                if (strcasecmp(universities_Faculty[i][j], faculte) == 0)
                {
                    return 1;
                }
            }
            return -1;
        }
    }
    return -1;
}



int print_database_csv(University *Pliste)
{
    University *univ = Pliste;
    Faculty *faculty;
    Diploma *diploma;
    LEtud *student;

    if (!univ)
    {
        printf("Erreur: la liste n'existe pas\n");
        return -1;
    }

    /// Parcourir la liste des universités
    while (univ)
    {
        /// Parcourir la liste des faculties de chaque université
        faculty = univ->faculties;
        while (faculty)
        {
            /// Parcourir la liste des diplômes de chaque faculté
            diploma = faculty->diplomas;
            while (diploma)
            {
                /// Obtenez la liste des étudiants pour chaque université, faculté et diplôme
                student = diploma->Etud;

                /// Trier la liste des étudiants par  moyennes
                if (strcmp(student->Etud.niveau_diplome, "Bac+2") == 0)
                {
                    // Le tri par moyenne_s1_s2_s3_s4
                    student = TriBulle_Bac2(student);
                }
                else if (strcmp(student->Etud.niveau_diplome, "Bac+3") == 0)
                {
                    // Le tri par moyenne_s5_s6
                    student = TriBulle_Bac3(student);
                }
                else // il existe des cas de Bac+5
                {
                    student = TriBulle_Bac3(student);
                }

                /// La Vérification de l'University Et la Faculty
                int correct = verification(univ->name, faculty->name);
                if(correct == 1)
                {
                    FILE *fp;
                    char filename[100];
                    sprintf(filename, "%s.csv", student->Etud.dossier);
                    fp = fopen(filename, "a");

                    /// Écrit l'en-tête du fichier CSV
                    fprintf(fp, "No DOSSIER,PRENOM,NOM,EMAIL,CNE/Code MASSAR,CIN,DATE DE NAISSANCE,LIEU DE NAISSANCE,NATIONALITE,SEXE,TELEPHONE,ADRESSE,BAC,MENTION BAC,ANNEE BAC,LYCEE BAC,VILLE BAC,NIVEAU DIPLOME (Dernier diplome),TYPE DIPLOME (Dernier diplome),INTITULE DIPLOME (Dernier diplome),OPTION DIPLOME (Dernier diplome),UNIVERSITE (Dernier diplome),FACULTE (Dernier diplome),ANNEE DIPLOME (Dernier diplome),ANN UNIV DIPLOME (Dernier diplome),NOTE S1,NOTE S2,NOTE S3,NOTE S4,NOTE S5,NOTE S6,MOYENNE_S1_S2_S3_S4,MOYENNE_S5_S6\n");

                    /// Parcourir la liste des étudiants et écrire les données de chaque étudiant dans le fichier CSV
                    while (student)
                    {
                        /// Écrire les données des étudiants dans le fichier CSV
                        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f\n",
                                student->Etud.dossier,
                                student->Etud.prenom,
                                student->Etud.nom,
                                student->Etud.email,
                                student->Etud.cne,
                                student->Etud.cin,
                                student->Etud.date_naissance,
                                student->Etud.lieu_naissance,
                                student->Etud.nationalite,
                                student->Etud.sexe,
                                student->Etud.telephone,
                                student->Etud.adresse,
                                student->Etud.bac,
                                student->Etud.mention_bac,
                                student->Etud.annee_bac,
                                student->Etud.lycee_bac,
                                student->Etud.ville_bac,
                                student->Etud.niveau_diplome,
                                student->Etud.type_diplome,
                                student->Etud.intitule_diplome,
                                student->Etud.option_diplome,
                                student->Etud.universite,
                                student->Etud.faculte,
                                student->Etud.annee_diplome,
                                student->Etud.ann_univ_diplome,
                                student->Etud.notes[0],
                                student->Etud.notes[1],
                                student->Etud.notes[2],
                                student->Etud.notes[3],
                                student->Etud.notes[4],
                                student->Etud.notes[5],
                                student->Etud.moyenne_s1_s2_s3_s4,
                                student->Etud.moyenne_s5_s6);

                        student = student->suiv;
                    }
                    fclose(fp);
                }
                else
                {
                    /// les données erronées doivent être stockées dans un autre fichier CSV distinct
                    FILE *autre;
                    autre = fopen("Autre.csv", "a");
                    while (student)
                    {
                        /// Stockage Dans Le Fichier 'Autre'
                        fprintf(autre, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f\n",
                                student->Etud.dossier,
                                student->Etud.prenom,
                                student->Etud.nom,
                                student->Etud.email,
                                student->Etud.cne,
                                student->Etud.cin,
                                student->Etud.date_naissance,
                                student->Etud.lieu_naissance,
                                student->Etud.nationalite,
                                student->Etud.sexe,
                                student->Etud.telephone,
                                student->Etud.adresse,
                                student->Etud.bac,
                                student->Etud.mention_bac,
                                student->Etud.annee_bac,
                                student->Etud.lycee_bac,
                                student->Etud.ville_bac,
                                student->Etud.niveau_diplome,
                                student->Etud.type_diplome,
                                student->Etud.intitule_diplome,
                                student->Etud.option_diplome,
                                student->Etud.universite,
                                student->Etud.faculte,
                                student->Etud.annee_diplome,
                                student->Etud.ann_univ_diplome,
                                student->Etud.notes[0],
                                student->Etud.notes[1],
                                student->Etud.notes[2],
                                student->Etud.notes[3],
                                student->Etud.notes[4],
                                student->Etud.notes[5],
                                student->Etud.moyenne_s1_s2_s3_s4,
                                student->Etud.moyenne_s5_s6);

                        student = student->suiv;
                    }
                    fclose(autre);
                }
                diploma = diploma->next;
            }
            faculty = faculty->next;
        }
        univ = univ->next;
    }

    return 1;
}



int main()
{
    lecture_fich_trans_bdd();
    return 0;
}
















