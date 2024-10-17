#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        printf("Error SDL2 Init : %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) 
    {
        printf("Erreur d'initialisation de la SDL_Image\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_OPENGL);

    if (window == NULL) 
    {
        printf("Error while creating a window : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) 
    {
        printf("Erreur à la création du renderer\n");
        return 1;
    }

    SDL_Surface* surface = IMG_Load("back.png");
    if (surface == NULL) 
    {
        printf("Error loading image %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) 
    {
        printf("Error creating texture\n");
        return 1;
    }

    SDL_FreeSurface(surface);   

    while(1)
    {
        SDL_Event e;
        if (SDL_WaitEvent(&e)) 
        {
            if (e.type == SDL_QUIT) 
            {
                SDL_FreeSurface(surface);
                SDL_QUIT;
                break;
            }
        }

        SDL_Rect rect = {0, 0, 900, 900};

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderPresent(renderer);
    }


    SDL_Quit();
    return 0; 
}
