//
// Created by nirin on 17/03/2025.
//
#include "lecture.h"

absorp readData(FT_HANDLE* ftHandle) {
    absorp input;
    FT_STATUS ftStatus;
        DWORD EventDWord;
        DWORD TxBytes;
        DWORD RxBytes;
        DWORD BytesReceived;
        char RxBuffer[512];

    FT_GetStatus(*ftHandle, &RxBytes, &TxBytes, &EventDWord);
        if (RxBytes > 0) {
            ftStatus = FT_Read(*ftHandle, RxBuffer, RxBytes, &BytesReceived);
            if (ftStatus == FT_OK) {
                // FT_Read OK
            } else {
                // FT_Read Failed
                printf("FT_Read failed");
            }
        }

        int i = 0;
        while(RxBuffer[i] != 10){ //\n CR flag
            i++;
            if(i >= 512){
                return;
            }
        }
        input.acr = (int)(RxBuffer[i+1] - '0') * 1000 + (int) (RxBuffer[i+2] - '0') * 100 + (int) (RxBuffer[i+3] - '0') * 10 + (int) (RxBuffer[i+4] - '0');
        input.dcr = (int)(RxBuffer[i+6] - '0') * 1000 + (int) (RxBuffer[i+7] - '0') * 100 + (int) (RxBuffer[i+8] - '0') * 10 + (int) (RxBuffer[i+9] - '0');
        input.acir = (int)(RxBuffer[i+11] - '0') * 1000 + (int) (RxBuffer[i+12] - '0') * 100 + (int) (RxBuffer[i+13] - '0') * 10 + (int) (RxBuffer[i+14] - '0');
        input.dcir = (int)(RxBuffer[i+16] - '0') * 1000 + (int) (RxBuffer[i+17] - '0') * 100 + (int) (RxBuffer[i+18] - '0') * 10 + (int) (RxBuffer[i+19] - '0');
        return input;
}
