//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 5
/*
    Use #define directives to define the BOARD_HEIGHT as 50 and BOARD_WIDTH as 50. Place these in
    a header file along with the function prototypes for all of the functions used in the program.
    Write the code for the following functions:

    main( ) - Thsi is the main function and it should create a 2D board array that is BOARD_WIDTH x
    BOARD_HEIGHT cells big and call the init_board function to initialize the board array with 200 randomly
    chosen cells that are alive. Run the game of life by calling the next_generation function once per cycle.
    For each cycle, display the board and allow the user to press enter to continue to the next generation, or
    type 'quit' or 'exit' or 'q' to terminate the program.

    init_board( board, num_alive) – This function should initialize the board with num_alive randomly
    chosen living cells.

    display_board( board ) - create a function that prints the board array out in a text form. Use '*' for alive
    cells and '.' for dead cells.

    num neighbors(board,x,y) - create a function that returns the number of live neighbors (cells
    vertically, horizontally, or diagonally adjacent) for the specified cell. Since our world is finite,
    adjacent cells which are beyond the edge of the world are presumed to be dead.

    next state( board,x,y) – create a function that returns the next state (alive or dead) of the cell at the
    specified coordinates using the number of live neighbors (returned by the num neighbors(x,y) function)
    and the standard “Game of Life” rules.

    next_generation(board ) - create a function that goes through each cell and determines the board state for
    the entire next generation. Be sure that you don't update the current generation as you go through the
    current pass. This may mean making a copy of the board for the next generation and then copying it after
    making a pass through the current generation to determine the next.
    Make sure to document your code as appropriate.
    Be sure to demonstrate and submit your completed working program.

    1. A live cell with fewer than two live neighbors dies.
    2. A live cell with more than three live neighbors also dies.
    3. A live cell with exactly two or three live neighbors lives.
    4. A dead cell with exactly three live neighbors becomes alive
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>//rand
#include <ctype.h>//exit()
#include "dimensions.h"// holds board dimensions and prototypes, check directory, to make a new File> new >empty file
//#include <string.h>//memcpy did not use this
/*
#define BOARD_HEIGHT 50
#define BOARD_WIDTH 50

void next_generation(int board[BOARD_HEIGHT][BOARD_WIDTH]);
int next_state(int board[BOARD_HEIGHT][BOARD_WIDTH],int x,int y);
int num_neighbors(int board[BOARD_HEIGHT][BOARD_WIDTH],int x,int y);
void init_board( int board[BOARD_HEIGHT][BOARD_WIDTH], int num_alive);
void display_board( int board[BOARD_HEIGHT][BOARD_WIDTH] );
*/

int main()
{
    int board[BOARD_HEIGHT][BOARD_WIDTH],num_alive=0;
    char message[100];
    srand(time(0));
    init_board( board, num_alive);
    display_board( board );// move

    for(;;)
    {
        printf("Press the enter key to continue or type quit, q, or exit to leave the program:");
        fgets(message,100,stdin);

        if(message[0] == 10)
        {
            next_generation(board );
        }
        else if(message[0] == 'q' && message[2] == '\0')
        {
            exit(0);
        }
        else if(message[0] == 'q' && message[1] == 'u' && message[2] == 'i' && message[3] == 't' && message[5] == '\0')
        {
            exit(0);
        }
        else if(message[0] == 'e' && message[1] == 'x' && message[2] == 'i' && message[3] == 't' && message[5] == '\0')
        {
            exit(0);
        }
    }
}

void init_board( int board[BOARD_HEIGHT][BOARD_WIDTH], int num_alive)
{
    int ROW,HEIGHT;
    float j;
// Fill the board with zeros----------------------------------------------------------------
    for(HEIGHT=0; HEIGHT<BOARD_WIDTH; HEIGHT++)
    {
        for(ROW=0; ROW<BOARD_HEIGHT; ROW++)
        {
            board[BOARD_HEIGHT][BOARD_WIDTH] = 0;
        }
    }
//------------------------------------------------------------------------------------------

    while(num_alive<200)
    {
        for(HEIGHT=0; HEIGHT<BOARD_WIDTH; HEIGHT++)
        {
            for(ROW=0; ROW<BOARD_HEIGHT; ROW++)
            {

                j = ((float)rand()/(RAND_MAX+1));

                if(board[ROW][HEIGHT] != 1)
                {
                    if(j < (200.0/2500.0) && num_alive < 200)
                    {
                        num_alive++;
                        board[ROW][HEIGHT] = 1;
                    }
                    else
                    {
                        board[ROW][HEIGHT] = 0;
                    }
                }
            }

        }
    }
}

