//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 8.2
//SDL Linker settings: -lmingw32 -lSDL2main -lSDL2
/*
Overview:
    For this class we'll be writing a couple of programs in SDL that acts as simple games.
    Program 1:
    Write a program in C that does the following:
    Define a structure that keeps track of block-faces on the screen:
    struct BLOCKHEAD_NODE
    {
    float x,y; // position
    float dx,dy; // movement component
    long color;
    int size;
    struct BLOCKHEAD_NODE * next;
    };
    Write functions:
    void addBlockHeadToList( struct BLOCKHEAD_NODE ** blockhead_list)
    {
    //this function will add a blockhead node to the list and set up it’s attributes as described.
    }
    void removeBlockHeadFromList( struct BLOCKHEAD_NODE ** blockhead_list, int index)
    {
    //this function will remove a blockhead node from the list at the position indicated by index.
    }
    void freeBlockHeadList.( struct BLOCKHEAD_NODE ** blockhead_list)
    {
    //this function will free all of the blockhead nodes in the list.
    }
    Additionally, you will need to write functions as follows:
    void renderBlockHead(struct BLOCKHEAD_NODE * blockhead)
    {
    //this function should draw the blockhead according that is appropriate for the structure elements.
    }
    void moveBlockHead(struct BLOCKHEAD_NODE * blockhead)
    {
    //this function should use the displacement vector to move the blockhead to a new position..
    //Be sure to handle bouncing off of the window borders.
    }
    void renderBlockHeadList( struct BLOCKHEAD_NODE * blockhead_list)
    {
    //this function should render all of the items in the block head list.
    }
    void moveBlockHeadList( struct BLOCKHEAD_NODE * blockhead_list)
    {
    //this function should update all of the items in the block head list.
    }
Write a program that:
    • Initializes a list of 30 block faces and initializes each face with random speed and direction, a
    random RGB color, a random x,y position, and a random size (10 to 20):
    • enters a loop that runs until “escape” is pressed.
    • Moves all of the blockheads.
    • Renders all of the blockheads.
    • If the “a” key is pressed, add 10 more block heads.
    • If the “r” key is pressed, remove blocks using a probability of 1 in 10.
    • If the “p” key is pressed, motion should be paused / unpaused.
    • Add mouse support so that clicking the left mouse button causes new faces to be created where
    the mouse is clicked.
    • Add mouse support so that clicking the right mouse button removes any faces that are under the
    mouse pointer.
    Use linked lists for your application.
Program 2:
    Rewrite the program above so that it uses dynamic arrays ( using realloc and free ) instead of a linked list.

*/
#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>//rand
#include<ctype.h>//exit()
#include"blockhead.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Window* window = NULL; //The window we'll be rendering to
    SDL_Surface* screenSurface = NULL; //The surface contained by the window
    int i, paused =0, number_of_blocks=0, index = 0;
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    struct BLOCKHEAD_NODE *blockhead_array;

    //Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf( "SDL not initialized. SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "Lab 8", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }

        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface( window );
            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ) );
            //Update the surface
            SDL_UpdateWindowSurface( window );
            //Wait a tenth of a second
            SDL_Delay( 100 );
        }
    }
