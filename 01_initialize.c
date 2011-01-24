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

    exit(EXIT_SUCCESS);
}

