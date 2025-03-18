#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "autotests.h"
#include "affichage.h"
#include "define.h"
#include "mesure.h"

int main(){
   absorp old_values[51] = {0};
   int etat=0;
   absorp myAbsorp;
   oxy myOxy;
   
   FILE* myFile =  fopen("../log/log1/log1.dat","r");
   int counter = 0;
   do
   {
	counter++;
   	myAbsorp = lireFichier(myFile,&etat);
	myAbsorp = fir(myAbsorp,counter,old_values);

	
   }while(etat !=EOF);

    printf("ACR : %f\n",myAbsorp.acr);
    printf("ACIR :%f\n",myAbsorp.acir);
    printf("DCR: %f\n",myAbsorp.dcr);
    printf("DCIR: %f\n",myAbsorp.dcir);
   finFichier(myFile);
   return 0;

}

