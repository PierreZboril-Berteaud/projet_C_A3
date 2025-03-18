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
    absorp old_values[51] = {0}; //tableau de valeurs initialisées
    int arr_size = 51;
    int counter =0;
    int front; //avant du tableau (pour gérer tableau circulaire)
    int etat=0;//etat de la lecture du fichier

    absorp myAbsorp;
    FILE* pf = initFichier(filename);
    absorp absorp_fichier = lireFichier(pf,&etat); //lecture du fichier


    while(etat !=EOF)
    {

        myAbsorp.acr = 0;
        myAbsorp.acir = 0;

        counter++;

	fir(myAbsorp,counter,old_values);


        //re lecture pour éviter la dernière ligne de 0 (du au EOC)
        absorp_fichier = lireFichier(pf,&etat);
    }
    finFichier(pf);
    return myAbsorp;

}

absorp fir(absorp input,int counter,absorp old_values[]){
	
	int arr_size = 51;
	old_values[counter%51] = input;
	int front = counter %51;
	for(int i=0;i<51;i++) {
        input.acr += FIR_TAPS[i] * old_values[(front + arr_size - 1 - i) % 51].acr;
        input.acir += FIR_TAPS[i] * old_values[(front + arr_size - 1 - i) % 51].acir;
        input.dcr = old_values[50].dcr;
        input.dcir = old_values[50].dcir;
    }

	return input;
	
}
