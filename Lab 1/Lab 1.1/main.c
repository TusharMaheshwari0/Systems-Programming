//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 1.1
/*
Description: Write a simple C-Language program that prints out your name and a favorite quote on the screen. Note that
the quote should appear in quotation marks. Compile and run the program using the CODE::BLOCKS
IDE. Be sure to save the program as a plain C-language program and not a C++ program.
*/
#include <stdio.h>
#include <stdlib.h>
#define QUOTE "Whoever fights monsters should see to it that in the process he does not become a monster. And if you gaze long enough into an abyss, the abyss will gaze back into you."
#define MARKS "\""

int main()
{
    printf("Kyle Johnson\n");
    printf(MARKS);
    printf(QUOTE);
    printf(MARKS);
    printf("\n~Friedrich Nietzsche");
    return 0;
}
