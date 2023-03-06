// TP GESTION D'UNE BIBLIOTHEQUE 
#include "biblio.h"

int menu()
{
	int choix;
// au programme du TP7 :
printf("\n\n 1 - ajouter un nouveau livre dans la bibliotheque "); 
printf("\n 2 - afficher tous les livres de la bibliotheque "); 
printf("\n 3 - rechercher un livre (par son titre)");  // il peut y avoir plusieurs livres de même titre. Dans ce cas, indiquez le nombre d'exemplaires disponibles
printf("\n 4 - rechercher et afficher tous les livres d'un auteur");
printf("\n 5 - supprimer un livre de la bibliotheque");
// si les 5 choix ci dessus sont bien codés, modifiez votre structure T_Livre et passez à 5 champs (avec cote,editeur et annee)


// au programme du TP8 :
// ajouter le champ emprunteur à votre structure T_Livre

printf("\n 6 - emprunter un livre de la bibliotheque");
printf("\n 7 - restituer/rendre un livre de la bibliotheque");
printf("\n 8 - trier les livres (par titre)");
printf("\n 9 - trier les livres (par auteur)");
printf("\n 10 - trier les livres (par annee)");

// si les 5 choix (6-10) sont bien codés, changez le type T_Emp et remplacez-le par la structure T_Emp visible dans livre.h
// vous pourrez alors faire les menus 11,12,etc...
// printf("\n 11- lister les livres disponibles "); 
// printf("\n 12 - lister les emprunts en retard "); //on suppose qu'un emprunt dure 7 jours.
// printf("\n 13 - ... imaginez vous même vos propres fonctionnalités ")

printf("\n 0 - QUITTER");
printf("\n Votre choix : ");
scanf("%d[^\n]",&choix);getchar();
return choix;


}



int main()
{
int reponse,chx;
char chaine_rep[MAX_TITRE];
char n_emp[K_MaxEmp];
char code[MAX_CODE];
T_Bibliotheque B; 
init( &B );

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
	case 0:
			printf("Fermeture du programme de traitement de bibliothèque\n");
			break;
	default:
			printf("Cette demande n'est pas valide\n");
			break;	
	}

}while(chx!=0);
return 0;

}