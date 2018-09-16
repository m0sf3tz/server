/*
 * buffApp.c
 *
 *  Created on: Sep 8, 2018
 *      Author: Sam2
 */


#include<pthread.h>
#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

#include "projectDefines.h"
#include "shiftParser.h"
#include "buffApp.h"


static uint32_t  rxIndex;
static bool      processingSector;
static char      buff[TOTAL_BYTES_IN_SECTOR];

//use this guy to pick a name for our log
uint32_t logId;
pthread_mutex_t idLock;

static FILE * createLog(uint32_t logId)
{
    char id[20];
    char name[30];
    strcpy(name, "log");
    //id will now hold a string equal to t
    sprintf(id,"%d", logId);
    //name is log, add whatever logId is to it, now we get something like log34, etc
    strcat(name,id);
    
    FILE *logfile = fopen(name,"wb");
}

//creates the system command to kick off python
// ie.. "python sectorParser.py log34" etc
static void sysCommand(char * command, uint32_t logId )
{
    char id[20];   
    strcpy(command, "python3 sectorParser.py log");
    sprintf(id,"%d", logId);
    strcat(command,id);
}

static void* processInfo(void *arg)
{
    pthread_mutex_lock(&idLock);
    uint32_t t = logId++;
    pthread_mutex_unlock(&idLock);
    
    FILE *log = createLog(t);

   	fwrite(arg, TOTAL_BYTES_IN_SECTOR, 1, log);

    fclose(log);
    		
    free(arg);

    		
    char command[100];
    sysCommand(command,t);
    printf("%s", command);
    system(command);
    
    return NULL;
}

void initRxDigestor()
{
    rxIndex = 0;
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
                
                
               
                //while(z!= TOTAL_BYTES_IN_SECTOR)
                //{
                //   printf("%d : %c \n", z, buff[z]);
                //   z++;
                // }

                pthread_t tid;
                char * fullSector = malloc(TOTAL_BYTES_IN_SECTOR);
                memcpy(fullSector, buff,TOTAL_BYTES_IN_SECTOR);
                pthread_create(&tid, NULL, &processInfo, fullSector);
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
