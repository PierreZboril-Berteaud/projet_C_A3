#ifndef PROJET_C_A3_MESURE_H
#include "define.h"
#include "fichiers.h"
#include "time.h"
#include "math.h"



double get_time_ns();
oxy mesureTest(char* filename);
oxy mesure(absorp input, int* nmb_ech, float* prevAC, float* rsir ,float* max_ac_r, float* min_ac_r, float* max_ac_ir, float* min_ac_ir);
void printTimeBuf(uint size, float* buf);

#endif

	
