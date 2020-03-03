//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 9.1
/*
    Rewrite the program 8.1 in C++
*/
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

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

                            case SDLK_a:
                                for(i=0; i<10; i++)
                                {
                                    addBlockHeadToList(&blockhead_list);
                                }
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