void display_board( int board[BOARD_HEIGHT][BOARD_WIDTH] )
{
    int ROW,HEIGHT;

    for(HEIGHT=0; HEIGHT<BOARD_WIDTH; HEIGHT++)
    {
        for(ROW=0; ROW<BOARD_HEIGHT; ROW++)
        {
            if(board[ROW][HEIGHT] ==1)
            {
                printf("*");
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

int num_neighbors(int board[BOARD_HEIGHT][BOARD_WIDTH],int x,int y)
{
    int i;
//------------------------Finding values for all corners first----------------
        if(y == 0 && x==0)
        {
            i = ((board[x][y+1]) + (board[x+1][y+1]) + (board[x+1][y]));
        }
        else if(y == 0 && x == BOARD_WIDTH-1)
        {
            i = ((board[x-1][y]) + (board[x-1][y+1]) + (board[x][y+1]));
        }
        else if(x == 0 && y == BOARD_HEIGHT-1)
        {
            i = ((board[x][y-1]) + (board[x+1][y-1]) + (board[x+1][y]));
        }
        else if(x == BOARD_WIDTH-1 && y == BOARD_HEIGHT-1)
        {
            i = ((board[x-1][y]) + (board[x-1][y-1]) + (board[x][y-1]));
        }
//--------------------------Counting the sides---------------------------------

        else if(x==0 && y < BOARD_HEIGHT && y > 0)
        {
            i = ((board[x][y-1]) + (board[x+1][y-1]) + (board[x+1][y]) + (board[x+1][y+1]) + (board[x][y+1]));
        }
        else if(x==BOARD_WIDTH-1 && y < BOARD_HEIGHT && y > 0)
        {
            i = ((board[x][y-1]) + (board[x-1][y-1]) + (board[x-1][y]) + (board[x-1][y+1]) + (board[x][y+1]));
        }
        else if(y==0 && x < BOARD_WIDTH && x > 0)
        {
            i = ((board[x-1][y]) + (board[x-1][y+1]) + (board[x][y+1]) + (board[x+1][y+1]) + (board[x+1][y]));
        }
        else if(y==BOARD_HEIGHT-1 && x < BOARD_WIDTH && x > 0)
        {
            i = ((board[x-1][y]) + (board[x-1][y-1]) + (board[x][y-1]) + (board[x+1][y-1]) + (board[x+1][y]));
        }
//------------------------Everything in the middle---------------------------
        else
        {
            i = ((board[x-1][y-1]) + (board[x][y-1]) + (board[x+1][y-1]) + (board[x-1][y]) + (board[x+1][y]) + (board[x-1][y+1]) + (board[x][y+1]) + (board[x+1][y+1]));
        }
    return i;
}

int next_state(int board[BOARD_HEIGHT][BOARD_WIDTH],int x,int y)
{
    int i;
    i = num_neighbors(board,x,y);

    if(i < 2 || i > 3)
    {
        return 0;
    }
    else if(board[x][y] == 0 &&  i == 2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void next_generation(int board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int temp_board[BOARD_HEIGHT][BOARD_WIDTH];

    for(int y = 0; y <BOARD_HEIGHT; y++)
    {
        for(int x = 0; x< BOARD_WIDTH; x++)
        {
            temp_board[x][y] = next_state(board,x,y);
        }
    }
    for(int y = 0; y <BOARD_HEIGHT; y++)
    {
        for(int x = 0; x< BOARD_WIDTH; x++)
        {
            board[x][y] = temp_board[x][y];
        }
    }
    display_board( board );
}
