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


class Schluessel : public Movable {
    private:
        SDL_Surface *bild;
        Spielfeld *spielfeld;
    public:
        int Richtung;
        bool gefangen;
        Schluessel(int, int, int, char*, Spielfeld*);
        void zeichnen(SDL_Surface *surf);
        void fliehen (int, int, int, int*, int*);
        void fangen (int);
};

Schluessel::Schluessel(int startpositionx, int startpositiony, int direction, char*fn, Spielfeld*SF) : Movable(startpositionx, startpositiony, SF) {
    bild = IMG_Load(fn);
    figur_x = startpositionx;
    figur_y = startpositiony;
    spielfeld = SF;
    Richtung = direction;
    gefangen = false;
}

void Schluessel::zeichnen(SDL_Surface *surf) {
    SDL_Rect schluessel_bildausschnitt;
    SDL_Rect schluessel_zielposition;
    schluessel_bildausschnitt = {x: 0, y: 224, w:32, h:32};
    schluessel_zielposition = {x: x, y: y, w:32, h:32};
    SDL_BlitSurface(bild, &schluessel_bildausschnitt, surf, &schluessel_zielposition);
}

void Schluessel::fliehen (int figurx, int figury, int nummer, int*kx, int*ky) {

    if(isMoving) return;

    int xachse = figurx - figur_x;
    int yachse = figury - figur_y;
    int probe_x = figur_x;
    int probe_y = figur_y;

    bool ungleich = true;
    int richtung = 0;

    if ((yachse <= 0) && (spielfeld->spielfeld[figur_y+1][figur_x]) != '#') {
        richtung = 3;
        probe_y +=1;
    } else if ((yachse >= 0) && (spielfeld->spielfeld[figur_y-1][figur_x]) != '#'){
        richtung = 4;
        probe_y -= 1;
    } else if ((xachse >= 0) && (spielfeld->spielfeld[figur_y][figur_x-1]) != '#') {
        richtung = 2;
        probe_x -= 1;
    } else if ((xachse <= 0) && (spielfeld->spielfeld[figur_y][figur_x+1]) != '#') {
        richtung = 1;
        probe_x += 1;
    }

    for (int o = 0; o < 4; o++){
            if (o != nummer){
                if ((probe_x == kx[o]) && (probe_y == ky[o])){
                    ungleich = false;
    }}}

    if (ungleich == true){
        bewegen(richtung);
        //std::cout << "fliehen" << std::endl;
    }
}

void Schluessel::fangen(int anzahl) {
    figur_x = 25;
    figur_y = anzahl;
    x = figur_x * BLOCKX;
    y = figur_y * BLOCKY;
    gefangen = true;
}

#endif // SCHLUESSEL_H_INCLUDED
