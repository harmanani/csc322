import sys
from bitstring import BitArray

# Input and Output Registers
A = 0
B = 0
Result = 0

# Status registers
Z = 0 # bitstring.Bits(uint=bytes, length=8)
Ovf = 0

#define OpCodes
ADD = 0
SUB = 1
LEFT = 0
RIGHT = 1

# Arithemtic and Logical Unit
def AddSub(A, B, OpCode):
    if (OpCode == 0):
        Sum = A + B
    else:
        Sum= A - B


# set up the Z flag. Ignore the Ovf right flag for now



    return(Sum)

# 2-to-1 Multiplexer
def mux(In1, In2, Sel):
    if (Sel == 0):




    return(Out)

# AND Gate
def AND(A, B):


# OR Gate
def OR(A, B):


# main function
def main():
    A = 0b0000000001111011
    B = 0b0000000001100100
    Result = 0





    assert Result == 0b1100000

    print('Register A: {0} Register B: {1} Register Result: {2}'.format(bin(A), bin(B), bin(Result)))


if __name__ == '__main__':
    main()
