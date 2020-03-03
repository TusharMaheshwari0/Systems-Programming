//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 7
/*
Overview:
    For this class we'll be writing a program in SDL that adds graphics to your previous “Game of Life”
    program (lab 5).
    Description:
    Modify your program from lab 6 such that the Game of Life as follows:
    1. The game board should be 200 x 100 cells. The game should begin with 10000 randomly chosen
    living cells.
    2. The game should be rendered graphically using SDL.
    3. Each cell should be a 4x4 pixel square with a 1 pixel gap between them.
    4. The keys should work as follows:
    • Escape or Q– exit the program.
    • P – Pause / Resume the game's progression.
    • R – Reset with a new board with 10000 randomly chosen living cells.
    • A – Add 100 new living cells.
    • K – Cycle through all the living cells and use a 10% chance that each cell will be killed off.
Bonus:
    1. Add a the “Space bar” key as a single step when the game is paused. (2 points)
    2. Color code the cells by life-span where a cell that has survived a single generation is blue and
    additional generations of survival become brighter in color and closer to red in color. This should
    be implemented something like a heat-map and there should be a minimum of 16 levels of
    brightness. (5 points)
    3. Use the left mouse button to “draw cells” by setting them to the alive state when moving the
    mouse over the cells with the button pressed. Use the right mouse button to “clear cells” by
    setting them to
*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>//rand
#include <ctype.h>//exit()
#include "dimensions.h" //holds board dimensions and prototypes, check directory, to make a new File> new >empty file
//#include <string.h>//memcpy did not use this

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 500;

int main(int argc, char *argv[])
{
    srand(time(0));
    int board[BOARD_HEIGHT][BOARD_WIDTH],num_alive=10000, paused=0;

    SDL_Window* window = NULL; //The window we'll be rendering to
    SDL_Surface* screenSurface = NULL; //The surface contained by the window
    //Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf( "SDL not initialized. SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }

        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );
        }
    }

    init_board( board, num_alive);
    display_board( board, window, screenSurface );

    const uint8_t *state = SDL_GetKeyboardState(NULL);
    while(!(state[SDL_SCANCODE_ESCAPE] || state[SDL_SCANCODE_Q]))
    {
        if(!paused)
        {
            next_generation(board);
            display_board(board, window, screenSurface);
            SDL_Delay(100);
        }
        //event ques
        SDL_Event event;
        //User inputs
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    break;//return;
                case SDL_KEYDOWN:
                    if(event.key.repeat==0)
                    {
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_p://paused = !paused paused becomes what it's not

                            if(paused == 1)
                            {
                                paused = 0;
                            }
                            else
                            {
                                paused = 1;
                            }
                            break;

                            case SDLK_r:
                                init_board( board, 10000);
                                display_board(board, window, screenSurface);
                            break;

                            case SDLK_SPACE:
                                next_generation(board);
                                display_board(board, window, screenSurface);
                            break;

                            case SDLK_a:
                                add_random(board, 100);
                                display_board(board, window, screenSurface);
                            break;
                            case SDLK_k:
                                kill_random(board, 0.1);
                                display_board(board, window, screenSurface);
                            break;
                        }
                    }
                    break;
            }
        }
        //Making god mode
        {
            int x,y,row,column;
            //creation
            if(SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                row = y/5;
                column = x/5;
                if(!board[row][column])//only replace if it is dead
                {
                    board[row][column] = 1;
                    display_board(board, window, screenSurface);
                }
            }
            //destruction
            else if(SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
            {
                int row = y /5;
                int column = x/5;
                if(board[row][column] !=0)
                {
                    board[row][column] = 0;
                    display_board(board, window, screenSurface);
                }
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void init_board( int board[BOARD_HEIGHT][BOARD_WIDTH], int num_alive)
{
    int ROW,HEIGHT, u;
    float j;
// Fill the board with zeros----------------------------------------------------------------
    for(HEIGHT=0; HEIGHT<BOARD_WIDTH; HEIGHT++)
    {
        for(ROW=0; ROW<BOARD_HEIGHT; ROW++)
        {
            board[ROW][HEIGHT] = 0;
        }
    }
//------------------------------------------------------------------------------------------

    while(u < num_alive)
    {
        for(HEIGHT=0; HEIGHT<BOARD_WIDTH; HEIGHT++)
        {
            for(ROW=0; ROW<BOARD_HEIGHT; ROW++)
            {

                //j between 0 and 1
                j = ((float)rand()/(RAND_MAX+1));

                if(board[ROW][HEIGHT] != 1)
                {
                    if(j < 0.5 && u < num_alive)
                    {
                        u++;
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

void display_board( int board[BOARD_HEIGHT][BOARD_WIDTH], SDL_Window*window,SDL_Surface* screenSurface)
{
    int x,y;
    //const Uint8 *state = SDL_GetKeyboardState(NULL);// const it will never change addresses of where its pointing. Uint8 is unsigned int of 8 bits. *state is pointing to the address of whats stored in the keyboard
    SDL_Rect rect1;
    rect1.x = 0;
    rect1.y = 0;
    rect1.w = 4;
    rect1.h = 4;

    //Make a rectangle on the screen
    for(x=0; x < 500; x = (x+5))
    {
        for(y=0; y < 1000; y = (y+5) )
        {
            rect1.x = y;
            rect1.y = x;

            if(board[x/5][y/5] == 0)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 0,0,0 ) );
            }
            else if(board[x/5][y/5] == 1)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 123, 70, 152) );
            }
            else if(board[x/5][y/5] == 2)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 88, 75, 152) );
            }
            else if(board[x/5][y/5] == 3)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 71, 77, 152) );
            }
            else if(board[x/5][y/5] == 4)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 46, 80, 152) );
            }
            else if(board[x/5][y/5] == 5)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 13, 102, 164) );
            }
            else if(board[x/5][y/5] == 6)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 13, 148, 195) );
            }
            else if(board[x/5][y/5] == 7)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 15, 191, 181) );
            }
            else if(board[x/5][y/5] == 8)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 27, 184, 97) );
            }
            else if(board[x/5][y/5] == 9)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 153, 192, 93) );
            }
            else if(board[x/5][y/5] == 10)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 235, 216, 87) );
            }
            else if(board[x/5][y/5] == 11)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 248, 172, 78) );
            }
            else if(board[x/5][y/5] == 12)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 239, 121, 68) );
            }
            else if(board[x/5][y/5] == 13)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 238, 109, 69) );
            }
            else if(board[x/5][y/5] == 14)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 232, 68, 66) );
            }
            else if(board[x/5][y/5] == 15)
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 205, 25, 64) );
            }
            else
            {
                SDL_FillRect( screenSurface, &rect1, SDL_MapRGB( screenSurface->format, 255, 0, 0) );
            }
        }
    }
    SDL_UpdateWindowSurface(window);
}

int num_neighbors(int board[BOARD_HEIGHT][BOARD_WIDTH],int x,int y)
{
    int i,j,number_of_neighbors = 0;
    for(j = x - 1; j <= x + 1; j++)
    {
        for(i = y - 1; i <= y + 1; i++)
        {
            if(j >= 0 && j < BOARD_HEIGHT && i > 0 && i < BOARD_WIDTH)
            {
                if(j != x || i != y)
                {
                    if(board[j][i])
                    {
                        number_of_neighbors++;
                    }
                }
            }
        }
    }

    return number_of_neighbors;
}

int next_state(int board[BOARD_HEIGHT][BOARD_WIDTH],int x,int y)
{
    int count;
    count = num_neighbors(board,y,x);

    if(board[y][x] != 0 && count < 2)
    {
        return 0;
    }
    else if(board[y][x] != 0 && count > 3)
    {
        return 0;
    }
    else if(board[y][x] != 0 && count == 2)
    {
        return 1;
    }
    else if(board[y][x] != 0 && count == 3)
    {
        return 1;
    }
    else if(board[y][x] == 0 && count == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void next_generation(int board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int temp_board[BOARD_HEIGHT][BOARD_WIDTH];

    for(int y = 0; y < BOARD_HEIGHT; y++)
    {
        for(int x = 0; x< BOARD_WIDTH; x++)
        {
            temp_board[y][x] = next_state(board,x,y);
            //Sets lifetime of spot
            if(board[y][x] != 0 && temp_board[y][x] == 1)//Cycles more than 1
            {
                //the initialized board is adding the temp board to it producing 3 on 2nd cycle
                temp_board[y][x] = (board[y][x] + temp_board[y][x]);
            }
        }
    }

    for(int y = 0; y < BOARD_HEIGHT; y++)
    {
        for(int x = 0; x< BOARD_WIDTH; x++)
        {
            board[y][x] = temp_board[y][x];
        }
    }
}

void add_random(int board[BOARD_HEIGHT][BOARD_WIDTH], int num_alive)
{
    int ROW,HEIGHT,u=0;
    float j;
    while(u < num_alive)
    {
        for(HEIGHT=0; HEIGHT<BOARD_WIDTH; HEIGHT++)
        {
            for(ROW=0; ROW<BOARD_HEIGHT; ROW++)
            {

                //j between 0 and 1
                j = ((float)rand()/(RAND_MAX+1));

                if(board[ROW][HEIGHT] == 0)
                {
                    if(j < 0.005 && u < num_alive)
                    {
                        u++;
                        board[ROW][HEIGHT] = 1;
                    }
                }
            }

        }
    }
}

void kill_random(int board[BOARD_HEIGHT][BOARD_WIDTH], float chance)
{
    int ROW,HEIGHT;
    float j;

    for(HEIGHT=0; HEIGHT<BOARD_WIDTH; HEIGHT++)
    {
        for(ROW=0; ROW<BOARD_HEIGHT; ROW++)
        {

            //j between 0 and 1
            j = ((float)rand()/(RAND_MAX+1));

            if(board[ROW][HEIGHT] != 0)
            {
                if(j < chance)
                {
                    board[ROW][HEIGHT] = 0;
                }
            }
        }
    }
}
