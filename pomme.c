#include <stdlib.h>
#include "struct.h"
#include <SDL2/SDL.h>

int estSurSerpent(Serpent* serpent, int x, int y) {
    Segment* segment = serpent->tete;
    while (segment != NULL) {
        if (segment->x == x && segment->y == y) {
            return 1;
        }
        segment = segment->next;
    }
    return 0;
}

void initialiserPomme(Pomme* pomme, int largeurFenetre, int hauteurFenetre, Serpent* serpent) {
    do {
        pomme->x = (rand() % (largeurFenetre / 32)) * 32;
        pomme->y = (rand() % (hauteurFenetre / 32)) * 32;
    } while (estSurSerpent(serpent, pomme->x, pomme->y));
}

void afficherPomme(SDL_Renderer* renderer, Pomme* pomme) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {pomme->x, pomme->y, 32, 32};
    SDL_RenderFillRect(renderer, &rect);
}
