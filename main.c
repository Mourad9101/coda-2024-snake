#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "struct.h"

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("SNAKE GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialisation du serpent
    Serpent serpent;
    initialiserSerpent(&serpent);
    int direction = -1; 
    int lastDirection = -1; 
    ajouterSegment(&serpent);

    // Initialisation de la pomme
    Pomme pomme;
    initialiserPomme(&pomme, 800, 800, &serpent);

    // Variables pour le timing
    Uint32 startTime = SDL_GetTicks();
    int deplacementIntervalle = 125;

    // Boucle principale
    SDL_bool running = SDL_TRUE;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = SDL_FALSE;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT && lastDirection != 1) {
                    direction = 0;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT && lastDirection != 0) {
                    direction = 1;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_UP && lastDirection != 3) {
                    direction = 2;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && lastDirection != 2) {
                    direction = 3;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - startTime > deplacementIntervalle) {
            deplacerSerpent(&serpent, direction);
            if (direction != -1) {
                lastDirection = direction;
            }
            startTime = currentTime;
        }

        // Efface l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Affichage du serpent et de la pomme
        afficherSerpent(renderer, &serpent);
        afficherPomme(renderer, &pomme);

        SDL_RenderPresent(renderer);
    }

    libererSerpent(&serpent);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
