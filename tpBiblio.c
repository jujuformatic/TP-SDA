// TP GESTION D'UNE BIBLIOTHEQUE 
#include "biblio.h"

void chargement(T_Bibliotheque *ptrB);
void lectureFichierTXT();
void sauvegarde(T_Bibliotheque *ptrB);

int menu()
{
	int choix;

printf("\n\n 1 - ajouter un nouveau livre dans la bibliotheque"); 
printf("\n 2 - afficher tous les livres de la bibliotheque"); 
printf("\n 3 - rechercher un livre (par son titre)");  // il peut y avoir plusieurs livres de même titre. Dans ce cas, indiquez le nombre d'exemplaires disponibles
printf("\n 4 - rechercher et afficher tous les livres d'un auteur");
printf("\n 5 - supprimer un livre de la bibliotheque");
printf("\n 6 - emprunter un livre de la bibliotheque");
printf("\n 7 - restituer/rendre un livre de la bibliotheque");
printf("\n 8 - trier les livres (par titre)");
printf("\n 9 - trier les livres (par auteur)");
printf("\n 10 - trier les livres (par annee)");
printf("\n 11- lister les livres disponibles"); 
printf("\n 12 - lister les emprunts en retard"); //on suppose qu'un emprunt dure 7 jours.
//printf("\n 13 - ... imaginez vous même vos propres fonctionnalités ")

printf("\n 0 - QUITTER");
printf("\n Votre choix : ");
scanf("%d[^\n]",&choix);getchar();
return choix;
}

int main()
{
lectureFichierTXT();
int reponse,chx;
char chaine_rep[MAX_TITRE];
char n_emp[K_MaxEmp];
char code[MAX_CODE];
T_Bibliotheque B; 
init( &B );
chargement(&B);
do
{
chx= menu();
switch(chx)
	{
	case  1 : reponse = ajouterLivre(   &B  );
			if (reponse==1)
				printf(" ajout reussi !!\n");
				else
				printf("impossible d ajouter (bibliotheque pleine)\n");
			break;

	case 2 : reponse=afficherBibliotheque(&B);
			if (reponse==0)	
				printf("La bibliotheque est vide\n");
			break;

	case 3: 
			printf("Rentrez le titre du livre que vous souhaitez rechercher: ");
			lireChaine("",chaine_rep,MAX_TITRE);
			printf("\nLivre recherché: %s\n", chaine_rep);
			reponse=rechercherLivreTitre(&B, chaine_rep);
			if(reponse==0)
				printf("Le livre n'est pas présent dans la bibliothèque\n");
				else
				printf("Le livre est présent en %d exemplaires dans la bibliothèque\n", reponse);
			break;

	case 4: 
			printf("Rentrez le nom de l'auteur dont vous voulez la liste des oeuvres: ");
			lireChaine("",chaine_rep,MAX_TITRE);
			printf("\nListe des livres de %s :\n", chaine_rep);
			reponse=rechercherLivresAuteur(&B, chaine_rep);
			if (reponse==0)	
				printf("La bibliothèque ne contient aucun livre de cet auteur\n");
			break;

	case 5: 
			printf("Rentrez le titre du livre que vous souhaitez supprimer: ");
			lireChaine("",chaine_rep,MAX_TITRE);
			printf("\nLivre à supprimer: %s\n", chaine_rep);
			reponse=supprimerLivre(&B, chaine_rep);
			if (reponse==0)	
				printf("Ce livre n'est pas dans la bibliothèque\n");
				else
				printf("Suppression réussie du livre de la bibliothèque\n");
			break;

	case 6:
			printf("Rentrez le titre du livre que vous souhaitez emprunter ");
			lireChaine("",chaine_rep,MAX_TITRE);
			printf("Rentrez le code du livre que vous souhaitez emprunter ");
			lireChaine("",code,MAX_CODE);
			printf("Rentrez le nom de l'emprunteur ");
			lireChaine("",n_emp,K_MaxEmp);
			reponse=Emprunter(&B,chaine_rep,n_emp,code);
			if (reponse==0)
				printf("Emprunt impossible");
			else 
				printf("Emprunt réussit");
			break;
		
	case 7:
			printf("Rentrez le titre du livre que vous souhaitez rendre ");
			lireChaine("",chaine_rep,MAX_TITRE);
			printf("Rentrez le code du livre que vous souhaitez emprunter ");
			lireChaine("",code,MAX_CODE);
			reponse=Rendre(&B,chaine_rep,code);
			if (reponse==0)
				printf("Retour impossible");
			else 
				printf("Retour Réussit");
			break;

	case 8:
			printf("Tri des livres dans la bibliothèque par titre\n");
			triTitre(&B);
			printf("Nouveau tri de la biliothèque:\n");
			afficherBibliotheque(&B);
			break;

	case 9:
			printf("Tri des livres dans la bibliothèque par auteur\n");
			triAuteur(&B);
			printf("Nouveau tri de la biliothèque:\n");
			afficherBibliotheque(&B);
			break;

	case 10:
			printf("Tri des livres dans la bibliothèque par année\n");
			triAnnee(&B);
			printf("Nouveau tri de la biliothèque:\n");
			afficherBibliotheque(&B);
			break;

	case 11:
			printf("liste des livres disponibles \n");
			ListerLibre(&B);
			break;

	case 12:
			printf("liste des livres avec un emprunt en retard\n");
			ListerRetard(&B);
			break;

	case 0:
			printf("Fermeture du programme de traitement de bibliothèque\n");
			break;
	default:
			printf("Cette demande n'est pas valide\n");
			break;	
	}

}while(chx!=0);
sauvegarde(&B);

return 0;

}



