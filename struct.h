#ifndef STRUCT_H
#define STRUCT_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct Segment {
    int x;
    int y;
    struct Segment* suivant;
} Segment;

typedef struct {
    Segment* tete;
    int longueur;
} Serpent;

typedef struct {
    int x;
    int y;
} Pomme;

void initialiserSerpent(Serpent* serpent);
void ajouterSegment(Serpent* serpent);
bool estSurSerpent(Serpent* serpent, int x, int y);
void deplacerSerpent(Serpent* serpent, int nouvelleX, int nouvelleY);
void libererSerpent(Serpent* serpent);
void afficherSerpent(Serpent* serpent, SDL_Renderer* renderer);
void genererPomme(Pomme* pomme, int largeur, int hauteur);
void afficherPomme(Pomme* pomme, SDL_Renderer* renderer);

#endif
