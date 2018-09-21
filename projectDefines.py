
#//********************************************************************************//
#//                SPI/ADC DEFINES
#//********************************************************************************//
BLOCK_SPI_MEM_BYTE                     =256
ADC_SAMPLES_PER_BLOCK                  =128

SPI_MEMORY_SRAM_SIZE_BYTES             =0x1FFFF
SPI_TOTAL_SRAM_TOTAL_BLOCKS            =SPI_MEMORY_SRAM_SIZE_BYTES/BLOCK_SPI_MEM_BYTE

SPI_MEMORY_BIT_RATE                    =200000
SPI_MEMORY_ADDRESS_SIZE                =8

ADC_BIT_RATE                           =180000
ADC_BITS_PER_SAMPLE                    =16


MAXIMUM_MEMORY_ADRESS                 =0x1FFFF #//max range for

FIRST_BLOCK_SPI                       =0


#//********************************************************************************//
#//                SECTOR TRANSMIT CONSTANTS
#//********************************************************************************//


NEW_TRASMITION_HEADER_B0  =0xA0
NEW_TRASMITION_HEADER_B1  =0x0B
NEW_TRASMITION_HEADER_B2  =0xC0
NEW_TRASMITION_HEADER_B3  =0x1D

TRASMITION_HEADER_B0      =0x0B
TRASMITION_HEADER_B1      =0xB1
TRASMITION_HEADER_B2      =0x1B
TRASMITION_HEADER_B3      =0xB2

STOP_SEQUENCE_B0          =0xC1
STOP_SEQUENCE_B1          =0x2C
STOP_SEQUENCE_B2          =0xC2
STOP_SEQUENCE_B3          =0x2C
STOP_SEQUENCE_B4          =0xC3


FINAL_STOP_SEQUENCE_B0    =0xD2
FINAL_STOP_SEQUENCE_B1    =0x3D
FINAL_STOP_SEQUENCE_B2    =0xD3
FINAL_STOP_SEQUENCE_B3    =0x3D
FINAL_STOP_SEQUENCE_B4    =0xD4



#//these guys are used in C programs upstreams - not used in endpoint FW
NEW_TRANSMIT_HEADER_32_BITS  =(0xA00BC01D)

TRANSMIT_HEADER_32_BITS      =(0x1BB11BB1)
STOP_SEQUENCE_64_BITS        =(0xC22CC22CC2)

FINAL_STOP_SEQUENCE_64_BITS  =(0xD23DD33DD4)


'''
//********************************************************************************//
//                SECTOR TRANSMIT SIZE
//********************************************************************************//
'''
NEW_TRASMITION_HEADER_SIZE       =4

TRASMITION_HEADER_SIZE           =4

TRASMIT_SECTOR_SIZE              =1

SEQUENCE_ID_SIZE                 =2

CAP_VOLTAGE_SIZE                 =2

ESTIMATED_ENERGY_QUALITY_SIZE    =1

DATA_SIZE                        =2048

PGA_GAIN_SIZE                    =1

FREE_SIZE                        =4

CRC_SIZE                         =2

STOP_SEQUENCE_SIZE               =5

FINAL_STOP_SEQUENCE_SIZE         =5



'''
//********************************************************************************//
//                SECTOR TRANSMIT INDEX
//********************************************************************************//
'''
NEW_TRASMITION_HEADER_B0_INDEX     =0
NEW_TRASMITION_HEADER_B1_INDEX     =(NEW_TRASMITION_HEADER_B0_INDEX  + 1)
NEW_TRASMITION_HEADER_B2_INDEX     =(NEW_TRASMITION_HEADER_B1_INDEX  + 1)
NEW_TRASMITION_HEADER_B3_INDEX     =(NEW_TRASMITION_HEADER_B2_INDEX  + 1)


TRASMITION_HEADER_B0_INDEX         =0
TRASMITION_HEADER_B1_INDEX         =(TRASMITION_HEADER_B0_INDEX      + 1)
TRASMITION_HEADER_B2_INDEX         =(TRASMITION_HEADER_B1_INDEX      + 1)
TRASMITION_HEADER_B3_INDEX         =(TRASMITION_HEADER_B2_INDEX      + 1)


TRASMIT_SECTOR_B0_INDEX            =(NEW_TRASMITION_HEADER_B0_INDEX + NEW_TRASMITION_HEADER_SIZE)


SEQUENCE_ID_B0_INDEX               =(TRASMIT_SECTOR_B0_INDEX + TRASMIT_SECTOR_SIZE)
SEQUENCE_ID_B1_INDEX               =(SEQUENCE_ID_B0_INDEX +1)

