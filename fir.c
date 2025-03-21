#include "fir.h"
#include <string.h>
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
    absorp* old_values = malloc(51*sizeof(absorp)); //tableau de valeurs initialisées
    memset(old_values, 0, 51);
    int counter =0;
    int etat=0;

    absorp myAbsorp;
    absorp temp;
    FILE* pf = initFichier(filename);
    absorp valeur_fichier = lireFichier(pf,&etat); //lecture du fichier
    while(etat !=EOF)
    {

	    myAbsorp = fir(valeur_fichier,counter,old_values);
        counter++;
        //re lecture pour éviter la dernière ligne de 0 (du au EOC)
        valeur_fichier = lireFichier(pf,&etat);
    }
    finFichier(pf);
    printf("ACR : %f`\n",myAbsorp.acr);
    printf("ACIR : %f\n",myAbsorp.acir);
    free(old_values);
    return myAbsorp;

}

absorp fir(absorp input,int counter,absorp* old_values){

	old_values[counter%51] = input;
    absorp output = {0};
	for(int i=0;i<51;i++) {
        output.acr += FIR_TAPS[i] * old_values[(counter+51 - i) % 51].acr; //Respecte la condition de circular buffer, le + 51 permet de ne jamais passer en dessous de 0
        output.acir += FIR_TAPS[i] * old_values[(counter+51- i) % 51].acir;
        output.dcr = old_values[50].dcr; //stockage de la dernière valeur de dcr
        output.dcir = old_values[50].dcir;
    }

	return output;
	
}
