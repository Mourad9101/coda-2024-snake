#ifndef STRUCT_H
#define STRUCT_H

#include <SDL2/SDL.h> 

typedef struct Segment {
    int x, y;
    struct Segment* next;
} Segment;

typedef struct {
    Segment* tete;
} Serpent;

typedef struct {
    int x, y;
} Pomme;

void afficherSerpent(SDL_Renderer* renderer, Serpent* serpent);
void initialiserSerpent(Serpent* serpent);
void ajouterSegment(Serpent* serpent);
void libererSerpent(Serpent* serpent);
void initialiserPomme(Pomme* pomme, int largeurFenetre, int hauteurFenetre, Serpent* serpent);
void deplacerSerpent(Serpent* serpent, int direction);

int estSurSerpent(Serpent* serpent, int x, int y);
int estCollision(Serpent* serpent);

void afficherPomme(SDL_Renderer* renderer, Pomme* pomme);

#endif

