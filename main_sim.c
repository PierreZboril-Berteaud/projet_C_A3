#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "affichage.h"
#include "define.h"
#include "mesure.h"

int main(){
   absorp old_values[51] = {0};
   absorp myAbsorp = {0};
   absorp valeur_fichier = {0};
   oxy myOxy = {0};

   absorp prevInput = {0}; //stock l'entrée précedante
   absorp prevOutpout = {0}; //stock la sortie précendante
   FILE* myFile =  fopen("../log1.dat","r");
   if(myFile == NULL){
       printf("Error while openning log file");
       return 1;
   }
   int etat,nmb_ech,counter=0;
   /*stock le nombre d'échantillon,les différents extremums l'entrée précendante*/
   float prevAC, rsir, max_ac_r, min_ac_r, max_ac_ir, min_ac_ir = 0;

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

      if(counter == 52){
          counter =1;
      }

   }while(etat !=EOF);

    printf("ACR : %f\n",myAbsorp.acr);
    printf("ACIR : %f\n",myAbsorp.acir);
    printf("DCR : %f\n",myAbsorp.dcr);
    printf("DCIR : %f\n",myAbsorp.dcir);
    

    finFichier(myFile);

    //testBlocAffichage();
   return 0;

}

