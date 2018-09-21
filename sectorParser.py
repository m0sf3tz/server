from sectorMagic import *
#from plot import *

import sys

#second arg is the name of the file to parse

logName = sys.argv[1]
#logName = "log0"

print("Verifying.. " + logName)


def getDataPlot(sector):
    data = []

    block = list (sectorToBLock(sector,TRASMIT_BLOCK_SIZE) )

    #for the three sectors, append the data segments together
    data.extend(block[0][DATA_0_INDEX:PGA_GAIN_INDEX])
    data.extend(block[1][DATA_0_INDEX:PGA_GAIN_INDEX])
    data.extend(block[2][DATA_0_INDEX:PGA_GAIN_INDEX])

    plot(data)

def putData(sector):
    data = []

    block = list (sectorToBLock(sector,TRASMIT_BLOCK_SIZE) )

    #for the three sectors, append the data segments together
    data.extend(block[0][DATA_0_INDEX:PGA_GAIN_INDEX])
    data.extend(block[1][DATA_0_INDEX:PGA_GAIN_INDEX])
    data.extend(block[2][DATA_0_INDEX:PGA_GAIN_INDEX])

    dataParsed = open(logName + "parsed" , "w")

    dataArr = makeIntArr(data)

    for i in range (0, len(dataArr)):
        dataParsed.write((str(dataArr[i])))
        dataParsed.write(" ")


    dataParsed.close()

def makeIntArr(data):
    arr16 = []
    totalSamples = int (len(data)/2 )
    for x in range (0,totalSamples):
        lsb = data[2*x]
        msb = data[2*x+1]

        num = msb << 8 | lsb
        num = (num*2.0/0xfff0)*2.5
        arr16.append( num)

    return arr16


binary_file = open(logName, "rb")
sector = binary_file.read()
        
if firstScan(sector):
    putData(sector)
    #getDataPlot(sector)

