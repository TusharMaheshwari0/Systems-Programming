//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 2.1
/*
        Write a simple C program that performs this Monte-Carlo simulation for 100,000,000 points. To do this,
    make a loop that iterates 100000000 times. Within that loop select two random numbers (x and y) in the
    range 0 through 1000. Treat these random numbers like a point in the box that is 1000 by 1000. If the
    point is less than or equal to 1000 units away form the origin (0,0) then count it is inside the box. For
    every 10000 points that are generated, print out the total count so far, the number counted as inside the
    circle so far, and the current estimate that is computed for Pi (as described above).
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    long i;
    int d, x, y;
    double points_inside_circle = 0;
    double pi;
    srand(time(0));

    for(i=1; i<100000000; i++)
    {
        x=((rand()/(double)RAND_MAX)*1000);
        y=((rand()/(double)RAND_MAX)*1000);
        d=sqrt(( (x*x) + (y*y) ));
        if(d<1000)
        {
            points_inside_circle++;
        }

        if(i%10000 == 0)
        {
            pi = ((points_inside_circle * 4) / i);
            printf("Total Count: %li, Points inside circle: %li, Estimate of Pi: %f\n", i, (long)points_inside_circle, pi);
        }
    }
    printf("Total Count: %li, Total points inside circle: %li, Estimate of Pi: %f", i,(long)points_inside_circle, pi);
}
