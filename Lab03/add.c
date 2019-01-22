/*******************************************
 * SP.1  Architectural simulation program. *
 *******************************************/

/*******************************************
 * Author:  Haidar M. Harmanani            *
 *          Department of Computer Science *
 *          Lebanese American University   *
 *          Byblos, 1401 2010.             *
 * Version: 1.0                            *
 * Date:    8 January 2018               *
 *                                         *
 *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/***************************
 * Memory Declaration.     *
 ***************************/
char DM[256] =
{
    15,         // Address 0
    20,         // Address 1
    10,        // Address 2
    25,        // Address 3
    11,         // Address 4
    3,          // Address 5
    12         // Address 6
};

char IM[256] =
{
    0,         // Address 0
    1,         // Add Opcode
};



/*******************************************************************
 * SP.1  Machine Registers - 8 bits register except the Z register *
 *******************************************************************/
unsigned char IP,    /* Instruction pointer */
               Z;    /* Zero flag */


char Reg1, Reg2, Reg3;   // CPU Registers

void Add(char *Destination, char Source1, char Source2);
int main(void);


/***************************
 * Main fetch/execute loop *
 ***************************/
int main()
{
    printf("CSC 322 Stupid Simulator\n");
    printf("--------------------\n");
    IP  = 0;
    Z   = 0;
    
    // Get two random values from Memory and add them
    // The memory has only 5 elements

    srand(time(NULL));

    // Load the values from the memory
    Reg1 = DM[rand() % 5];
    Reg2 = DM[rand() % 5];

    Add(&Reg3, Reg1, Reg2);

    printf("\nReg1: %02x    Reg2: %02x    Reg3: %02x\n", (unsigned) Reg2 & 0xFF, (unsigned) Reg2 & 0xFF,(unsigned) Reg3 & 0xFF);
    printf("IP: %02x      Z:  %s\n", (unsigned) IP & 0xFF,(Z ? "True" : "False"));
    
    printf("\n\nLeaving the stupid simulator.\n\n");
    
    return (0);
}


/*****************************************************************************************
 * Add the contents of two source registers and store the value in a destinatin register *
******************************************************************************************/
void Add(char *Destination, char Source1, char Source2)
{
    *Destination = Source1 + Source2;
    IP = IP + 1;
}
