#ifndef SPIELFIGUR_H_INCLUDED
#define SPIELFIGUR_H_INCLUDED

#define BLOCKX 32
#define BLOCKY 32

#ifdef __unix__
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#else

#include <SDL.h>
#include <SDL_image.h>
#endif

#include <iostream>
#include <time.h>
#include "Spielfeld.h"
#include "Movable.h"
#include <stdlib.h>

class Spielfigur : public Movable {
    private:
        SDL_Surface *bild;

    public:
        int ausrichtung_figur;
        Spielfigur(int, int, int, char*, Spielfeld*);
        void zeichnen(int, SDL_Surface *surf);
};

Spielfigur::Spielfigur(int startpositionx, int startpositiony, int Richtung, char*fn, Spielfeld*SF) : Movable(startpositionx, startpositiony, SF) {
    bild = IMG_Load(fn);
    figur_x = startpositionx;
    figur_y = startpositiony;
    ausrichtung_figur = Richtung;
    spielfeld = SF;
}



void Spielfigur::zeichnen(int ausrichtung_figur, SDL_Surface *surf) {
    SDL_Rect figur_bildausschnitt;
    SDL_Rect figur_zielposition;

    int diffx = abs(figur_x * BLOCKX - x);
    int diffy = abs(figur_y * BLOCKY - y);

    int diff = diffx > diffy ? diffx : diffy;

    // geteilt durch 16 für 2 Bilder, geteilt durch 8 für 4 Bilder
    int imgx = diff / 16;

    figur_bildausschnitt = {x: imgx * 32, y: direction*32 + 64, w:32, h:32};
    //figur_zielposition = {x: figur_x*32, y: figur_y*32, w:32, h:32};
    figur_zielposition = {x: x, y: y, w:BLOCKX, h:BLOCKY};
    SDL_BlitSurface(bild, &figur_bildausschnitt, surf, &figur_zielposition);
}

#endif // SPIELFIGUR_H_INCLUDED
