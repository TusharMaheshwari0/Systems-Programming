#include <stdio.h>
#include <stdlib.h>

main()
{
    int i=3,j=0,k=2,l=0,m=0;
    float a,b;
    i++;
    l=i+k;
    m=i-1.0;
    a=m/k;
    j=a;
    b=11;
    b+=i;
    b/=2;
    printf("\ni=%d   j=%d",i,j);
    printf("\nk=%d   l=%d",k,l);
    printf("\na=%f   b=%f",a,b);
    printf("\n%d %d\n%d\n\n%d",i/2,l,(short)a/i,k+l);
}
