#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "autotests.h"
void main(){
    //testBlocIIR();
    testBlocFIR();
    firTest("log/log1/log1_fir.dat");
    return;
}
