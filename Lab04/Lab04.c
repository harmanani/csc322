/*******************************************
 * Pinky Machine Architectural simulator   *
 *******************************************/

/*******************************************
 * Author:  Haidar M. Harmanani            *
 *                                         *
 * CSC 322: Computer Organization Lab      *
 * Spring 2017                             *
 *                                         *
 * Lab 04                                  *
 *******************************************/

#include <stdio.h>

/********************************************
 * Pinky Machine Operation code definitions *
 ********************************************/

#define OP_HALT 0x0
#define OP_LDW  0x1
#define OP_STW  0x2
#define OP_ADD  0x3
#define OP_SUB  0x4
#define OP_AND  0x5
#define OP_OR   0x6
#define OP_XOR  0x7
#define OP_ADDS 0x8
#define OP_SUBS 0x9
#define OP_SL   0xA
#define OP_SR   0xB

#define W0   0x0
#define W1   0x1
#define W2   0x2
#define W3   0x3
#define W4   0x4
#define W5   0x5
#define W6   0x6
#define W7   0x7
#define W8   0x8
#define W9   0x9
#define W10  0xA
#define W11  0xB
#define W12  0xC
#define W13  0xD
#define W14  0xE
#define W15  0xF
#define W16  0x10
#define W17  0x11
#define W18  0x12
#define W19  0x13
#define W20  0x14
#define W21  0x15
#define W22  0x16
#define W23  0x17
#define W24  0x18
#define W25  0x19
#define W26  0x1A
#define W27  0x1B
#define W28  0x1C
#define W29  0x1D
#define W30  0x1E
#define W31  0x1F


/*************************************
 * Picky Machine Assembly code macros *
 *************************************/

#define HALT                                  OP_HALT << 20
#define LDW(DestReg, BaseReg, Address)       (OP_LDW  << 20) | (Address << 10)  | (BaseReg << 5) | DestReg
#define STW(SourceReg, BaseReg, Address)   (OP_STW  << 20) | (Address << 10)  | (BaseReg << 5) | SourceReg
#define ADD(DestReg, SourceReg2, SourceReg1) (OP_ADD << 20) | (SourceReg2 << 15) | (SourceReg1 << 5) | DestReg


char *Instr[] =
{
    "Halt","Load","Store", "Add", "Sub", "Logical And", "Logical Or", "Logical Xor",
    "AddS", "SubS", "Shift Left", "Shift Right"
};

/**********************************
 * Pinky MachineInstruction memory *
 **********************************/
unsigned int IM[256] =
{
    LDW(W0,W5, 0),     // 0
    LDW(W1,W6, 1),     // 1
    ADD(W2,W0,W1),     // 2
    STW(W2,W31,2),     // 3
    HALT               // 4
};

unsigned int DM[256] =
{
    30,               // 0
    20                // 1
};


/*****************************************************
 * Pinky Machine Register File - 32x32-bit registers *
 *****************************************************/

int R[32];

/****************************
 * Condition Flag registers *
 ****************************/

unsigned short Z, N;

/****************************
 * Instruction Pointer      *
 ****************************/

unsigned short PC  = 0, Opcode;


 /****************************
  * Simulator variables      *
  ****************************/

unsigned short sRun = 1;

void load(unsigned short iIndex, unsigned short iAddress, unsigned short iDisplacement);
void store(unsigned short iIndex, unsigned short iAddress, unsigned short iDisplacement);
void add(unsigned short uDest, unsigned short uReg1, unsigned short uReg2);
void halt(void);

void  Decode(int IR, unsigned short *iOpcode, unsigned short *iDestReg,
             unsigned short *iSourceReg2, unsigned short *iSourceReg1,
             unsigned short *iShiftAmt, unsigned short *iAddress,
             unsigned short *iBaseReg);

unsigned int IR;


 /***************************
 *         Decode Unit      *
 ****************************/

void  Decode(int IR, unsigned short *iOpcode, unsigned short *iDestReg, unsigned short *iSourceReg2,
             unsigned short *iSourceReg1, unsigned short *iShiftAmt, unsigned short *iAddress,
             unsigned short *iBaseReg)
{
    *iOpcode = (IR >> 20);
    
    *iDestReg = -1;
    *iSourceReg2 = -1;
    *iSourceReg1 = -1;
    *iShiftAmt = -1;
    *iAddress = -1;
    *iBaseReg = -1;
    
    switch (*iOpcode)
    {
        case OP_HALT:
            break;
            
        case OP_LDW:
            *iBaseReg = (IR >>  5) & 0x001F;
            *iAddress = (IR >> 10) & 0x03FF;
            *iDestReg = (IR & 0x001F);
            break;
        
        case OP_STW:
            *iBaseReg    = (IR >>  5) & 0x001F;
            *iAddress    = (IR >> 10) & 0x03FF;
            *iSourceReg1 = (IR & 0x001F);
            break;
            
        case OP_ADD:
            *iSourceReg1 = (IR >>  5) & 0x001F;
            *iSourceReg2 = (IR >> 15) & 0x001F;
            *iDestReg = (IR & 0x001F);
            break;
    }
    
}

