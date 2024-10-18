#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h> 
typedef struct serpent serpent; 

struct serpent {
    int x, y;
    char type;
    serpent *next;
};