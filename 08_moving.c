#include <SDL.h>
#include <stdlib.h>

#define TUX_COUNT 16
#define SPEED 2
struct tux {
    SDL_Rect pos;
    int dir_x;
    int dir_y;
};

int main(int argc, char *argv[])
{
    int i;
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
    image = SDL_LoadBMP("tux0.5x.bmp");
    if ( !image )
    {
        fprintf(stderr, "Could not load tux.bmp: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255, 0, 255));

    /*
        We declare the sprites we want to move around on the screen, setting
        random start-positions and directions.
    */
    struct tux tux[TUX_COUNT];
    for(i=0;i<TUX_COUNT;i++)
    {
        tux[i].pos.x = rand() % (screen->w - image->w);
        tux[i].pos.y = rand() % (screen->h - image->h);

        if ( rand() % 2 ) tux[i].dir_x = 1; else tux[i].dir_x = -1;
        if ( rand() % 2 ) tux[i].dir_y = 1; else tux[i].dir_y = -1;
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
            Move application forward
        */
        for(i=0;i<TUX_COUNT;i++)
        {
            /*
                Checking if tux is colliding with the edge of the screen, and 
                changing direction if he is.
            */
            if ( tux[i].pos.x >= screen->w - image->w &&
                 tux[i].dir_x == 1 )
                tux[i].dir_x = -1;
            if ( tux[i].pos.x <= 0 &&
                 tux[i].dir_x == -1 )
                tux[i].dir_x = 1;
            if ( tux[i].pos.y >= screen->h - image->h &&
                 tux[i].dir_y == 1 )
                tux[i].dir_y = -1;
            if ( tux[i].pos.y <= 0 && 
                 tux[i].dir_y == -1 )
                tux[i].dir_y = 1;

            tux[i].pos.x += tux[i].dir_x * SPEED;
            tux[i].pos.y += tux[i].dir_y * SPEED;
        }

        /*
            Draw - drawing an image to the screen.
        */
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        for(i=0;i<TUX_COUNT;i++)
        {
            SDL_BlitSurface(image, NULL, screen, &tux[i].pos);
        }
        SDL_Flip(screen);

        // Wait a little bit - 33ms means approxx. 60 frames per second.
        // If you're using GL, you can rely on Vertical Sync, which will help
        // you avoid tearing.
        SDL_Delay(33);
    }

    SDL_FreeSurface(image);
    exit(EXIT_SUCCESS);
}

