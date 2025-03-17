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
    int cnt=0;
    while(1){
	cnt++;
    	myOxy.spo2 = cnt%10;
    	myOxy.pouls =cnt%15;
    	affichage(myOxy);
    }
    
    return;
}