CAP_VOLTAGE_B0_INDEX               =(SEQUENCE_ID_B0_INDEX + SEQUENCE_ID_SIZE)
CAP_VOLTAGE_B1_INDEX               =(CAP_VOLTAGE_B0_INDEX + 1)

ESTIMATED_ENERGY_QUALITY_INDEX     =(CAP_VOLTAGE_B0_INDEX + CAP_VOLTAGE_SIZE)

DATA_0_INDEX                       =(ESTIMATED_ENERGY_QUALITY_INDEX + ESTIMATED_ENERGY_QUALITY_SIZE)

PGA_GAIN_INDEX                     =(DATA_0_INDEX + DATA_SIZE)

FREE_B0_INDEX                      =(PGA_GAIN_INDEX + PGA_GAIN_SIZE)
FREE_B1_INDEX                      =(FREE_B0_INDEX + 1)
FREE_B2_INDEX                      =(FREE_B1_INDEX + 1)
FREE_B3_INDEX                      =(FREE_B2_INDEX + 1)

CRC_B0_INDEX                       =(FREE_B0_INDEX + FREE_SIZE)
CRC_B1_INDEX                       =(CRC_B0_INDEX + 1)

STOP_SEQUENCE_B0_INDEX             =(CRC_B0_INDEX + CRC_SIZE)
STOP_SEQUENCE_B1_INDEX             =(STOP_SEQUENCE_B0_INDEX + 1)
STOP_SEQUENCE_B2_INDEX             =(STOP_SEQUENCE_B1_INDEX + 1)
STOP_SEQUENCE_B3_INDEX             =(STOP_SEQUENCE_B2_INDEX + 1)
STOP_SEQUENCE_B4_INDEX             =(STOP_SEQUENCE_B3_INDEX + 1)


FINAL_STOP_SEQUENCE_B0_INDEX       =(CRC_B0_INDEX + CRC_SIZE)
FINAL_STOP_SEQUENCE_B1_INDEX       =(FINAL_STOP_SEQUENCE_B0_INDEX + 1)
FINAL_STOP_SEQUENCE_B2_INDEX       =(FINAL_STOP_SEQUENCE_B1_INDEX + 1)
FINAL_STOP_SEQUENCE_B3_INDEX       =(FINAL_STOP_SEQUENCE_B2_INDEX + 1)
FINAL_STOP_SEQUENCE_B4_INDEX       =(FINAL_STOP_SEQUENCE_B3_INDEX + 1)





CRC_PROTECED_SIZE                =(TRASMIT_SECTOR_SIZE + SEQUENCE_ID_SIZE + CAP_VOLTAGE_SIZE + ESTIMATED_ENERGY_QUALITY_SIZE + DATA_SIZE + PGA_GAIN_SIZE + FREE_SIZE) #// size of data protected by CRC, starting at SEQUENCE_ID_B0_INDEX
TRASMIT_BLOCK_SIZE               =(TRASMITION_HEADER_SIZE + TRASMIT_SECTOR_SIZE + SEQUENCE_ID_SIZE + CAP_VOLTAGE_SIZE + ESTIMATED_ENERGY_QUALITY_SIZE + DATA_SIZE + PGA_GAIN_SIZE + FREE_SIZE + CRC_SIZE + STOP_SEQUENCE_SIZE)

#********************************************************************************//
#                blocks <---> sector logic
#********************************************************************************//
#currently there are 8 blocks per sector (2048/256)

SECTORS_PER_SAMPLE       =(3)
BLOCKS_PER_SECTOR        =(DATA_SIZE/BLOCK_SPI_MEM_BYTE) //8
TOTAL_BLOCKS_IN_SAMPLE   =(SECTORS_PER_SAMPLE*BLOCKS_PER_SECTOR)

FIRST_TRASMIT_SECTOR     = (0)
LAST_TRANSMIT_SECTOR      =(SECTORS_PER_SAMPLE - 1)

TOTAL_BYTES_IN_SECTOR     =(TRASMIT_BLOCK_SIZE*SECTORS_PER_SAMPLE)


#//we need to take one away to account for byte - to index offset
FINAL_INDEX_SAMPLE       = (TOTAL_BYTES_IN_SECTOR - 1)
#********************************************************************************//
#               VCAP targets before we kick off tasks(see notes.h)
#********************************************************************************//

VCAP_TARGET_SAMPLE          =(0x164F)
VCAP_TARGET_CREATE_TX_BUFF  =(0x164F)
VCAP_TARGET_TRANSMIT        =(0x1EAD)



