#include <SDL.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /*
        SDL_Init initializes SDL, and take the subsystems to initialize
        as a parameter.  If it returns a non-NULL value, it has failed.
    */
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        /*
            SDL_GetError() returns a pointer to a string, explaining what
            the last set SDL-error is.  It is not necessarily fatal.
        */
        fprintf(stderr,"Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    /*
        We want to call SDL_Quit() when we tell the application to exit().

        ... exit / atexit are stdlib-stuff.
    */
    atexit(SDL_Quit);

    /*
        Everything you can draw on in SDL, is an SDL_Surface.

        This includes the application window.
    */
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    if ( !screen )
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*
        We typically want to load the graphics before we end up in the loop.
    */
    SDL_Surface *image;
    image = SDL_LoadBMP("tux.bmp");
    if ( !image )
    {
        fprintf(stderr, "Could not load tux.bmp: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*
        A simple loop.
    */
    int quit = 0;
    while(!quit)
    {
        /*
            Input - we do some very basic input handling.
        */
        SDL_Event e;
        /*
            From the SDL_PollEvent man-page:
                Polls for currently pending events, and returns 1 if there are
                any pending events, or 0 if there are none available.

                If event is not NULL, the next event is removed from the queue
                and stored in that area.

            This is where you handle any input.
        */
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                /*
                    Happens when the user attempts to close the window.
                    We want to make sure that this results in the application
                    stopping.
                */
                case SDL_QUIT:
                    quit = 1;
                break;
                /*
                    If there are any unhandled events, we can do some default
                    handling, e.g. log them or whatever.  Doing nothing for 
                    now.
                    For a complete list of event types, check the SDL_Event man
                    page.
                */
                default:
                break;
            }
        }

        /*
            Move application forward - we implement this later.
        */

        /*
            Draw - we implement this later.
        */

        // Wait a little bit - 33ms means approxx. 60 frames per second.
        // If you're using GL, you can rely on Vertical Sync, which will help
        // you avoid tearing.
        SDL_Delay(33);
    }

    SDL_FreeSurface(image);
    exit(EXIT_SUCCESS);
}