//--------------------Above closes based on clicking x or escape key pressed----------

    //printlist(blockhead_array, number_of_blocks);
    for(i=0; i<30; i++)
    {
        addBlockHeadToList(&blockhead_array, number_of_blocks);
        number_of_blocks++;
        //printlist(blockhead_array, number_of_blocks);
    }
    while(!(state[SDL_SCANCODE_ESCAPE]))
    {
        SDL_Delay( 50 );
        if(!paused)
        {
            moveBlockHeadList(blockhead_array,number_of_blocks);
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ) );
            renderBlockHeadList(&blockhead_array, screenSurface,number_of_blocks);
            SDL_UpdateWindowSurface( window );
            SDL_Delay( 50 );
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
                            case SDLK_p:
                            if(paused == 1)
                            {
                                paused = 0;
                            }
                            else
                            {
                                paused = 1;
                            }
                            break;

                            case SDLK_a:
                                for(i=0; i<10; i++)
                                {
                                    addBlockHeadToList(&blockhead_array, number_of_blocks);
                                    number_of_blocks++;
                                }
                            break;

                            case SDLK_r:
                                index = 0;
                                for(index =0; index < number_of_blocks; index++)
                                {
                                    if((rand()/(double)RAND_MAX) <= 0.1)
                                    {
                                        removeBlockHeadFromList(&blockhead_array, index, number_of_blocks);
                                        number_of_blocks--;
                                    }
                                    index++;
                                }

                                //Note: we do not want to increment if we delete because it would skip the current block we are checking
                            break;
                        }
                    }
                    break;
            }
        }

        //Making god mode
        {
            int x,y;
            //creation
            if(SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                addBlockHeadToListOnClick(&blockhead_array, &x, &y, number_of_blocks);
                number_of_blocks++;
            }
            //destruction
            else if(SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
            {
                removeBlockHeadToListOnClick(&blockhead_array, &x, &y, &number_of_blocks);
            }
        }

    }

    return 0;
}
/*
void printlist( struct BLOCKHEAD_NODE *blockhead_array, int number_of_blocks)
{
    int i;
    for(i=0; i < number_of_blocks; i++)
    {
        printf("\nX-Position= %d, Y-Position= %d, X-Direction= %f, Y-Direction= %f, Color = %li, Size = %d",(blockhead_array[i]).x, (blockhead_array[i]).y,//ask paul why arrows and periods here
                                                            (blockhead_array[i]).dx, (blockhead_array[i]).dy, (blockhead_array[i]).color, (blockhead_array[i]).size);
                                                            //use arrow SDL REct struct *.x, SDL REct struct var.x makes
                                                            //we use periods because we already have pointer*
                                                            //use arrow if struct pointer
                                                            //use . if struct
    }
}
*/
void addBlockHeadToList(struct BLOCKHEAD_NODE ** blockhead_array, int number_of_blocks)
{
    int blockSize=(10*rand()/(double)RAND_MAX)+ (10);
    long blockColor = (((rand()/(double)RAND_MAX))* 0xffffff);
    double xPosition = ((rand()/(double)RAND_MAX)*1000), yPosition = ((rand()/(double)RAND_MAX)*1000), xVector = (rand()/(double)RAND_MAX)*10, yVector = (rand()/(double)RAND_MAX)*10;

    //50% chance of each direction
    if((int)xVector % 2 == 0)
        xVector = xVector * (-1);
    if((int)yVector % 2 == 0)
        yVector = yVector * (-1);

        //printf("%d ",sizeof(blockhead_array));
        //printf("%d ", number_of_blocks);
    if(number_of_blocks == 0)
    {
        (*blockhead_array)= (struct BLOCKHEAD_NODE *) malloc(sizeof(struct BLOCKHEAD_NODE));
    }
    else
    {
       (*blockhead_array)= (struct BLOCKHEAD_NODE *) realloc((*blockhead_array), sizeof(struct BLOCKHEAD_NODE) * (number_of_blocks +1));
    }
    (*blockhead_array)[number_of_blocks].x = xPosition;
    (*blockhead_array)[number_of_blocks].y = yPosition;
    (*blockhead_array)[number_of_blocks].dx = xVector;
    (*blockhead_array)[number_of_blocks].dy = yVector;
    (*blockhead_array)[number_of_blocks].color = blockColor;
    (*blockhead_array)[number_of_blocks].size = blockSize;
}

void addBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_array, int* x, int* y, int number_of_blocks)
{
    int blockSize=(10*rand()/(double)RAND_MAX)+ (10);
    long blockColor = (((rand()/(double)RAND_MAX))* 0xffffff);
    double xVector = (rand()/(double)RAND_MAX)*10, yVector = (rand()/(double)RAND_MAX)*10;

    //50% chance of each direction
    if((int)xVector % 2 == 0)
        xVector = xVector * (-1);
    if((int)yVector % 2 == 0)
        yVector = yVector * (-1);


    if(number_of_blocks == 0)
    {
        (*blockhead_array)= (struct BLOCKHEAD_NODE *) malloc(sizeof(struct BLOCKHEAD_NODE));
    }
    else
    {
        (*blockhead_array)= (struct BLOCKHEAD_NODE *) realloc((*blockhead_array), sizeof(struct BLOCKHEAD_NODE) * (number_of_blocks +1));
    }

    (*blockhead_array)[number_of_blocks].x = *x;
    (*blockhead_array)[number_of_blocks].y = *y;
    (*blockhead_array)[number_of_blocks].dx = xVector;
    (*blockhead_array)[number_of_blocks].dy = yVector;
    (*blockhead_array)[number_of_blocks].color = blockColor;
    (*blockhead_array)[number_of_blocks].size = blockSize;
}

