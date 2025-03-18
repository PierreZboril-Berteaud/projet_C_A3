#ifndef FIR_H
#define FIR_H

#include "define.h"
#include "fichiers.h"

absorp firTest(char* filename);
absorp fir(absorp input,int counter,absorp old_values[]);
#endif
