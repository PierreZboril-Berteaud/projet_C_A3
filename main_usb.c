//
// Created by nirin on 18/03/2025.
//

#include "main_usb.h"

#include "iir.h"
#include "fir.h"
#include "fichiers.h"
#include "autotests.h"
#include "affichage.h"
#include "define.h"
#include "mesure.h"
#include "lecture.h"
/*int main(){
    absorp input = {0};
    absorp firOutput;
    absorp iirOutput;
    FILE* fd = fopen("log_usb.dat", "a");
    if(fd == NULL){
        printf("Failed to open file log_usb.dat");
        return 1;
    }
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
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    ftStatus = FT_OpenEx((PVOID) "D30BPUPH", FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);
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
        printf("data trame ok");
        // FT_SetDataCharacteristics OK
    } else {
        // FT_SetDataCharacteristics Failed
        printf("data trame not ok");
    }
    // Set read timeout of 5sec, write timeout of 1sec
    ftStatus = FT_SetTimeouts(ftHandle, 2, 1000);
    if (ftStatus == FT_OK) {
        // FT_SetTimeouts OK
    }
    else {
        // FT_SetTimeouts failed
    }

    while (1){
        input = readData(&ftHandle);
        printf("ACR: %f\n", input.acr);
        printf("DCR: %f\n", input.dcr);
        printf("ACIR: %f\n", input.acir);
        printf("DCIR: %f\n", input.dcir);
        fprintf(fd, "%f,%f,%f,%f", input.acr, input.dcr, input.acir, input.dcir);
    }

    FT_Close(ftHandle);
    fclose(fd);
    return 0;
}

*/
