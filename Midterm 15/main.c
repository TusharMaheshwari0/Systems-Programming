//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Midterm 15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    unsigned int size;
    void rhombus(unsigned int size);
    printf("Enter the length in * of how big of a rhombus you'd like: ");
    rhombus(size);
    return 0;
}

void rhombus(unsigned int size)
{
    int i,j;
    scanf("%i", &size);
    printf("%i\n", size);
    for(j=0; j<= size; j++)
    {
        printf("\n");
        for(i=0; i<= (size-j); i++)
        {
            printf(" ");
        }
        for(i=0; i<= size; i++)
        {
            printf("* ");
        }
        printf("\n");
    }
}
