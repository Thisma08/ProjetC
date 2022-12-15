#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct plat{
	int idPlat;
	char nomPlat[21];
	float prix;
	struct plat *suivant;
}plat;

typedef struct tab{
	int numero;
	int nbPlaces;
	int reserve;
}tab;

typedef struct client{
	int idClient;
	char nom[21];
	char prenom[21];
	int numeroTable; 
	int nbPersonne;
	struct client *cliSuivant;
} client;


main(){
	//déclarations
	FILE *fmenu, *fres,*ftable,*fclient;
	int i,n=0,idPlatero,place,choixMenu,j,nbPlaceTot=0,nbTable=0,fin=0,choixSousMenu,c=0,nbPlaceDispo=0;    //n = nombres de plat, c = nombre de clients
	fmenu = fopen("menu.dat","r");
	ftable = fopen("tables.dat","r");
	fclient = fopen("clients.dat","r");
	plat *deb,*courant,*suivant,*intercale,*tri;
	client *cliDeb,*cliCourant,*cliSuivant,*cliIntercale,*cliTri;
	
	deb=malloc(sizeof(plat));
	cliDeb=malloc(sizeof(client));
	courant=deb;
	cliCourant=cliDeb;
	struct tab table[51];
	
	//lecture et remplissage de la liste chainée des plats
	fscanf(fmenu,"%2d",&courant->idPlat);
	while(!feof(fmenu)){
		fscanf(fmenu,"%s %f",&courant->nomPlat,&courant->prix);
		suivant=malloc(sizeof(plat));
		(*courant).suivant=suivant;
		n++; 		//Détermine le nb de plats 
		printf("%2d %-20s %6.2f\n",courant->idPlat,courant->nomPlat,courant->prix);  //A SUPPRIMER (test)
		courant=suivant;
		fscanf(fmenu,"%3d",&courant->idPlat);
	}
	//termine avec adresse null
	courant=deb;
	for(i=1;i<n;i++){
		courant=courant->suivant;
	}
	(*courant).suivant=NULL;
	free(suivant);
	
	//lecture des tables
	i=1;
	fscanf(ftable,"%d",&table[i].numero);
	while(!feof(ftable)){
		fscanf(ftable,"%d %d",&table[i].nbPlaces,&table[i].reserve);
		i++;
		nbTable++;
		fscanf(ftable,"%d",&table[i].numero);
	}
	
	//lecture des clients
	fscanf(fclient,"%d",&cliCourant->idClient);
	while(!feof(fclient)){
		fscanf(fclient,"%s %s %d %d",&cliCourant->nom,&cliCourant->prenom,&cliCourant->numeroTable,&cliCourant->nbPersonne);
		cliSuivant=malloc(sizeof(client));
		(*cliCourant).cliSuivant=cliSuivant;
		c++;                                   //Détermine le nb de clients
		printf("%2d %-20s %-20s %2d %2d\n",cliCourant->idClient,cliCourant->nom,cliCourant->prenom,cliCourant->numeroTable,cliCourant->nbPersonne); //A SUPPRIMER (test)
		cliCourant=cliSuivant;
		fscanf(fclient,"%d",&cliCourant->idClient);
	}
	//termine avec adresse null
	cliCourant=cliDeb;
	for(i=1;i<c;i++){
		cliCourant=cliCourant->cliSuivant;
	}
	(*cliCourant).cliSuivant=NULL;
	free(cliSuivant);
	
	//MENU PRINCIPAL
	printf("----------- RESTAURANT ------------\n");
	while(fin==0){	
		printf("\n1. Gestion du menu\n");
		printf("2. Gestion des tables\n");
		printf("3. Gestion des réservations\n");
		printf("0. Quittez le programme\n");
		
		printf("\nQue voulez vous faire ?\n");
		printf("CHOIX : ");
		scanf("%d",&choixMenu);
		
		//MENU POUR LES PLATS
		if (choixMenu == 1){
			printf("\n1. Affichez le menu\n");
			printf("2. Ajouter un plat au menu\n");
			printf("3. Supprimer un plat du menu\n");
			printf("0. Retour\n");
			printf("CHOIX : ");
			scanf("%d",&choixSousMenu);
			
			//AFFICHAGE DES PLATS
			if (choixSousMenu == 1){
				printf(" NUM  | NOM DU PLAT               | PRIX EN EURO | \n");
				printf("--------------------------------------------------\n");
				courant=deb;
				for(i=1;i<=n;i++){
					printf("  %2d  | %-20s      |        %5.2f |\n",i,courant->nomPlat,courant->prix);
					courant=courant->suivant;
				}
			}
			
			//AJOUT D'UN PLAT
			if (choixSousMenu == 2){
				place=n+1;
				intercale=malloc(sizeof(plat));
				if (place!=1){
					courant=deb;
					for (i=1;i<place-1;i++){
						courant=courant->suivant;
					}
					intercale->suivant=courant->suivant;
					courant->suivant=intercale;
				}
				else{
					intercale->suivant=deb;
					deb=intercale;
				}
				printf("Entrez le nom du nouveau plat");
				scanf("%s",&intercale->nomPlat);
				printf("Entrez le prix du nouveau plat");
				scanf("%f",&intercale->prix);
				n++;
			}
			
			//SUPPRESSION D'UN PLAT
			if (choixSousMenu == 3){
				printf("suppression en quelle position ?\n");
				scanf("%d",&place);
				if(place>=1 && place <=n){
					if (place==1){
						intercale=deb;
						deb=deb->suivant;
						free(intercale);
					}
					else{
						courant = deb;
						for(i=1;i<place-1;i++){
							courant=courant->suivant;
						}
						if(place!=n){
							intercale=courant->suivant;
							courant->suivant=intercale->suivant;
							free(intercale);
						}
						else{
							intercale=courant->suivant;
							courant->suivant=NULL;
							free(intercale);
						}
					}
					n--;
				}
				else printf("Impossible\n");
			}	
		}
		
		//MENU DES TABLES
		if(choixMenu==2){
			printf("\n1. Affichez la liste des tables\n");
			printf("2. Affichez le nombre places totales\n");
			printf("3. Affichez le nombre places disponibles\n");
			printf("0. Retour\n");
			printf("CHOIX : ");
			scanf("%d",&choixSousMenu);
			
			//AFFICHAGE DE LISTE DE TABLES
			if(choixSousMenu==1){
				printf("Numéro de table | Nombres de places\n");
				printf("-----------------------------------\n");
				for (i=1;i<=nbTable;i++){
					printf("             %2d |                %2d",table[i].numero,table[i].nbPlaces);
					if (table[i].reserve==0){
						printf(" Pas reservee\n");
					}else printf(" Reservee\n");
				}
			}
			
			//AFFICHAGE DU NB DE PLACES TOTALES
			if(choixSousMenu==2){
				nbPlaceTot=0;
				for (i=1;i<=nbTable;i++){
					nbPlaceTot+=table[i].nbPlaces;
				}
				printf("Nombre de places totales dans le restaurant : %3d\n",nbPlaceTot);	
			}
			
			//AFFICHAGE DU NB DE PLACES DISPONIBLES
			if(choixSousMenu==3){
				nbPlaceDispo=0;
				for (i=1;i<=nbTable;i++){
					if(table[i].reserve==0){
						nbPlaceDispo+=table[i].nbPlaces;	
					}			
				}
				printf("Nombre de places disponibles dans le restaurant : %3d\n",nbPlaceDispo);	
			}
			
		}
		
		//MENU RESERVATION
		if(choixMenu == 3){
			printf("\n1. Afficher les réservations\n");
			printf("2. Réserver une table\n");
			printf("3. Annuler une réservation\n");
			printf("0. Retour\n");
			printf("CHOIX : ");
			scanf("%d",&choixSousMenu);
			
			//AFFICHAGE DES RESERVATIONS
			if (choixSousMenu == 1){
				cliCourant=cliDeb;
				printf(" NOM                 | PRENOM              | NUMERO DE TABLE | NOMBRE DE PERSONNES |\n");
				printf("------------------------------------------------------------------------------------\n");
				for(i=1;i<=c;i++){
					printf(" %-20s| %-20s| %2d              | %2d                  |\n",cliCourant->nom,cliCourant->prenom,cliCourant->numeroTable,cliCourant->nbPersonne);
					cliCourant=cliCourant->cliSuivant;
				}
			}
			
			//RESERVATION
			if (choixSousMenu == 2){
				place = c + 1;
				cliIntercale=malloc(sizeof(client));
				if (place!=1){																// A OPTI
					cliCourant=cliDeb;
					for (i=1;i<place-1;i++){
						cliCourant=cliCourant->cliSuivant;
					}
					cliIntercale->cliSuivant=cliCourant->cliSuivant;
					cliCourant->cliSuivant=cliIntercale;
				}
				else{
					cliIntercale->cliSuivant=cliDeb;
					cliDeb=cliIntercale;
				}
				printf("Sous quel nom voulez vous réserver ?\n");
				scanf("%s",&cliIntercale->nom);
				printf("Sous quel prénom voulez vous réserver ?\n");
				scanf("%s",&cliIntercale->prenom);
				printf("Pour combien de personnes ?\n");
				scanf("%d",&cliIntercale->nbPersonne);
				printf("Choississez une table parmis celles disponibles\n");
				printf("Numéro de table | Nombres de places\n");
				printf("-----------------------------------\n");
					
				//AFFICHE UNIQUEMENT LES TABLES NON RESERVEES ET CELLES ASSEZ GRANDES POUR LA RESERVATION
				for (i=1;i<=nbTable;i++){	
					if (table[i].reserve==0 && cliIntercale->nbPersonne <= table[i].nbPlaces){
						printf("             %2d |                %2d\n",table[i].numero,table[i].nbPlaces);
					}
				}
				scanf("%d",&cliIntercale->numeroTable);
					
				//Update -> mets la nouvelle table Reservee en Reservee
				for (i=1;i<=nbTable;i++){	
					if (table[i].numero==cliIntercale->numeroTable){
						table[i].reserve=1;												
					}
				}
				c++;				
			}	
		}
		
		//Quitte le programme
		if(choixMenu==0){
			fin=1;
		}
	}
	
//	//tri
//	courant=deb;
//	for(i=1;i<=n-1;i++){
//		for(j=i+1;j<=n;j++){
//			if (courant->nomPlat>suivant->nomPlat){
//				tri = courant;
//				courant = suivant;
//				suivant = tri;
//			}
//		}
//		courant = courant->suivant;
//	}
	
//MISE A JOUR DES FICHIERS DE DONNEES 

	//Update du fichier menu
	fmenu = fopen("menu.dat","w");
	courant = deb;
	for(i=1;i<=n;i++){
		fprintf(fmenu,"%d %-20s %5.2f\n",i,courant->nomPlat,courant->prix);
		courant=courant->suivant;
	}
	
	//Update du fichier clients
	fclient = fopen("clients.dat","w");
	cliCourant = cliDeb;
	for(i=1;i<=c;i++){
		fprintf(fclient,"%d %-20s %-20s %d %d\n",i,cliCourant->nom,cliCourant->prenom,cliCourant->numeroTable,cliCourant->nbPersonne);
		cliCourant=cliCourant->cliSuivant;
	}
	
	//Update du fichier tables
	ftable = fopen("tables.dat","w");
	for (i=1;i<=nbTable;i++){	
		fprintf(ftable,"%2d %2d %d\n",table[i].numero,table[i].nbPlaces,table[i].reserve);
	}
	
}
