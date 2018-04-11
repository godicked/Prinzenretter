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

class Spielfigur {
    private:
        SDL_Surface *bild;
        Spielfeld *spielfeld;

        // Bewegungs variablen
        bool isMoving;  // ob die Figur sich gerade zwichen zwei zellen bewegt
        int speed = 4;  // die Geswindichkeit ( 1, 2, 4, 8, 16, oder 32)
        int direction = 3;  // die Richtung
        int x;  // reale X position im bild
        int y;  // reale Y position im bild

    public:
        int figur_x;
        int figur_y;
        int ausrichtung_figur;
        Spielfigur(int, int, int, char*, Spielfeld*);
        void zeichnen(int, SDL_Surface *surf);
        void bewegen(int richtung);
        void update();
};

Spielfigur::Spielfigur(int startpositionx, int startpositiony, int Richtung, char*fn, Spielfeld*SF) {
    bild = IMG_Load(fn);
    figur_x = startpositionx;
    figur_y = startpositiony;
    ausrichtung_figur = Richtung;
    spielfeld = SF;
}

void Spielfigur::bewegen(int richtung) {

    // Wenn sich die Figur zwischen zwei Zellen ist wird die bewegung erst zu ende gebracht
    if(isMoving) return;

    x = BLOCKX * figur_x;
    y = BLOCKY * figur_y;

    if ((richtung == 4) && (spielfeld->free(figur_y-1, figur_x)))
    {
        //figur_y -= 1;
        isMoving = true;
    }
    else if ((richtung == 3) && (spielfeld->free(figur_y+1, figur_x)))
    {
        //figur_y += 1;
        isMoving = true;
    }
    else if ((richtung == 1) && (spielfeld->free(figur_y, figur_x+1)))
    {
        //figur_x += 1;
        isMoving = true;
    }
    else if ((richtung == 2) && (spielfeld->free(figur_y, figur_x-1)))
    {
        //figur_x -= 1;
        isMoving = true;
    }

    if (isMoving)
    {
        direction = richtung;
    }
}

// Bewegen der Figur wenn nötig
void Spielfigur::update()
{
    // wenn die figur sich nicht bewegt ist nichts zu machen
    if(!isMoving) return;

    switch(direction)
    {
        case 1:
            x += speed;
            break;
        case 2:
            x -= speed;
            break;
        case 3:
            y += speed;
            break;
        case 4:
            y -= speed;
            break;
    }
    // Wenn die Figur auf der nächsten Zelle angekommen ist endet die Bewegung
    if( x % BLOCKX == 0 && y % BLOCKY == 0)
    {
        isMoving = false;
        figur_x = x / BLOCKX;
        figur_y = y / BLOCKY;
    }
}

void Spielfigur::zeichnen(int ausrichtung_figur, SDL_Surface *surf) {
    SDL_Rect figur_bildausschnitt;
    SDL_Rect figur_zielposition;
    figur_bildausschnitt = {x: 0, y: direction*32 + 64, w:32, h:32};
    //figur_zielposition = {x: figur_x*32, y: figur_y*32, w:32, h:32};
    figur_zielposition = {x: x, y: y, w:BLOCKX, h:BLOCKY};
    SDL_BlitSurface(bild, &figur_bildausschnitt, surf, &figur_zielposition);
}

#endif // SPIELFIGUR_H_INCLUDED
