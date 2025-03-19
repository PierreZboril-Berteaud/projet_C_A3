#include "affichage.h"

void affichage(oxy myOxy){
	if(access("../.verrouData",F_OK) !=-1) //vérifie si le fichier verrouData existe
	{

	}
	else
	{

		FILE * data =  fopen("../data.txt","w"); //ouvre le fichier data en mode write
		FILE * verrouData = NULL;
        verrouData = fopen("../.verrouData","w");; //si le fichier verrouData n'existe pas, on le crée
        fclose(verrouData);
		if(data==NULL)
		{
		printf("erreur lors de l'ouverture du fichier data");
		}

		fprintf(data,"%d\n",myOxy.spo2); //on met le spo2 à la première ligne du data.txt
		fprintf(data,"%d\n",myOxy.pouls); //on met le pouls à la deuxième ligne du data.txt

		fclose(data);
		remove("../.verrouData");
	}
		
}

