//Name: Kyle Johnson
//Class: ETEC2110
//Section: 02
//Assignment 6
// Simple SDL2 program
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Click on the tab “Linker Settings” and in the “Other linker options:” pane, type the following:
//-lmingw32 -lSDL2main -lSDL2

//Screen dimension constants
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

int main(int argc, char *argv[])
{
    srand(time(0));
    unsigned char r = 255,g = 255,b = 255;
    SDL_Event e;
    int done = 0;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

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

            //Handling the Events
            while(!done)
            {
                while(SDL_PollEvent(&e))
                {
                    //Fill the surface white
                    SDL_FillRect( screenSurface, NULL,
                        SDL_MapRGB( screenSurface->format, r, g, b ) );


                    //Update the surface
                    SDL_UpdateWindowSurface( window );
                    //Wait a tenth of a second
                    SDL_Delay( 100 );

                    switch(e.type)
                    {
                        //Clicking the x on the window
                        case SDL_QUIT:
                        {
                            if(window)
                            {
                                SDL_DestroyWindow(window);
                                window = NULL;
                                done =1;
                            }
                        }
                        break;
                        //RGB stuff
                        case SDL_KEYDOWN:
                        {
                            switch(e.key.keysym.sym)
                            {
                                case SDLK_r:
                                r = rand();
                                g = rand();
                                b = rand();
                            }
                        }
                        break;
                        //--------------------
                    }
                    //pressing of the escape key to close the window
                    if(state[SDL_SCANCODE_ESCAPE])
                    {
                        if(window)
                        {
                            SDL_DestroyWindow(window);
                            window = NULL;
                            done =1;
                        }
                    }
                }
            }
//--------------------Above closes based on clicking x or escape key pressed----------
        }
    }

    //Destroy window
    SDL_DestroyWindow( window );
    //Quit SDL subsystems
    SDL_Quit();
    return 1;
}
