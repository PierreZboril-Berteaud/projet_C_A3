#include "affichage.h"

void affichage(oxy myOxy){
	if(access(".verrouData",F_OK) !=-1)
	{
		
	}
	else
	{
		FILE * data =  fopen("data.txt","w");
		FILE * verrouData;
		
		verrouData = fopen("verrouData","r");
		if(data==NULL)
		{
		printf("erreur lors de l'ouverture du fichier data");
		}

		fprintf(data,"%d\n",myOxy.spo2);
		fprintf(data,"%d\n",myOxy.pouls);

		fclose(data);
		remove(".verrouData");
	}
		
}

