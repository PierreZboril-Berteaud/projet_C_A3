#include "iir.h"

absorp iirTest(char* filename){
    absorp prevInput;
    absorp prevOutput;
    absorp output;
    absorp input;
    int line = 0;
    FILE* fd = initFichier(filename);
    int etat = 0;
    input = lireFichier(fd, &etat);
    while (etat != EOF){
        if(line == 0){ //first input, no predecessor
            output = input;
            line += 1;
        }
        else{
            output.acr = input.acr - prevInput.acr + 0.992*prevOutput.acr;
            output.acir = input.acir - prevInput.acir + 0.992*prevOutput.acir;
            output.dcr = input.dcr;
            output.dcir = input.dcir;
            line+=1;
        }
        prevInput = input,
        prevOutput = output;
        printf("ACR: %f, DCR: %f, ACIR: %f, DCIR: %f\n", output.acr, output.dcr, output.acir, output.dcir);
        input = lireFichier(fd, &etat);
    }
    printf("line: %d", line);
    finFichier(fd);
	return output;
}

absorp iir(absorp input, absorp* prevInput, absorp* prevOutput){
    absorp output;
        if(prevOutput->acr == 0 && prevOutput->acir == 0 && prevOutput->dcr == 0 && prevOutput->dcir == 0){ //first input, no predecessor
            output = input;
        }
        else{
            output.acr = input.acr - prevInput->acr + 0.992*prevOutput->acr;
            output.acir = input.acir - prevInput->acir + 0.992*prevOutput->acir;
            output.dcr = input.dcr;
            output.dcir = input.dcir;
        }
        *prevInput = input,
        *prevOutput = output;

    return output;
}
