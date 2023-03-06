# include "biblio.h"

#define AVANT -1
#define APRES 1

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


int afficherBibliotheque(const T_Bibliotheque  *ptrB)
{
int i;
if(ptrB->nbLivres==0)
	return 0;
	else
		{
		for(i=0;i<ptrB->nbLivres;i++)
			{
			afficherLivreDet( &(ptrB->etagere[i])  );
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
	if (i==0) return 0;
	else
	{
		for(i=0;i<ptrb->nbLivres;i++){
			if((strcmp((&(ptrb->etagere[i]))->titre, livre)==0)&&(strcmp((&(ptrb->etagere[i]))->code, code_l)==0))
			{
				if (strcmp((&(ptrb->etagere[i]))->emprunteur.nomemprunteur,"")==0)
				{
					strcpy((&(ptrb->etagere[i]))->emprunteur.nomemprunteur,nom);
					lireDateSysteme(&(ptrb->etagere[i].emprunteur));
					(&(ptrb->etagere[i]))->secondsSince1970=time(NULL);
					return 1;
				}
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
					strcpy((&(ptrb->etagere[i]))->emprunteur.nomemprunteur,"");
				return 1;
			}
		}
	return 0;	
}	


int triTitre(T_Bibliotheque  *ptrB){
	int i,j=0;
	int ordre;
	T_livre aux;

	for(i=0;i<ptrB->nbLivres-1;i++){
		for(j=0;j<ptrB->nbLivres-1;j++){
			ordre=compareChaines(ptrB->etagere[j].titre, ptrB->etagere[j+1].titre);
			if(ordre==APRES){ //Le livre en i se place après celui en i+1
				aux = ptrB->etagere[j]; 
				ptrB->etagere[j] = ptrB->etagere[j+1];
				ptrB->etagere[j+1] = aux;
			}
		}
	}
return 0;
}

int triAuteur(T_Bibliotheque  *ptrB){
	int i,j=0;
	int ordre;
	T_livre aux;

	for(i=0;i<ptrB->nbLivres-1;i++){
		for(j=0;j<ptrB->nbLivres-1;j++){
			ordre=compareChaines(ptrB->etagere[j].auteur, ptrB->etagere[j+1].auteur);
			if(ordre==APRES){ //Le livre en i se place après celui en i+1
				aux = ptrB->etagere[j]; 
				ptrB->etagere[j] = ptrB->etagere[j+1];
				ptrB->etagere[j+1] = aux;
			}
		}
	}
return 0;
}

int triAnnee(T_Bibliotheque  *ptrB){
	int i,j=0;
	T_livre aux;

	for(i=0;i<ptrB->nbLivres-1;i++){
		for(j=0;j<ptrB->nbLivres-1;j++){
			if(ptrB->etagere[j].annee > ptrB->etagere[j+1].annee){ //Le livre en i se place après celui en i+1
				aux = ptrB->etagere[j]; 
				ptrB->etagere[j] = ptrB->etagere[j+1];
				ptrB->etagere[j+1] = aux;
			}
		}
	}
return 0;
}

int compareChaines(char* chaineA, char* chaineB){
	int i=0;

	do {
		if(chaineA[i]-chaineB[i]>0) return APRES; //Exemple: on compare A(ab) et B(aa): a-a=0 donc on continue la boucle
		if(chaineA[i]-chaineB[i]<0) return AVANT;  //ensuite b-a=1>0 donc la chaine A se place après la B par tri croissant 
		i++;
	} while(chaineA[i-1]!='\0');
return 0;
}

void echangeLivres(T_livre livreA, T_livre livreB){
	T_livre aux;
	aux=livreA;
	livreA=livreB;
	livreB=aux;
}

void afficherLivreDet(const T_livre *L)
{

char jour[13],mois[13];

printf("\n titre du livre : %s",L->titre);

if (strcmp(L->emprunteur.nomemprunteur,"")==0)
	printf("\n  Livre disponible");
else{
printf("\n  Emprunteur du livre : %s",L->emprunteur.nomemprunteur);

printf("\n   Emprunté depuis le : ");
switch(L->emprunteur.lejour)
{
case 0 :  strcpy(jour,"lundi");break;
case 1 :  strcpy(jour,"mardi");break;
case 2 :  strcpy(jour,"mercredi");break;
case 3 :  strcpy(jour,"jeudi");break;
case 4 :  strcpy(jour,"vendredi");break;
case 5 :  strcpy(jour,"samedi");break;
case 6 :  strcpy(jour,"dimanche");break;

default : strcpy(jour,"jour inconnu");break;
}
printf("%s ",jour);

printf("%d ",L->emprunteur.ladate);


switch(L->emprunteur.lemois)
{
case 0 :  strcpy(mois,"janvier");break;
case 1 :  strcpy(mois,"fevrier");break;
case 2 :  strcpy(mois,"mars");break;
case 3 :  strcpy(mois,"avril");break;
case 4 :  strcpy(mois,"mai");break;
case 5 :  strcpy(mois,"juin");break;
case 6 :  strcpy(mois,"juillet");break;
case 7 :  strcpy(mois,"aout");break;
case 8 :  strcpy(mois,"septembre");break;
case 9 :  strcpy(mois,"octobre");break;
case 10 :  strcpy(mois,"novembre");break;
case 11 :  strcpy(mois,"decembre");break;

default : strcpy(jour,"mois inconnu");break;
}
printf("%s ",mois);

printf("%d ",L->emprunteur.lannee);
}

}

void lireDateSysteme(T_Emp *E)
{
char j[9],m[10],h[9],mer[11],vir[2];
int d,a;


system("date > ladate");
FILE * fic=NULL;  // pointeur de fichier
fic=fopen("ladate","r"); //fileOpen en mode 'r'EAD

//ici , si fic vaut NULL, alors le fopen a indiquÃ©
//que le fichier ladate n'est pas accessible
if (fic!=NULL)
	{
	while(!feof(fic))	
		{
		fscanf(fic,"%s %d %s %d %s %s %s",j,&d,m,&a,vir,h,mer);		
		if (!feof(fic)) 
			printf("\n-->LU : %s- %d- %s- %d- %s- %s",j,d,m,a,h,mer);		

		}
	fclose(fic);

if (strcmp(j,"lun.")==0) E->lejour=lu;
else if (strcmp(j,"mar.")==0) E->lejour=ma;
else if (strcmp(j,"mer.")==0) E->lejour=me;
else if (strcmp(j,"jeu.")==0) E->lejour=je;
else if (strcmp(j,"ven.")==0) E->lejour=ve;
else if (strcmp(j,"sam.")==0) E->lejour=sa;
else if (strcmp(j,"dim.")==0) E->lejour=di;

E->ladate=d;

if (strcmp(m,"janvier")==0) E->lemois=janv;
else if (strcmp(m,"fevrier")==0) E->lemois=fevr;
else if (strcmp(m,"mars")==0) E->lemois=mars;
else if (strcmp(m,"avril")==0) E->lemois=avri;
else if (strcmp(m,"mai")==0) E->lemois=mai;
else if (strcmp(m,"juin")==0) E->lemois=juin;
else if (strcmp(m,"juillet")==0) E->lemois=juil;
else if (strcmp(m,"aout")==0) E->lemois=aout;
else if (strcmp(m,"septembre")==0) E->lemois=sept;
else if (strcmp(m,"octobre")==0) E->lemois=octo;
else if (strcmp(m,"novembre")==0) E->lemois=nove;
else if (strcmp(m,"decembre")==0) E->lemois=dece;


E->lannee=a;
	}
	else
	{
		printf("n souci avec la date systeme !!");
		
		//on range une date irrÃ©elle 
		E->lejour=di;
		E->ladate=99;
		E->lemois=dece;
		E->lannee=-999;
	}
}

void ListerLibre(T_Bibliotheque *ptrb){
    int i;
    for(i=0;i<ptrb->nbLivres;i++)
    {
        if ((strcmp((&(ptrb->etagere[i]))->emprunteur.nomemprunteur,"")==0))
        afficherLivre( &(ptrb->etagere[i])  );
    }
}


void ListerRetard(T_Bibliotheque *ptrb){
    int i;
	time_t seconds1970;

	seconds1970=time(NULL);
    for(i=0;i<ptrb->nbLivres;i++)
    {
        if ((strcmp((&(ptrb->etagere[i]))->emprunteur.nomemprunteur,"")!=0 && seconds1970 - (&(ptrb->etagere[i]))->secondsSince1970 > 604800)){
        afficherLivre( &(ptrb->etagere[i])  );
		}
    }
}
