# include "biblio.h"


void init (T_Bibliotheque *ptrB)
{

ptrB->nbLivres=0;
// ou (*ptrB).nbLivres=0;
}

int ajouterLivre(T_Bibliotheque  *ptrB)
{
if (ptrB->nbLivres<CAPACITE_BIBLIO)// reste t il de la place?
	{
	saisirLivre(&(ptrB->etagere[ptrB->nbLivres]));
	ptrB->nbLivres++;
	return 1;
	}
	
	
return 0;
	
}


int  afficherBibliotheque(const T_Bibliotheque  *ptrB)
{
int i;
if(ptrB->nbLivres==0)
	return 0;
	else
		{
		for(i=0;i<ptrB->nbLivres;i++)
			{
			afficherLivre( &(ptrB->etagere[i])  );
			
			}


		
		return 1;
		}
}

int rechercherLivreTitre(T_Bibliotheque *ptrB,char* chaine)
{
	int i,count=0;
	for (i=0;i<(ptrB->nbLivres);i++){
		if (strcmp((&(ptrB->etagere[i]))->titre,chaine)==0)
		count++;
	}
return count;
}

int rechercherLivresAuteur(T_Bibliotheque *ptrB,char* chaine)
{
	int i,count=0;
	for (i=0;i<(ptrB->nbLivres);i++){
		if (strcmp((&(ptrB->etagere[i]))->auteur,chaine)==0)
		printf("-%s \n",(&(ptrB->etagere[i]))->titre);
		count++;
	}
return count;
}

int supprimerLivre(T_Bibliotheque *ptrB,char* chaine)
{
    int i=0;
    if(strcmp(chaine,"")==0)return 0;
    if(ptrB->nbLivres==0)return 0;
    else if(ptrB->nbLivres==1)
    {
        (ptrB->nbLivres)--;
        return 1;
    }
    else if(ptrB->nbLivres>1)
    {
    for(i=0;i<ptrB->nbLivres;i++)
        if(strcmp((&(ptrB->etagere[i]))->titre, chaine)==0)
        {
            strcpy((&(ptrB->etagere[i]))->auteur, (&(ptrB->etagere[ptrB->nbLivres-1]))->auteur);
            strcpy((&(ptrB->etagere[i]))->titre, (&(ptrB->etagere[ptrB->nbLivres-1]))->titre);
            strcpy((&(ptrB->etagere[i]))->code, (&(ptrB->etagere[ptrB->nbLivres-1]))->code);
            strcpy((&(ptrB->etagere[i]))->editeur, (&(ptrB->etagere[ptrB->nbLivres-1]))->editeur);
            (&(ptrB->etagere[i]))->annee = (&(ptrB->etagere[ptrB->nbLivres-1]))->annee;
            (ptrB->nbLivres)--;
            return 1;
        }
    }
    return 0;
}

int Emprunter(T_Bibliotheque *ptrb,char * livre, char* nom,char* code_l)
{
	int i;
	i=rechercherLivresAuteur(ptrb,livre);
	if (i==0)
		return 0;
	else
	{
		for(i=0;i<ptrb->nbLivres;i++){
			if((strcmp((&(ptrb->etagere[i]))->titre, livre)==0)&&(strcmp((&(ptrb->etagere[i]))->code, code_l)==0))
			{
				if (strcmp((&(ptrb->etagere[i]))->emprunteur,"")==0){
					strcpy((&(ptrb->etagere[i]))->emprunteur,nom);
					return 1;
				}
				else 
					return 0;
			}
		}
	}
	return 0;
}

int Rendre(T_Bibliotheque *ptrb,char * livre,char* code_l){
	int i;
	i=rechercherLivresAuteur(ptrb,livre);
	if (i==0)
		return 0;
	else
		for(i=0;i<ptrb->nbLivres;i++)
		{		
			if((strcmp((&(ptrb->etagere[i]))->titre, livre)==0)&&(strcmp((&(ptrb->etagere[i]))->code, code_l)==0))
			{
				strcpy((&(ptrb->etagere[i]))->emprunteur,"");
				return 1;
			}
		}
	return 0;	
}			