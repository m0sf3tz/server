typedef enum {START_SECTOR, START_BLOCK, END_BLOCK, END_SECTOR, NO_MAGIC_KEY} magicKey_t;
typedef enum {PROCESSING_START_BLOCK, PROCESSING_MIDDLE_BLOCK, PROCESSING_FINAL_BLOCK} currentBlock_t;



typedef struct
{
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    uint8_t b4;
}state_t;


typedef struct
{
    state_t     shiftRegister;
    uint8_t     currentBuff;
}validator_t;

void       initShiftParser();
magicKey_t shiftInRxAndSearchForMagicKeys(uint8_t rxIn);
