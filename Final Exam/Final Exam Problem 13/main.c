//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment Final Problem 13
//-lmingw32 -lSDL2main -lSDL2
/*
Write a program that makes a little face bounce back and forth across the screen between the two edges.
*/
#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>//rand
#include<ctype.h>//exit()
#include"Blockhead_info.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Window* window = NULL; //The window we'll be rendering to
    SDL_Surface* screenSurface = NULL; //The surface contained by the window
    int paused =0, index = 0;
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    struct BLOCKHEAD_NODE *blockhead_list = NULL;

    SDL_Rect leftCol;
    leftCol.x=0;
    leftCol.y=0;
    leftCol.h=500;
    leftCol.w=10;

    SDL_Rect rightCol;
    rightCol.x=490;
    rightCol.y=0;
    rightCol.h=500;
    rightCol.w=10;

    //Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        printf( "SDL not initialized. SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "Final Exam Problem 12", SDL_WINDOWPOS_UNDEFINED,
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
    addBlockHeadToList(&blockhead_list);

    while(!(state[SDL_SCANCODE_ESCAPE]))//blockhead_list *head ==0
    {
        SDL_Delay( 50 );
        if(!paused)
        {
            moveBlockHeadList(blockhead_list);
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 255, 255, 255 ) );
            SDL_FillRect( screenSurface, &leftCol, SDL_MapRGB( screenSurface->format, 0, 255, 0 ) );
            SDL_FillRect( screenSurface, &rightCol, SDL_MapRGB( screenSurface->format, 0, 255, 0 ) );
            renderBlockHeadList(blockhead_list, screenSurface);
            SDL_UpdateWindowSurface( window );
            //SDL_Delay( 100 );
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

                            case SDLK_SPACE:
                                    addBlockHeadToList(&blockhead_list);
                            break;

                            case SDLK_r:
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
    int blockSize=(10*rand()/(double)RAND_MAX +(10));
    long blockColor = (0xffff00);
    double xPosition = 1.0, yPosition = ((rand()/(double)RAND_MAX)*1000), xVector = (rand()/(double)RAND_MAX)*10, yVector =0;//sometimes having a 0 xpostion glitches the block

    if((int)xVector % 2 == 0)
        xVector = xVector * (-1);

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
    long blockColor = (0xffff00);
    double xVector = (rand()/(double)RAND_MAX)*10, yVector = 0, blockBonk = 0;

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
    (*blockhead_list)->number_of_bonks = blockBonk;
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
        if(((blockhead -> x) + (blockhead -> size) >= SCREEN_WIDTH) || (blockhead -> x <= 0))// Right Side || Left side
        {
            (blockhead -> dx) = (((blockhead -> dx)*-1)+1);
            (blockhead -> color )=(rand() *(16777215/RAND_MAX));
            (blockhead -> number_of_bonks) = (blockhead -> number_of_bonks + 1);
            if(blockhead -> number_of_bonks >= 10)
            {
                (blockhead -> color ) = 0xffffff;//need a remove from list call here but need index to do so
            }
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
