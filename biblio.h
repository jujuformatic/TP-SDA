#ifndef BIBLIO_H   //compilation conditionnelle
#define BIBLIO_H


#include "livre.h"

#define CAPACITE_BIBLIO 100 // nb maximum de livres ds la bibliotheque

typedef  T_livre 	T_tabloDeLivres[CAPACITE_BIBLIO];

typedef struct
{
	T_tabloDeLivres etagere;
	int nbLivres;  //nb de livres actuellement ds la bibliotheque

} T_Bibliotheque;




//prototypes

void init (T_Bibliotheque *ptrB);
int ajouterLivre(T_Bibliotheque  *ptrB);
int  afficherBibliotheque(const T_Bibliotheque  *ptrB);
int rechercherLivreTitre(T_Bibliotheque *ptrB,char* chaine);
int rechercherLivresAuteur(T_Bibliotheque *ptrB,char* chaine);
int supprimerLivre(T_Bibliotheque *ptrB,char* chaine);
int Emprunter(T_Bibliotheque *ptrb,char * livre, char* nom,char* code_l);
int Rendre(T_Bibliotheque *ptrb,char * livre,char* code_l);
#endif
