#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "projectDefines.h"
#include "shiftParser.h"


validator_t validator;


//zero out the validator structure
//@todo - this is in BSS - we don't need
//to do this, there is something wrong with
//the BSS init script POS compiler is using
void initShiftParser()
{
    memset(&validator, 0, sizeof(validator_t));
}

magicKey_t searchForMagicBytes()
{
    uint32_t magicByte32 =   validator.shiftRegister.b0 << 0u  |
                             validator.shiftRegister.b1 << 8u  |
                             validator.shiftRegister.b2 << 16u |
                             validator.shiftRegister.b3 << 24u;



    uint64_t magicByte64  =  magicByte32 | (uint64_t)validator.shiftRegister.b4<< 32ull;


    if(magicByte32 == NEW_TRANSMIT_HEADER_32_BITS)
    {
        return START_SECTOR;
    }
    else if(magicByte64 == FINAL_STOP_SEQUENCE_64_BITS)
    {
        return END_SECTOR;
    }

    return NO_MAGIC_KEY;

}



//used to keep track of the last 5 byes we got
static void shiftIn(char in)
{
   validator.shiftRegister.b4 = validator.shiftRegister.b3;
   validator.shiftRegister.b3 = validator.shiftRegister.b2;
   validator.shiftRegister.b2 = validator.shiftRegister.b1;
   validator.shiftRegister.b1 = validator.shiftRegister.b0;
   validator.shiftRegister.b0 = in;
}

magicKey_t shiftInRxAndSearchForMagicKeys(uint8_t rxIn)
{
    shiftIn(rxIn);

    return searchForMagicBytes();
}

