#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "autotests.h"
#include "affichage.h"
#include "define.h"
void main(){
    //testBlocIIR();
    //testBlocFIR();
    //firTest("log/log1/log1_fir.dat");
    oxy myOxy;
    myOxy.spo2 = 1;
    myOxy.pouls =1;
    affichage(myOxy);
    return;
}
