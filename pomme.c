#include "struct.h"
#include <stdlib.h>
#include <time.h>

void genererPomme(Pomme* pomme, int largeur, int hauteur) {
    pomme->x = rand() % (largeur / 32);
    pomme->y = rand() % (hauteur / 32);
}

void afficherPomme(Pomme* pomme, SDL_Renderer* renderer) {
    SDL_Rect rect = {pomme->x * 32, pomme->y * 32, 32, 32};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