int main(void);

/***************************
 * Main fetch/execute loop *
 ***************************/
int main()
{
    unsigned short iOpcode, iDestReg, iSourceReg2, iSourceReg1, iShiftAmt, iAddress, iBaseReg;
    unsigned short iRegIndex;

    R[W31] = 0;
    R[W5] = 0;
    R[W6] = 0;
    
    printf("Pinky Machine simulator (version 1.0)\n");
    printf("----------------------------\n");
    
    while(sRun) {
        printf("\nCurrent Memory address: %02X\n", (unsigned short) PC);
        
        IR = IM[PC];
        
        Decode(IR, &iOpcode, &iDestReg, &iSourceReg2, &iSourceReg1, &iShiftAmt, &iAddress, &iBaseReg);
        printf("Current Instruction:%s\n", Instr[iOpcode] );

        switch (iOpcode) {
            case OP_LDW:
                load(iDestReg, iAddress, iBaseReg);
                PC = PC + 1;
                break;
            case OP_STW:
                store(iSourceReg1, iAddress, iBaseReg);
                PC = PC + 1;
                break;
            case OP_ADD:
                add(iDestReg, iSourceReg1, iSourceReg2);
                PC = PC + 1;
                break;
            case OP_HALT:
                PC = PC + 1;
                halt();
                break;
        }
        printf("\nPC: %02x\n", (unsigned) PC);
        
        for (iRegIndex =1; iRegIndex < 33; iRegIndex++)
        {
            printf("R[%d] = %d ", iRegIndex-1, R[iRegIndex-1]);
            if ((iRegIndex % 6) == 0)
                printf("\n");
        }
    }
    printf("\n\nLeaving the simulator.\n\n");
    
    return (0);
}

/*******************************************
 * Load a value from memory                *
 *******************************************/

void load(unsigned short iDestReg, unsigned short iAddress, unsigned short iBaseReg)
{
    R[iDestReg] = DM[iAddress + R[iBaseReg]];
}

/*******************************************
 * Store a value in memory                 *
 *******************************************/

void store(unsigned short iSourceReg, unsigned short iAddress, unsigned short iBaseReg)
{
    DM[iAddress + R[iBaseReg]] = R[iSourceReg];
    printf("%d %d\n", iSourceReg, R[iSourceReg]);
}


/****************************************************************************************
 * Shift right the content of a register in the register file and store the results     *
 ****************************************************************************************/

void sr(unsigned short destination, unsigned short shiftamt, unsigned short source)
{
    
    
}

/****************************************************************************************
 * Shift left the content of a register in the register file and store the results      *
 ****************************************************************************************/

void sl(unsigned short destination, unsigned short shiftamt, unsigned short source)
{
    
    
}


/**********************************************
 * Add The contents of the two registers      *
 * in the register file and store the results *
 **********************************************/

void add(unsigned short destination, unsigned short source1, unsigned short source2)
{
    R[destination]= R[source1] + R[source2];
}

/**********************************************
 * Sub The contents of the two registers      *
 * in the register file and store the results *
 **********************************************/

void sub(unsigned short destination, unsigned short source1, unsigned short source2)
{
    R[destination]= R[source1] - R[source2];
}

/***************************************************
 * Logical 'and' the contents of the two registers *
 * in the register file and store the results      *
 ***************************************************/

void and(unsigned short destination, unsigned short source1, unsigned short source2)
{
    R[destination] = R[source1] & R[source2];
}

/***************************************************
 * Logical 'or' the contents of the two registers *
 * in the register file and store the results      *
 ***************************************************/

void or(unsigned short destination, unsigned short source1, unsigned short source2)
{
    R[destination]= R[source1] | R[source2];
}

/*************************************************************************************
 * Sub The contents of a register and an immediate and stores the results            *
 ************************************************************************************/

void subi(unsigned short destination, unsigned short source1, unsigned short source2)
{
    
    
    
}

/*************************************************************************************
 * Add The contents of a register and an immediate and stores the results            *
 ************************************************************************************/

void addi(unsigned short destination, unsigned short source1, unsigned short source2)
{
    
    
    
}

/************************************************************************************
 * Add The contents of a register and an immediate and stores the results           *
  * Set the condition flags                                                         *
 ************************************************************************************/
void adds(unsigned short destination, unsigned short source1, unsigned short source2)
{
    
    
    
}

/*************************************************************************************
 * Sub The contents of two registers and an immediate and stores the results         *
 * Set the condition flags                                                           *
 ************************************************************************************/
void subs(unsigned short destination, unsigned short source1, unsigned short source2)
{
    
    
    
}



/*******************************************
 * Halt the execution of the system        *
 *******************************************/

void halt()
{
    printf("Halt executed, program normally terminated. ");
    
    sRun = 0;
}
