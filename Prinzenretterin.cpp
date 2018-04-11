#ifdef __unix__
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <time.h>
#include <iostream>
#include "Spielfeld.h"
#include "Spielfigur.h"
#include "Raetsel.h"
#include "Schluessel.h"

using namespace std;

int richtung ();

int main(int a, char **b){

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 832, 768, SDL_WINDOW_SHOWN);
    SDL_Surface *surf = SDL_GetWindowSurface(win);

    IMG_Init( IMG_INIT_PNG );
    SDL_Surface *bild = IMG_Load("tiles.png");
    SDL_Surface *anfang = IMG_Load("anfang.png");
    SDL_Surface *verloren = IMG_Load("verloren.png");
    SDL_Surface *uebergang = IMG_Load("uebergang.png");
    SDL_Surface *gewonnen = IMG_Load("gewonnen.png");

    SDL_Surface *raetsel1 = IMG_Load("raetsel1.png");
    SDL_Surface *raetsel2 = IMG_Load("raetsel2.png");
    SDL_Surface *raetsel3 = IMG_Load("raetsel3.png");
    SDL_Surface *raetsel4 = IMG_Load("raetsel4.png");
    SDL_Surface *raetsel[4] = {raetsel1, raetsel2, raetsel3, raetsel4};

    Spielfeld field("tiles.png");
    Spielfigur S1 (7, 6, 1, "tiles.png", &field);

    Schluessel K1 (1, 1, 1, "tiles.png", &field);
    Schluessel K2 (24, 1, 2, "tiles.png", &field);
    Schluessel K3 (1, 22, 3, "tiles.png", &field);
    Schluessel K4 (24, 22, 4, "tiles.png", &field);
    Schluessel K[4] = {K1, K2, K3, K4};

    Raetsel R1 (1, 1, 4, "tiles.png", "raetsel1.png", &field);
    Raetsel R2 (19, 6, 1, "tiles.png", "raetsel2.png", &field);
    Raetsel R3 (20, 18, 3, "tiles.png", "raetsel3.png", &field);
    Raetsel R4 (4, 20, 2, "tiles.png", "raetsel4.png", &field);
    Raetsel R[4] = {R1, R2, R3, R4};

    int Richtung = 4;
    srand(time(NULL));

    int Level = 1;
    int Nummer = 0;

    int m, n;
    int anderex[4];
    int anderey[4];

    int key_counter = 0;

    SDL_Event e;
    bool ende = false;
    while (!ende) {
      Richtung = richtung();
      while ( SDL_PollEvent( &e ) != 0 ) {
        if( e.type == SDL_KEYDOWN ) {
            int taste = e.key.keysym.sym;
            if (taste == SDLK_SPACE) {
                    ende = true;
                }
        }}

        if (Level == 1) {
            SDL_BlitSurface(anfang, NULL, surf, NULL);
            if (Richtung == 1){
                Level++;
                Richtung = 4;
        }}

        if (Level == 2) {
        field.zeichnen(surf);
        S1.bewegen(Richtung);
        S1.update();
        S1.zeichnen(Richtung, surf);

        for (int i=0; i < 4; i++) {
            R[i].zeichnen(surf);
        }
        for (int i=0; i < 4; i++) {
            if ((S1.figur_x == R[i].raetsel_x) && (S1.figur_y == R[i].raetsel_y)){
                    R[i].loesen(Nummer, surf, win);
                    Nummer++;
        }
            if (R[i].falsch == true) {
                Level = 3;
        }}

        if (Nummer == 4){
            field.spielfeld[12][25] = '_';
        }

        if ((S1.figur_x == 25) && (S1.figur_y == 12)){
            Level = 4;
            Richtung = 4;
        }}

        if (Level == 3) {
            SDL_BlitSurface(verloren, NULL, surf, NULL);
        }

        if (Level == 4) {
            SDL_BlitSurface(uebergang, NULL, surf, NULL);
            Nummer = 0;
            field.spielfeld[12][25] = '#';
            S1.figur_x = 7;
            S1.figur_y = 6;
            if (Richtung == 1){
                Level++;
                Richtung = 4;
        }}

        if (Level == 5){
            field.zeichnen(surf);
            S1.bewegen(Richtung);
            S1.update();
            S1.zeichnen(Richtung, surf);

            for (int i=0; i < 4; i++) {
                m = S1.figur_x - K[i].schluessel_x;
                n = S1.figur_y - K[i].schluessel_y;

                if (K[i].gefangen == false && key_counter % 10 == 0){
                    K[i].fliehen(S1.figur_x, S1.figur_y, i, anderex, anderey);

                    if ((m*m == 0) && (n*n == 0)){
                        K[i].fangen(Nummer);
                        Nummer++;
                    }
                }
            }

            key_counter++;

            for (int i=0; i < 4; i++) {
                K[i].zeichnen(surf);
                anderex[i] = K[i].schluessel_x;
                anderey[i] = K[i].schluessel_y;
            }

            if (Nummer == 4){
                field.spielfeld[12][25] = '_';
            }
            if ((S1.figur_x == 25) && (S1.figur_y == 12)){
                Level++;
            }
        }

        if (Level == 6) {
            SDL_BlitSurface(gewonnen, NULL, surf, NULL);
        }

        SDL_UpdateWindowSurface(win);
        SDL_Delay(10);

    }

    return 0;
}

int richtung () {
    int auswahl = 0;

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
    {
        auswahl = 2;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        auswahl = 1;
    }
    if (state[SDL_SCANCODE_UP])
    {
        auswahl = 4;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        auswahl = 3;
    }

    return (auswahl);
}
