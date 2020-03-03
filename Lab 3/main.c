//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 3
/*
Write a simple C-Language program that defines the following functions:
int main( )
{
 //code to call the print table function to print out a table of the
 //characters form 'A' to 'Z'
}
void printTable(unsigned char startChar, unsigned char endChar)
{
 // code to print a table of the specified characters as follows:
 // decimal representation, the character representation, and the 8-bit binary
 // representation. Call the printBinary function to print the
// binary representation. Call the printHex function to print the hexadecimal
// representation.
}
void printBinary(unsigned char ch)
{
 // code to print out the specified character in binary.
}
void printHex(unsigned char ch)
{
 // code to print out the specified character in hexadecimal.
}
Your program should compile and execute without any warnings or errors.
Your output should look something like this:
Table A to Z:
 num ch bin hex
 65 A 01000001 0x41
 66 B 01000010 0x42
 67 C 01000011 0x43
 68 D 01000100 0x44
 69 E 01000101 0x45
 70 F 01000110 0x46
 71 G 01000111 0x47
 72 H 01001000 0x48
 73 I 01001001 0x49
 74 J 01001010 0x4a
 75 K 01001011 0x4b
 76 L 01001100 0x4c
 77 M 01001101 0x4d
 78 N 01001110 0x4e
 79 O 01001111 0x4f
 80 P 01010000 0x50
 81 Q 01010001 0x51
 82 R 01010010 0x52
 83 S 01010011 0x53
 84 T 01010100 0x54
 85 U 01010101 0x55
 86 V 01010110 0x56
 87 W 01010111 0x57
 88 X 01011000 0x58
 89 Y 01011001 0x59
 90 Z 01011010 0x5a
*/

#include <stdio.h>
#include <stdlib.h>

//Must define prototypes or put main at the bottom
//because some compilers will not realize what the main is calling
//on until after the prototypes are initialized
void printTable(unsigned char startChar, unsigned char endChar);
void printBinary(unsigned char startChar);
void printHex(unsigned char startChar);

unsigned char startChar, endChar = 90, mask = 0x80;
int i;

int main()
{
    printTable(startChar, endChar);
    return 0;
}
void printTable(unsigned char startChar, unsigned char endChar)
{
    printf("Table A to Z:\n");
    printf("num ch bin hex\n");
    for(startChar=65; startChar<=endChar; startChar++)
    {
        printBinary(startChar);
        mask = 0x80;
        printHex(startChar);
    }
}
void printBinary(unsigned char startChar)
{
        printf("%d  %c  ", startChar, startChar);
        for(i=0; i<8; i++)//Would have been better to use a while(mask); because mask will automatically turn into all zeros
        {
            startChar&mask?printf("1"):printf("0");
            mask>>=1;
        }
}
void printHex(unsigned char startChar)
{
 printf(" 0x%x\n", startChar);
}
