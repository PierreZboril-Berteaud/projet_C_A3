#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "autotests.h"
#include "affichage.h"
#include "define.h"
#include "mesure.h"

int main(){
   absorp old_values[51] = {0};
   absorp myAbsorp;
   absorp valeur_fichier;
   oxy myOxy = {0};

   absorp prevInput = {0}; //stock l'entrée précedante
   absorp prevOutpout = {0}; //stock la sortie précendante
   FILE* myFile =  fopen("../log/log1/log1.dat","r");
   int etat=0;
   int nmb_ech = 0;
   /*stock le nombre d'échantillon,les différents extremums l'entrée précendante*/
   float prevAC, rsir, max_ac_r, min_ac_r, max_ac_ir, min_ac_ir = 0;
   int counter = 0;

  do{
      if(counter==0) {
          valeur_fichier = lireFichier(myFile, &etat);
      }

      myAbsorp = fir(valeur_fichier,counter,old_values);
      myAbsorp = iir(myAbsorp,&prevInput,&prevOutpout);
      counter++;
      myOxy = mesure(myAbsorp, &nmb_ech, &prevAC, &rsir, &max_ac_r, &min_ac_r, &max_ac_ir, &min_ac_ir);
      affichage(myOxy);


      valeur_fichier = lireFichier(myFile, &etat);

   }while(etat !=EOF);

    printf("ACR : %f\n",myAbsorp.acr);
    printf("ACIR : %f\n",myAbsorp.acir);
    printf("DCR : %f\n",myAbsorp.dcr);
    printf("DCIR : %f\n",myAbsorp.dcir);
    

    finFichier(myFile);

    //testBlocAffichage();
   return 0;

}

