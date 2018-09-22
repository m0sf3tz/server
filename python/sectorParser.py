from sectorMagic import *
from fftMagic import *
from Email import *

import sys

#second arg is the name of the file to parse

logName = sys.argv[1]

binary_file = open(logName, "rb")
rawBinary = binary_file.read()
parsedData = getData(rawBinary)


if firstScan(rawBinary):
    #integrate up tot 200Hz 
    score = integrateFFT(parsedData,200)

    print("score = " + str(score))

    if score > 1.25:
         #sendEmail(score)
         print("Fault found within sample - emialing client")
    else:
        print ("no fault found within sample")




#getDataPlot(rawBinary)
