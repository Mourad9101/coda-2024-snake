#include "struct.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

void initialiserSerpent(Serpent* serpent) {
    serpent->tete = (Segment*)malloc(sizeof(Segment));
    serpent->tete->x = 4;
    serpent->tete->y = 4;
    serpent->tete->suivant = NULL;
    serpent->longueur = 1;
}

void ajouterSegment(Serpent* serpent) {
    Segment* nouveauSegment = (Segment*)malloc(sizeof(Segment));
    nouveauSegment->x = serpent->tete->x;
    nouveauSegment->y = serpent->tete->y;
    nouveauSegment->suivant = serpent->tete;
    serpent->tete = nouveauSegment;
    serpent->longueur++;
}

bool estSurSerpent(Serpent* serpent, int x, int y) {
    Segment* courant = serpent->tete;
    while (courant != NULL) {
        if (courant->x == x && courant->y == y) {
            return true;
        }
        courant = courant->suivant;
    }
    return false;
}

void deplacerSerpent(Serpent* serpent, int nouvelleX, int nouvelleY) {
    Segment* courant = serpent->tete;
    int precedentX, precedentY;

    precedentX = courant->x;
    precedentY = courant->y;
    courant->x = nouvelleX;
    courant->y = nouvelleY;
    courant = courant->suivant;

    while (courant != NULL) {
        int tempX = courant->x;
        int tempY = courant->y;
        courant->x = precedentX;
        courant->y = precedentY;
        precedentX = tempX;
        precedentY = tempY;
        courant = courant->suivant;
    }
}

void libererSerpent(Serpent* serpent) {
    Segment* courant = serpent->tete;
    while (courant != NULL) {
        Segment* temp = courant;
        courant = courant->suivant;
        free(temp);
    }
    serpent->tete = NULL;
    serpent->longueur = 0;
}

void afficherSerpent(Serpent* serpent, SDL_Renderer* renderer) {
    Segment* courant = serpent->tete;
    while (courant != NULL) {
        SDL_Rect rect = {courant->x * 32, courant->y * 32, 32, 32};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        courant = courant->suivant;
    }
}
