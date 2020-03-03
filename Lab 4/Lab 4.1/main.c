//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 4
/*
Leetspeak is a simple fun transformation that substitutes numeric digits (and sometimes other symbols) for
letters. For example: The phrase “password” might be represented in leetspeak as “p@55w0rd”. Write a
simple C-Language function called void convertToLeetSpeak(char * text) that goes through all of the
characters pointed to by the text pointer and converts them as follows: a → @, A → 4 , s→ 5, S → $, e
or E → 3, l or L → 1, o or O → 0, b → 6, B→8 , z or Z → 2, t ot T → 7 .
int main( )
{
 //code to allow the input of a message string.
//call the convertToLeetSpeak function to modify the string.
 //print out the converted message string.
}
void convertToLeetSpeak( char * text )
{
 // code to convert the string as described above.
}
Your program should compile and execute without any warnings or errors.
*/

#include <stdio.h>
#include <stdlib.h>

char message[100];
int i;

void convertToLeetSpeak(char * text);

int main()
{
    printf("In this house we speak like Gamers only.\n");
    printf("Enter a word and it will be translated to leet speak:\n");
    convertToLeetSpeak(message);
    printf("After applying leet speak:\n");
    printf(message);

    return 0;
}

void convertToLeetSpeak(char * text)
{
    fgets(message,100,stdin);

    for(i=0; i< 100 ; i++)
    {
        if(message[i] == 'a')
        {
            message[i] = '@';
        }
        if(message[i] == 'A')
        {
            message[i] = '4';
        }
        if(message[i] == 's')
        {
            message[i] = '5';
        }
        if(message[i] == 'S')
        {
            message[i] = '$';
        }
        if(message[i] == 'e' || message[i] ==  'E')
        {
            message[i] = '3';
        }
        if(message[i] == 'l' || message[i] ==  'L')
        {
            message[i] = '1';
        }
        if(message[i] == 'o' || message[i] ==  'O')
        {
            message[i] = '0';
        }
        if(message[i] == 'b')
        {
            message[i] = '6';
        }
        if(message[i] == 'B')
        {
            message[i] = '8';
        }
        if(message[i] == 'z' || message[i] ==  'Z')
        {
            message[i] = '2';
        }
        if(message[i] == 't' || message[i] ==  'T')
        {
            message[i] = '7';
        }
    }
    printf("\n");
}
