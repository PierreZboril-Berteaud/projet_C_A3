//
// Created by nirin on 18/03/2025.
//


#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "affichage.h"
#include "define.h"
#include "mesure.h"
#include "lecture.h"

int main(){
    absorp firOutput;
    absorp iirOutput;
    FT_STATUS ftStatus;
    ftStatus = FT_SetVIDPID(0403, 6015);
    if (ftStatus != FT_OK) {
        printf("Failed to set custom VID PID");
    }
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    DWORD numDevs;
// create the device information list
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus == FT_OK) {
        printf("Number of devices is %d\n", numDevs);
    }
    if (numDevs > 0) {
// allocate storage for list based on numDevs
        devInfo =
                (FT_DEVICE_LIST_INFO_NODE *) malloc(sizeof(FT_DEVICE_LIST_INFO_NODE) * numDevs);
// get the device information list
        ftStatus = FT_GetDeviceInfoList(devInfo, &numDevs);
        if (ftStatus == FT_OK) {
            for (int i = 0; i < numDevs; i++) {
                printf("Dev %d:\n", i);
                printf(" Flags=0x%x\n", devInfo[i].Flags);
                printf(" Type=0x%x\n", devInfo[i].Type);
                printf(" ID=0x%x\n", devInfo[i].ID);
                printf(" LocId=0x%x\n", devInfo[i].LocId);
                printf(" SerialNumber=%s\n", devInfo[i].SerialNumber);
                printf(" Description=%s\n", devInfo[i].Description);
                printf(" ftHandle=0x%x\n", devInfo[i].ftHandle);
            }
        }
    }

    FT_HANDLE ftHandle;
    ftStatus = FT_Open(0,&ftHandle);
    //ftStatus = FT_OpenEx((PVOID) "D30BPUPK", FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);
    if (ftStatus != FT_OK) {
        // FT_Open failed
        printf("Failed to open device handler\n");
        printf("ftstatus: %d", ftStatus);
        //return input;
    }
    ftStatus = FT_SetBaudRate(ftHandle, FT_BAUD_460800);
    if (ftStatus == FT_OK) {
        // FT_SetBaudRate OK
    } else {
        // FT_SetBaudRate Failed
    }
    // Set 8 data bits, 1 stop bit and no parity
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1,
                                         FT_PARITY_NONE);
    if (ftStatus == FT_OK) {
        printf("data trame ok\n");
        // FT_SetDataCharacteristics OK
    } else {
        // FT_SetDataCharacteristics Failed
        printf("data trame not ok");
    }

    int counter = 1;
    absorp old_values[51] = {0};
    int nmb_ech = 0;
    float prevAC, rsir, max_ac_r, min_ac_r, max_ac_ir, min_ac_ir = 0;
    absorp prevInput = {0};
    absorp prevOutput = {0};
    oxy myOxy = {0};
    absorp* inputArr = NULL;
    absorp input = {0};
    while (1){
        inputArr = readData(&ftHandle);
        for(int i = 0; i < (RX_BUF_SIZE/21)-1; i++) {
            //printf("%f\n", inputArr[i].acr);
            input = fir(inputArr[i], counter, old_values);
            input = iir(input, &prevInput, &prevOutput);
            myOxy = mesure(input, &nmb_ech, &prevAC, &rsir, &max_ac_r, &min_ac_r, &max_ac_ir, &min_ac_ir);
            if (myOxy.spo2 != 0 && myOxy.pouls != 0) { //intermediate value
                affichage(myOxy);
            }
            counter++;
        }
        free(inputArr);
    }

    FT_Close(ftHandle);
    return 0;
}


