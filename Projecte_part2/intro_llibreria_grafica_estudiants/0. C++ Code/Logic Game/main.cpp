//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "./InfoJoc.h"
#include "./Tetris.h"

int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    //Mostrem la finestra grafica
    pantalla.show();

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    
    Tetris tetris;
    int opcio;
    string fitxerTest = "./data/Games/partida.txt", fitxerFigures = "./data/Games/figures.txt", fitxerMoviments = "./data/Games/moviments.txt", fitxerPuntuacions = "./data/Games/puntuacions.txt";

    do
    {
        opcio = tetris.mostraMenu();

        if (opcio == 1 || opcio == 2)
        {
            tetris.inicialitza(opcio, fitxerTest, fitxerFigures, fitxerMoviments);
            bool final = false;

            do
            {
                LAST = NOW;
                NOW = SDL_GetPerformanceCounter();
                deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

                // Captura tots els events de ratolí i teclat de l'ultim cicle
                pantalla.processEvents();

                final = tetris.juga(opcio, deltaTime);

                // Actualitza la pantalla
                pantalla.update();

            } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !final);
            // Sortim del bucle si pressionem ESC
        }
        else
            if (opcio == 3)
                tetris.mostraPuntuacions();
            else
                if (opcio != 4)
                    cout << " Error: opcio no valida" << endl << endl;
    } while (opcio != 4);

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

