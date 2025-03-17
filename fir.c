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
	absorp old_value[51] = {0};
	int arr_size = 0;

	int etat=0;//etat de la lecture du fichier
	absorp myAbsorp;
	int sum_acr = 0;
	int sum_acir = 0;
	FILE* pf = initFichier(filename);

	while(etat !=EOF)
	{
		absorp absorp_fichier = lireFichier(pf,&etat);
		

		for(int i=0;i<arr_size;i++)
		{
			old_value[arr_size] = absorp_fichier;
			sum_acr += FIR_TAPS[i]*old_value[arr_size-i].acr;
			sum_acir += FIR_TAPS[i]*old_value[arr_size-i].acir;

			arr_size++;
			
		}	
		myAbsorp.acr = sum_acr;
	       	myAbsorp.acir = sum_acir;	

		myAbsorp.dcr = absorp_fichier.dcr;
		myAbsorp.dcir = absorp_fichier.dcir;
		
		
		//finFichier(pf);
	}

	return myAbsorp;

}

void main(){
	char* filename = "log/log1/log1.dat";
	firTest(filename);
	return;
}

