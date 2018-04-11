#ifndef SCHLUESSEL_H_INCLUDED
#define SCHLUESSEL_H_INCLUDED

#ifdef __unix__
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <iostream>
#include <time.h>
#include "Spielfeld.h"


class Schluessel {
    private:
        SDL_Surface *bild;
        Spielfeld *spielfeld;
    public:
        int schluessel_x;
        int schluessel_y;
        int Richtung;
        bool gefangen;
        Schluessel(int, int, int, char*, Spielfeld*);
        void zeichnen(SDL_Surface *surf);
        void fliehen (int, int, int, int*, int*);
        void fangen (int);
};

Schluessel::Schluessel(int startpositionx, int startpositiony, int direction, char*fn, Spielfeld*SF) {
    bild = IMG_Load(fn);
    schluessel_x = startpositionx;
    schluessel_y = startpositiony;
    spielfeld = SF;
    Richtung = direction;
    gefangen = false;
}

void Schluessel::zeichnen(SDL_Surface *surf) {
    SDL_Rect schluessel_bildausschnitt;
    SDL_Rect schluessel_zielposition;
    schluessel_bildausschnitt = {x: 0, y: 224, w:32, h:32};
    schluessel_zielposition = {x: schluessel_x*32, y: schluessel_y*32, w:32, h:32};
    SDL_BlitSurface(bild, &schluessel_bildausschnitt, surf, &schluessel_zielposition);
}

void Schluessel::fliehen (int figurx, int figury, int nummer, int*kx, int*ky) {
    int xachse = figurx - schluessel_x;
    int yachse = figury - schluessel_y;
    int probe_x = schluessel_x;
    int probe_y = schluessel_y;

    bool ungleich = true;

    if ((yachse <= 0) && (spielfeld->spielfeld[schluessel_y+1][schluessel_x]) != '#') {
        probe_y += 1;
    } else if ((yachse >= 0) && (spielfeld->spielfeld[schluessel_y-1][schluessel_x]) != '#'){
        probe_y -= 1;
    } else if ((xachse >= 0) && (spielfeld->spielfeld[schluessel_y][schluessel_x-1]) != '#') {
        probe_x -= 1;
    } else if ((xachse <= 0) && (spielfeld->spielfeld[schluessel_y][schluessel_x+1]) != '#') {
        probe_x += 1;
    }

    for (int o = 0; o < 4; o++){
            if (o != nummer){
                if ((probe_x == kx[o]) && (probe_y == ky[o])){
                    ungleich = false;
    }}}

    if (ungleich == true){
        schluessel_x = probe_x;
        schluessel_y = probe_y;
    }
}

void Schluessel::fangen(int anzahl) {
    schluessel_x = 25;
    schluessel_y = anzahl;
    gefangen = true;
}

#endif // SCHLUESSEL_H_INCLUDED
