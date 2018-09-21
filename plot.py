#import matplotlib.pyplot as plt
#import numpy as np
#from scipy.fftpack import fft
#import matplotlib.pyplot as plt

def plot(data):
    pass
'''
    arr16 = []

    totalSamples = int (len(data)/2 )

    for x in range (0,totalSamples):
        lsb = data[2*x]
        msb = data[2*x+1]

        num = msb << 8 | lsb
        num = (num*2.0/0xfff0)*2.5
        arr16.append( num)

    completeData = []
    incrementAxis = []

    count = 0;
    for elm in data:
        count = count + 1
        incrementAxis.append(count)

    # Number of sample points
    N = 3072
    # sample spacing
    T = 1.0 / 2100.0
    x = np.linspace(0.0, N * T, N)
    y = arr16
    yf = fft(y)
    # for N%2=0 first N/2 elements is relative to positive frequencies
    xf = np.linspace(0.0, 1.0 / (2.0 * T), N // 2)
    plt.figure(1)
    plt.subplot(211)
    plt.plot(x, y)
    plt.grid()

    plt.subplot(212)
    yf[0] = 0
    plt.plot(xf, 10 * 2.0 / N * np.abs(yf[0:N // 2]))
    plt.grid()
    plt.show()
