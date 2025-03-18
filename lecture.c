//
// Created by nirin on 17/03/2025.
//
#include "lecture.h"

absorp readData(){
    absorp input = {0};

    FT_STATUS ftStatus;
    ftStatus =  FT_SetVIDPID(0403, 6015);
    if(ftStatus != FT_OK){
        printf("Failed to set custom VID PID");
    }
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    DWORD numDevs;
// create the device information list
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if (ftStatus == FT_OK) {
        printf("Number of devices is %d\n",numDevs);
    }
    if (numDevs > 0) {
// allocate storage for list based on numDevs
        devInfo =
                (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
// get the device information list
        ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
        if (ftStatus == FT_OK) {
            for (int i = 0; i < numDevs; i++) {
                printf("Dev %d:\n",i);
                printf(" Flags=0x%x\n",devInfo[i].Flags);
                printf(" Type=0x%x\n",devInfo[i].Type);
                printf(" ID=0x%x\n",devInfo[i].ID);
                printf(" LocId=0x%x\n",devInfo[i].LocId);
                printf(" SerialNumber=%s\n",devInfo[i].SerialNumber);
                printf(" Description=%s\n",devInfo[i].Description);
                printf(" ftHandle=0x%x\n",devInfo[i].ftHandle);
            }
        }
    }

    while(1) {
        FT_HANDLE ftHandle;
        DWORD EventDWord;
        DWORD TxBytes;
        DWORD RxBytes;
        DWORD BytesReceived;
        char RxBuffer[256];
        ftStatus = FT_OpenEx((PVOID) "D30BPUPH",FT_OPEN_BY_SERIAL_NUMBER,&ftHandle);
        if (ftStatus != FT_OK) {
            // FT_Open failed
            printf("Failed to open device handler\n");
            printf("ftstatus: %d", ftStatus );
            return input;
        }
        FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
        if (RxBytes > 0) {
            ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
            if (ftStatus == FT_OK) {
                // FT_Read OK
            } else {
                // FT_Read Failed
                printf("FT_Read failed");
            }
        }
    }
}
