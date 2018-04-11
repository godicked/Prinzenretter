#ifndef RAETSEL_H_INCLUDED
#define RAETSEL_H_INCLUDED

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

int richtung ();

class Raetsel {
    private:
        SDL_Surface *bild;
        SDL_Surface *raetsel;
        Spielfeld *spielfeld;
    public:
        int raetsel_x;
        int raetsel_y;
        int loesung;
        bool falsch;
        Raetsel(int, int, int, char*, char*, Spielfeld*);
        void zeichnen(SDL_Surface *surf);
        void loesen(int, SDL_Surface *surf, SDL_Window *win);
};

Raetsel::Raetsel(int positionx, int positiony, int richtung, char*fn, char*fr, Spielfeld*SF) {
    bild = IMG_Load(fn);
    raetsel = IMG_Load(fr);
    raetsel_x = positionx;
    raetsel_y = positiony;
    loesung = richtung;
    spielfeld = SF;
    falsch = false;
}

void Raetsel::zeichnen(SDL_Surface *surf) {
    SDL_Rect raetsel_bildausschnitt;
    SDL_Rect raetsel_zielposition;
    raetsel_bildausschnitt = {x: 0, y: 256, w:32, h:32};
    raetsel_zielposition = {x: raetsel_x*32, y: raetsel_y*32, w:32, h:32};
    SDL_BlitSurface(bild, &raetsel_bildausschnitt, surf, &raetsel_zielposition);
}

void Raetsel::loesen(int anzahl, SDL_Surface *surf, SDL_Window *win) {
    SDL_Event e;
    bool ende = false;
    int direction = 0;
    bool init = false; // Der spieler muss erst mal alle Tasten loslassen

    while (!ende) {

      // Hat der spieler seit der letzen Bewegung die tasten losgelassen ?
      direction = richtung();
      if(direction == 0)
      {
        // Wenn ja, dann kann die nächste Eingabe als Antwort akzeptiert werden.
        init = true;
      }

      while ( SDL_PollEvent( &e ) != 0) {
        if( e.type == SDL_KEYDOWN ) {
            int taste = e.key.keysym.sym;
            direction = richtung();
            if (direction == 10) {
                    ende = true;
            }
        }}

        SDL_BlitSurface(raetsel, NULL, surf, NULL);

        if (loesung == direction && init){
            raetsel_x = 25;
            raetsel_y = anzahl;
            ende = true;
        } else if (direction != 0 && init) {
            falsch = true;
            ende = true;
        }

        SDL_UpdateWindowSurface(win);
        SDL_Delay(10);
}}

#endif // RAETSEL_H_INCLUDED
