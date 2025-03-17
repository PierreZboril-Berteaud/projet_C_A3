#include "fir.h"

float FIR_TAPS[51]={
        1.4774946e-019,
        1.6465231e-004,
        3.8503956e-004,
        7.0848037e-004,
        1.1840522e-003,
        1.8598621e-003,
        2.7802151e-003,
        3.9828263e-003,
        5.4962252e-003,
        7.3374938e-003,
        9.5104679e-003,
        1.2004510e-002,
        1.4793934e-002,
        1.7838135e-002,
        2.1082435e-002,
        2.4459630e-002,
        2.7892178e-002,
        3.1294938e-002,
        3.4578348e-002,
        3.7651889e-002,
        4.0427695e-002,
        4.2824111e-002,
        4.4769071e-002,
        4.6203098e-002,
        4.7081811e-002,
        4.7377805e-002,
        4.7081811e-002,
        4.6203098e-002,
        4.4769071e-002,
        4.2824111e-002,
        4.0427695e-002,
        3.7651889e-002,
        3.4578348e-002,
        3.1294938e-002,
        2.7892178e-002,
        2.4459630e-002,
        2.1082435e-002,
        1.7838135e-002,
        1.4793934e-002,
        1.2004510e-002,
        9.5104679e-003,
        7.3374938e-003,
        5.4962252e-003,
        3.9828263e-003,
        2.7802151e-003,
        1.8598621e-003,
        1.1840522e-003,
        7.0848037e-004,
        3.8503956e-004,
        1.6465231e-004,
        1.4774946e-019
};

absorp firTest(char* filename){
	absorp old_value[51] = {0}; //tableau de valeurs initialisées
	int arr_size = 0; 
	int front; //avant du tableau (pour gérer tableau circulaire)
	int etat=0;//etat de la lecture du fichier
	
	absorp myAbsorp;
	FILE* pf = initFichier(filename); 
	absorp absorp_fichier = lireFichier(pf,&etat); //lecture du fichier
	

	while(etat !=EOF)
	{
		
		myAbsorp.acr = 0;
		myAbsorp.acir = 0;

		
		
		old_value[arr_size %51] = absorp_fichier; 
		
		arr_size++;
		front = arr_size%51;



		for(int i=0;i<51;i++)
		{
		/*Formule du filtre FIR*/

		myAbsorp.acr += FIR_TAPS[i]*old_value[(front+50-i)%51].acr;
		
		myAbsorp.acir += FIR_TAPS[i]*old_value[(front+50-i)%51].acir;
			

		}
		//Ajout des valeurs brut à dcr et dcir 
		myAbsorp.dcr = old_value[arr_size%51].dcr;
		myAbsorp.dcir = old_value[arr_size%51].dcir;



		//re lecture pour éviter la dernière ligne de 0 (du au EOC)
		absorp_fichier = lireFichier(pf,&etat);
		
	}

	finFichier(pf);
	return myAbsorp;

}


