//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 8

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
#include"blockhead_node.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Window* window = NULL; //The window we'll be rendering to
    SDL_Surface* screenSurface = NULL; //The surface contained by the window
    int i, paused =0, index = 0;
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    struct BLOCKHEAD_NODE *blockhead_list = NULL;

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
    for(i=0; i<30; i++)
    {
        addBlockHeadToList(&blockhead_list);
    }
    while(!(state[SDL_SCANCODE_ESCAPE]))
    {
        SDL_Delay( 50 );
        if(!paused)
        {
            moveBlockHeadList(blockhead_list);
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ) );
            renderBlockHeadList(blockhead_list, screenSurface);
            SDL_UpdateWindowSurface( window );
            //SDL_Delay( 50 );
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
                                    addBlockHeadToList(&blockhead_list);
                                }
                            break;

                            case SDLK_k:
                                removeBlockHeadFromList(&blockhead_list, index);
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
                addBlockHeadToListOnClick(&blockhead_list, &x, &y);
            }
            //destruction
            else if(SDL_GetMouseState(&x,&y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
            {
                removeBlockHeadToListOnClick(&blockhead_list, &x, &y);
            }
        }

    }

    return 0;
}

void addBlockHeadToList(struct BLOCKHEAD_NODE ** blockhead_list)
{
    int blockSize=(10*rand()/(double)RAND_MAX)+ (10);
    long blockColor = (((rand()/(double)RAND_MAX))* 0xffffff);
    double xPosition = ((rand()/(double)RAND_MAX)*1000), yPosition = ((rand()/(double)RAND_MAX)*1000), xVector = (rand()/(double)RAND_MAX)*10, yVector = (rand()/(double)RAND_MAX)*10;

    //50% chance of each direction
    if((int)xVector % 2 == 0)
        xVector = xVector * (-1);
    if((int)yVector % 2 == 0)
        yVector = yVector * (-1);

    while((*blockhead_list)!=NULL)
    {
        blockhead_list=&((*blockhead_list)->next);
    }

    (*blockhead_list)=(BLOCK *)malloc(sizeof(BLOCK));
    (*blockhead_list)->x = xPosition;
    (*blockhead_list)->y = yPosition;
    (*blockhead_list)->dx = xVector;
    (*blockhead_list)->dy = yVector;
    (*blockhead_list)->color = blockColor;
    (*blockhead_list)->size = blockSize;
    (*blockhead_list)->next=NULL;
}

void addBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_list, int* x, int* y)
{
    int blockSize=(10*rand()/(double)RAND_MAX)+ (10);
    long blockColor = (((rand()/(double)RAND_MAX))* 0xffffff);
    double xVector = (rand()/(double)RAND_MAX)*10, yVector = (rand()/(double)RAND_MAX)*10;

    //50% chance of each direction
    if((int)xVector % 2 == 0)
        xVector = xVector * (-1);
    if((int)yVector % 2 == 0)
        yVector = yVector * (-1);

    while((*blockhead_list)!=NULL)
    {
        blockhead_list=&((*blockhead_list)->next);
    }

    (*blockhead_list)=(BLOCK *)malloc(sizeof(BLOCK));
    (*blockhead_list)->x = *x;
    (*blockhead_list)->y = *y;
    (*blockhead_list)->dx = xVector;
    (*blockhead_list)->dy = yVector;
    (*blockhead_list)->color = blockColor;
    (*blockhead_list)->size = blockSize;
    (*blockhead_list)->next=NULL;
}

void removeBlockHeadFromList( struct BLOCKHEAD_NODE ** blockhead_list, int index)
{
    int i=0;
    struct BLOCKHEAD_NODE * temp;

    while((*blockhead_list)!=NULL)
    {
        if((rand()/(double)RAND_MAX) <= 0.1)//10% chance
        {
            temp=(*blockhead_list);
            (*blockhead_list)=(*blockhead_list)->next;
            free(temp);
            return;
        }
        blockhead_list=&((*blockhead_list)->next);
        i++;
    }
}

void removeBlockHeadToListOnClick(struct BLOCKHEAD_NODE ** blockhead_list, int* x, int* y)
{
    int i=0;
    struct BLOCKHEAD_NODE * temp;

    while((*blockhead_list)!=NULL)
    {
        //if((*blockhead_list)->x == *x && (*blockhead_list)->y == *y)
        if(*x >= (*blockhead_list) -> x &&
           *x <= ((*blockhead_list) -> x + (*blockhead_list) -> size) &&
           *y >= (*blockhead_list) -> y &&
           *y <= ((*blockhead_list) ->y + (*blockhead_list) -> size) )
        {
            temp=(*blockhead_list);
            (*blockhead_list)=(*blockhead_list)->next;
            free(temp);
            return;
        }
        blockhead_list=&((*blockhead_list)->next);
        i++;
    }
}
void renderBlockHead(struct BLOCKHEAD_NODE * blockhead, SDL_Surface *screenSurface)
{
    SDL_Rect rect = {blockhead ->x, blockhead ->y, blockhead -> size, blockhead -> size};
    unsigned char B,G,R;
    B = (blockhead -> color) & 0xff;
    G = (blockhead -> color>>8) & 0xff;
    R = (blockhead -> color>>16) & 0xff;
    SDL_FillRect( screenSurface, &rect, SDL_MapRGB( screenSurface->format, R, G, B ) );
}

void renderBlockHeadList( struct BLOCKHEAD_NODE * blockhead_list, SDL_Surface *screenSurface)
{
    while(blockhead_list!=NULL)
    {
        renderBlockHead(blockhead_list, screenSurface);
        blockhead_list= blockhead_list->next;
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

void moveBlockHeadList( struct BLOCKHEAD_NODE * blockhead_list)
{
    while(blockhead_list!=NULL)
    {
        moveBlockHead(blockhead_list);
        blockhead_list= blockhead_list->next;
    }
}
