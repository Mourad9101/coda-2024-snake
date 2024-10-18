#include <stdlib.h>
#include <stdio.h>
#include "struct.h"

void initialiserSerpent(Serpent* serpent) {
    serpent->tete = malloc(sizeof(Segment));
    serpent->tete->x = 12;
    serpent->tete->y = 15;
    Segment* segment2 = malloc(sizeof(Segment));
    segment2->x = 13;
    segment2->y = 15;
    serpent->tete->next = segment2;

    Segment* segment3 = malloc(sizeof(Segment));
    segment3->x = 14;
    segment3->y = 15;
    segment2->next = segment3;

    segment3->next = NULL;
}

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

int estCollision(Serpent* serpent) {
    if (estSurSerpent(serpent, serpent->tete->x, serpent->tete->y)) {
        return 1;
    }

    if (serpent->tete->x < 0 || serpent->tete->x >= (800 / 32) || 
        serpent->tete->y < 0 || serpent->tete->y >= (800 / 32)) {
        return 1;
    }

    return 0;
}

void deplacerSerpent(Serpent* serpent, int direction) {
    if (serpent->tete == NULL) return; 

    int ancienX = serpent->tete->x;
    int ancienY = serpent->tete->y;

    switch (direction) {
        case 0:
            serpent->tete->x += 1;
            break;
        case 1:
            serpent->tete->x -= 1;
            break;
        case 2:
            serpent->tete->y -= 1;
            break;
        case 3:
            serpent->tete->y += 1;
            break;
    }

    if (estCollision(serpent)) {
        printf("Collision !\n");
        return;
    }
    Segment* segmentActuel = serpent->tete->next;
    Segment* segmentPrecedent = serpent->tete;

    while (segmentActuel != NULL) {
        int tempX = segmentActuel->x;
        int tempY = segmentActuel->y;

        segmentActuel->x = ancienX;
        segmentActuel->y = ancienY;

        ancienX = tempX;
        ancienY = tempY;

        segmentPrecedent = segmentActuel;
        segmentActuel = segmentActuel->next;
    }
}