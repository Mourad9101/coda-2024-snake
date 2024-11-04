#include "struct.h"

void afficherTexte(SDL_Renderer* renderer, const char* message, TTF_Font* font, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

bool serpentSeToujours(Serpent* serpent, int nouvelleX, int nouvelleY) {
    Segment* courant = serpent->tete->suivant;
    while (courant != NULL) {
        if (courant->x == nouvelleX && courant->y == nouvelleY) {
            return true;
        }
        courant = courant->suivant;
    }
    return false;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 24);
    Serpent serpent;
    initialiserSerpent(&serpent);

    Pomme pomme;
    srand(time(NULL));
    genererPomme(&pomme, 800, 800);

    bool running = true;
    bool gameOver = false;
    SDL_Event event;
    int directionX = 1, directionY = 0;
    int directionPrecedenteX = directionX;
    int directionPrecedenteY = directionY;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        if (directionPrecedenteY != 1) {
                            directionX = 0; directionY = -1;
                        }
                        break;
                    case SDLK_DOWN:
                        if (directionPrecedenteY != -1) {
                            directionX = 0; directionY = 1;
                        }
                        break;
                    case SDLK_LEFT:
                        if (directionPrecedenteX != 1) {
                            directionX = -1; directionY = 0;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (directionPrecedenteX != -1) { 
                            directionX = 1; directionY = 0;
                        }
                        break;
                }
            }
        }

        int nouvelleTeteX = serpent.tete->x + directionX;
        int nouvelleTeteY = serpent.tete->y + directionY;

        if (nouvelleTeteX < 0 || nouvelleTeteX >= 800 / 32 || 
            nouvelleTeteY < 0 || nouvelleTeteY >= 800 / 32 || 
            serpentSeToujours(&serpent, nouvelleTeteX, nouvelleTeteY)) {
            gameOver = true;
        } else {

            deplacerSerpent(&serpent, nouvelleTeteX, nouvelleTeteY);

            if (serpent.tete->x == pomme.x && serpent.tete->y == pomme.y) {
                ajouterSegment(&serpent);
                genererPomme(&pomme, 800, 800);
            }

            directionPrecedenteX = directionX;
            directionPrecedenteY = directionY;

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            afficherSerpent(&serpent, renderer);
            afficherPomme(&pomme, renderer);

            if (gameOver) {
                SDL_Color textColor = {255, 0, 0, 255};
                afficherTexte(renderer, "Game Over! Vous vous êtes mordu.", font, textColor, 100, 400);
            }

            SDL_RenderPresent(renderer);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect bordure = {0, 0, 800, 800};
        SDL_RenderDrawRect(renderer, &bordure);

        SDL_Delay(125);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    libererSerpent(&serpent);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
