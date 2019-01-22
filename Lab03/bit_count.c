#include <stdio.h>
#include <stdlib.h>

// YOUR CODE HERE
// Define a function to count the bits in a
// number, and find the hightest and lowest
// 1 bit positions. Valid positions are 0
// for the lowest position, through 31 for
// the highest position. If the number has
// no 1 bits, the positions are both -1.
// ... you will need to change this function
// definition entirely
void analyze(const unsigned x) {
}


void bit_analyze(const int x) {
    unsigned bit_count = 0;
    int high_1, low_1;
    high_1 = low_1 = 0;
    

    // YOUR CODE HERE
    // Call the function you defined, and update
    // the 3 values: bit_count, high_1, low_1.
    // ... you will need to change this function
    // call to match your function definition
    analyze(x);
    
    
    printf("   NUMBER: %u\n",x);
    printf("     BITS: %u\n",bit_count);
    printf("HIGHEST 1: %d\n",high_1);
    printf(" LOWEST 1: %d\n",low_1);
    printf("\n");
}
int stoi(const char * str) {
    char * x = NULL;
    const long parsed = strtol(str, &x, 0);
    return x==str ? 0 : (int)parsed;
}
int main(int argc,
         const char * argv[]) {
    bit_analyze(argc>1 ? stoi(argv[1]) : 0);    
    return 0;
}