void sauvegarde(T_Bibliotheque *ptrB)
{
FILE *fic=NULL; //le type FILE
int i;
fic=fopen("baseLivres","w"); // w = le mode = write avec ECRASEMENT
//fopen renvoie NULL si probleme (disque plein, disque non accessible ...
if (fic!=NULL)
	{
	for(i=0;i<ptrB->nbLivres;i++)
		{
    //fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    fwrite(  &(ptrB->etagere[i])        ,sizeof(T_livre),1,fic);

		}
	fclose(fic);
	puts("SAUVEGARDE REUSSIE ..............");



	}
	else puts("ECHEC DE SAUVEGARDE  !!!!!  ");

}

void lectureFichierTXT()
{
int M=100;
FILE *fic=NULL; //le type FILE
char chaine[M];
char chaine2[M];
char c;
fic=fopen("fic.txt","rt"); // r = le mode read   w = mode write (avec ecrasement)
//fopen renvoie NULL si probleme (fichier effac� , disque non accessible ...
if (fic!=NULL)
	{
	do
		{
		fgets(chaine,M,fic);   //fputs pour �crire dans un fichier txt
		fprintf(fic,"%s",chaine); //fprintf pour �crire dans un fichier txt
	    fscanf(fic,"%s %s",chaine,chaine2);
		fscanf(fic,"%c",&c);
		fscanf(fic,"%c",&chaine[0]);
	if (!feof(fic))
           printf("\n\t >%s--%s<",chaine,chaine2);
        printf(">%c<",c);
		}
    while(!feof(fic));
	fclose(fic);
	puts("\nLECTURE REUSSIE ..............");
	}
	else puts("ECHEC DE LECTURE DU FICHIER TXT !!!!!  ");
}

void chargement(T_Bibliotheque *ptrB)
{
FILE *fic=NULL; //le type FILE
int i=0;
fic=fopen("baseLivres","r"); // r = le mode read
//fopen renvoie NULL si probleme (disque plein, disque non accessible ...
if (fic!=NULL)
	{
	do
		{

		fread(  &(ptrB->etagere[i]) ,sizeof(T_livre),1,fic);
		i++;
		}
		while(!feof(fic));
	fclose(fic);
	ptrB->nbLivres=i-1;
	puts("CHARGEMENT  REUSSI ..............");
	}
	else puts("ECHEC DE CHARGEMENT  !!!!!  ");

}
