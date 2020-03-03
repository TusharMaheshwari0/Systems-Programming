//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Midterm 13

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(unsigned char input)
{
    char string[100];
    unsigned int num_positions = 0;
    rotateStringPrint(string,num_positions);
    printf(string);
    return 0;
}
void rotateStringPrint(char * string, unsigned int num_positions)
{
    int i,j;

    printf("Please enter the string you would like to be cycled less than : ");
    fgets(string,100,stdin);
    printf(string);

    printf("Please enter the number of cycles less than 128: ");
    scanf("%i", &num_positions);
    printf("\n%i\n", num_positions);

    for(i=0; i < num_positions; i++)
    {
        string[0]=string[((strlen(string)-1))];
        string[((strlen(string)-1))] << 1;
        //for(j=0; j < (strlen(string)-2); j++)
        //string[((strlen(string)-2))]= string[0];
        //string[((strlen(string)-2))]= string[i];
        //string[(strlen(string))]<<0x01;
        //printf(string);
    }

}