void removeBlockHeadFromList( struct BLOCKHEAD_NODE ** blockhead_array, int index, int number_of_blocks)
{
    /*
    int i;
    struct BLOCKHEAD_NODE* temp;
    (temp) = (struct BLOCKHEAD_NODE *) malloc(sizeof(struct BLOCKHEAD_NODE)*(number_of_blocks -1));
    ripple effect
    for(i=0; i<number_of_blocks; i++)
    {
        printf("%d ", i);
        if(i == index)
        {
            ;//do nothing
        }
        else if(i > index)
        {
            *blockhead_array[i-1] = *blockhead_array[i];
        }
        else if(i < index)
        {
            *blockhead_array[i] = *blockhead_array[i];//does nothing
        }
    }
    (*blockhead_array) = (struct BLOCKHEAD_NODE *)realloc((*blockhead_array), sizeof(struct BLOCKHEAD_NODE)*(number_of_blocks -1));
    */
    (*blockhead_array)[index] = (*blockhead_array)[number_of_blocks -1];
    (*blockhead_array) = (struct BLOCKHEAD_NODE *)realloc((*blockhead_array), sizeof(struct BLOCKHEAD_NODE)*(number_of_blocks -1));

    return;
}



void removeBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_array, int* x, int* y, int *number_of_blocks)
{
    int i;
    //struct BLOCKHEAD_NODE * temp;

        //if((*blockhead_array)->x == *x && (*blockhead_array)->y == *y)
    for(i=0; i < (*number_of_blocks); i++)
    {
        if(*x >= (*blockhead_array)[i].x && *x <= ((*blockhead_array)[i].x + (*blockhead_array)[i].size) && *y >= (*blockhead_array)[i].y && *y <= ((*blockhead_array)[i].y + (*blockhead_array)[i].size) )
        {
            (*blockhead_array)[i] = (*blockhead_array)[(*number_of_blocks) -1];
            (*blockhead_array) = (struct BLOCKHEAD_NODE *)realloc((*blockhead_array), sizeof(struct BLOCKHEAD_NODE)*((*number_of_blocks) -1));
            (*number_of_blocks)--;
        }
    }
}
/*
void freeBlockHeadList( struct BLOCKHEAD_NODE ** blockhead_array)
{

}
*/
void renderBlockHead(struct BLOCKHEAD_NODE * blockhead, SDL_Surface *screenSurface)
{
    SDL_Rect rect = {(*blockhead).x, blockhead ->y, blockhead -> size, blockhead -> size};
    unsigned char B,G,R;
    B = (blockhead -> color) & 0xff;
    G = (blockhead -> color>>8) & 0xff;
    R = (blockhead -> color>>16) & 0xff;
    SDL_FillRect( screenSurface, &rect, SDL_MapRGB( screenSurface->format, R, G, B ) );
}

void renderBlockHeadList( struct BLOCKHEAD_NODE ** blockhead_array, SDL_Surface *screenSurface, int number_of_blocks)
{
    int i;
    for(i = 0; i < number_of_blocks; i++)
    {
        renderBlockHead(&(*blockhead_array)[i], screenSurface);
    }
}

void moveBlockHead(struct BLOCKHEAD_NODE * blockhead)
{
    //Flipping the vectors on bonks
    if(((blockhead -> x) + (blockhead -> size) >= SCREEN_WIDTH) || (blockhead -> x <=0))// Right Side || Left side
    {
        (blockhead -> dx) = ((blockhead -> dx)*-1);
    }
    if(((blockhead -> y) + (blockhead -> size) >= SCREEN_HEIGHT) || (blockhead -> y <=0))// Bottom side || Top side
    {
        (blockhead -> dy) = ((blockhead -> dy)*-1);
    }
    (blockhead -> x) = (blockhead -> x) + (blockhead -> dx);
    (blockhead -> y) = (blockhead -> y) + (blockhead -> dy);
}

void moveBlockHeadList( struct BLOCKHEAD_NODE * blockhead_array,int number_of_blocks)
{
    int i;
    for(i = 0; i< number_of_blocks; i++)
    {
        moveBlockHead(&blockhead_array[i]);
    }
}
