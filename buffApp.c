/*
 * buffApp.c
 *
 *  Created on: Sep 8, 2018
 *      Author: Sam2
 */



#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "projectDefines.h"
#include "shiftParser.h"
#include "buffApp.h"


static uint32_t  rxIndex;
static bool      processingSector;
static char      buff[TOTAL_BYTES_IN_SECTOR];

void initRxDigestor()
{
    rxIndex     = 0;
}


void putBuff(uint32_t index, uint8_t rx)
{

    if(index > TOTAL_BYTES_IN_SECTOR)
    {
        printf("Critical error - went over bounds in putBuff \n");
        return;
    }
    buff[index] = rx;
}

void processIncomingData(uint8_t rxByte)
{
    magicKey_t key = shiftInRxAndSearchForMagicKeys(rxByte);

    if(processingSector == SEARCHING_FOR_SECTOR)
    {
        if (key == START_SECTOR)
        {
            //we found our first sector magic key, start storing the
            //incoming rx data into teh buffer;
            printf("Found start sector! \n");
            processingSector =  PROCESSING_SECTOR;
            rxIndex = TRASMIT_SECTOR_B0_INDEX;
        }
    }
    else
    {
        if (key == START_SECTOR)
        {
            //a new start key, start processing sector again (this is an error condition)
            rxIndex = TRASMIT_SECTOR_B0_INDEX;
        }
        else if(key == END_SECTOR)
        {
            if (rxIndex == FINAL_INDEX_SAMPLE)
            {
                //we need to put this because we don't start storing values until we
                //have finished getting the start magic key,
                //hence we need to manually put the magic key back in the buffer so it makes sense
                putBuff(NEW_TRASMITION_HEADER_B0_INDEX,NEW_TRASMITION_HEADER_B0);
                putBuff(NEW_TRASMITION_HEADER_B1_INDEX,NEW_TRASMITION_HEADER_B1);
                putBuff(NEW_TRASMITION_HEADER_B2_INDEX,NEW_TRASMITION_HEADER_B2);
                putBuff(NEW_TRASMITION_HEADER_B3_INDEX,NEW_TRASMITION_HEADER_B3);

                //still gotta put the last byte in
                putBuff(rxIndex,rxByte);
                processingSector =  SEARCHING_FOR_SECTOR;
                printf("Found end sector! \n");
            }
        }
        else
        {
            putBuff(rxIndex,rxByte);

            rxIndex++;

            if(rxIndex == TOTAL_BYTES_IN_SECTOR)
            {
                //should have gotten an end key by now
                //start scanning for a new sector
                printf("Critical error - sector over run, did not recieve magic end sector \n");
                processingSector =  SEARCHING_FOR_SECTOR;
            }
        }
    }
}
