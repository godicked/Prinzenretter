#ifndef MOVABLE_INCLUDED
#define MOVABLE_INCLUDED

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
#include "Spielfeld.h"


class Movable
{
    public:
    Movable(int, int, Spielfeld*);
    void bewegen(int richtung);
    void update();

    Spielfeld *spielfeld;
    int figur_x;
    int figur_y;

    protected:
    // Bewegungs variablen
    bool isMoving = false;  // ob die Figur sich gerade zwichen zwei zellen bewegt
    int speed = 4;  // die Geswindichkeit ( 1, 2, 4, 8, 16, oder 32)
    int direction = 3;  // die Richtung
    int x;  // reale X position im bild
    int y;  // reale Y position im bild
};

Movable::Movable(int startx, int starty, Spielfeld *sp)
{
    figur_x = startx;
    figur_y = starty;
    x = startx * BLOCKX;
    y = starty * BLOCKY;
    spielfeld = sp;
}

void Movable::bewegen(int richtung) {

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
void Movable::update()
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

#endif // MOVABLE_INCLUDED
