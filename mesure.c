#include "mesure.h"

oxy mesureTest(char* filename){
    uint nmb_ech = 0;
    float prevAC = 0;
    float max_ac_r = 0;
    float min_ac_r = INFINITY;
    float max_ac_ir = 0;
    float min_ac_ir = INFINITY;
    float rsir = 0;
    float ellapsedTime = 0; //in ms
	oxy myOxy;
    absorp input;
    FILE* fd = initFichier(filename);
    int etat = 0;
    input = lireFichier(fd, &etat);
    prevAC = input.acr;
    while (etat != EOF){

        //BPM calculation
        if(prevAC <= 0 && input.acr > 0){ //crossed zero
            ellapsedTime = nmb_ech*0.002; //sample each 2ms
            myOxy.pouls = 60 / ellapsedTime;
            if(rsir <= 1){
                myOxy.spo2 = -25*rsir + 110;
            }
            else{
                myOxy.spo2 = -425/12 * rsir + 120.4;
            }
            nmb_ech = 0;
            max_ac_r = 0;
            min_ac_r = INFINITY;
            max_ac_ir = 0;
            min_ac_ir = INFINITY;
        }

        //AC peak to peak calculation;
        if(input.acr > max_ac_r){
            max_ac_r = input.acr;
        }
        if(input.acir > max_ac_ir){
            max_ac_ir = input.acir;
        }
        if(input.acr < min_ac_r){
            min_ac_r = input.acr;
        }
        if(input.acir < min_ac_ir){
            min_ac_ir = input.acir;
        }
        rsir = ((max_ac_r - min_ac_r)/input.dcr) / ((max_ac_ir - min_ac_ir) / input.dcir);

        printf("Pouls: %d, SPo2(%%): %d\n", myOxy.pouls, myOxy.spo2);
        prevAC = input.acr;
        input = lireFichier(fd, &etat);
        nmb_ech++;
    }
	return myOxy;
}

oxy mesure(absorp input, int* nmb_ech, float* prevAC, float* rsir ,float* max_ac_r, float* min_ac_r, float* max_ac_ir, float* min_ac_ir){
    if(nmb_ech == 0){
        *prevAC = 0;
        *max_ac_r = 0;
        *min_ac_r = INFINITY;
        *max_ac_ir = 0;
        *min_ac_ir = INFINITY;
        *rsir = 0;
    }
    float ellapsedTime = 0; //in ms
    oxy myOxy = {0};

    //BPM calculation
    if(*prevAC <= 0 && input.acr > 0){ //crossed zero
        ellapsedTime = (*(nmb_ech))*0.002; //sample each 2ms
        myOxy.pouls = 60 / ellapsedTime;
        if(*rsir <= 1 && *rsir >= 0.3){ //take margin for the extremum
            myOxy.spo2 = -25*(*rsir) + 110;
        }
        else{
            if(*rsir > 1 && *rsir <= 3.5){
                myOxy.spo2 = -425/12 * (*rsir) + 120.4;
            }
        }
        if(myOxy.spo2 < 0){ //when spo2 = 0 by the sim card
            myOxy.spo2 = 0;
        }
        *nmb_ech = 0;
        *max_ac_r = 0;
        *min_ac_r = INFINITY;
        *max_ac_ir = 0;
        *min_ac_ir = INFINITY;
        printf("Pouls: %d, SPo2(%%): %d\n", myOxy.pouls, myOxy.spo2);

    }

    //AC peak to peak calculation;
    if(input.acr > *max_ac_r){
        *max_ac_r = input.acr;
    }
    if(input.acir > *max_ac_ir){
        *max_ac_ir = input.acir;
    }
    if(input.acr < *min_ac_r){
        *min_ac_r = input.acr;
    }
    if(input.acir < *min_ac_ir){
        *min_ac_ir = input.acir;
    }
    *rsir = ((*max_ac_r - *min_ac_r)/input.dcr) / ((*max_ac_ir - *min_ac_ir) / input.dcir);
    (*(nmb_ech))++;
    *prevAC = input.acr;
    return myOxy;

}




