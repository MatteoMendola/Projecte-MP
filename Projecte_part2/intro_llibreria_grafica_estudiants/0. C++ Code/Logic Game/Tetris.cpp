#include "./Tetris.h"
#include <iostream>
using namespace std;

void Tetris::inicialitza(int mode, const string& nomFitxer, const string& nomFitxer2, const string& nomFitxer3)
{
    m_partida.inicialitza(mode, nomFitxer, nomFitxer2, nomFitxer3);
}

bool Tetris::juga(int mode, double deltaTime)
{
    bool final = m_partida.actualitza(mode, deltaTime);
    if (final)
    {
        //GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, SCREEN_SIZE_X / 2 - 180, SCREEN_SIZE_Y / 2 - 50, 2.0, "GAME OVER"); //no funciona
    }
    return final;
}

int Tetris::mostraMenu() const
{
    int op;

    cout << " MENU PRINCIPAL" << endl;
    cout << " ==============" << endl;
    cout << " 1. Joc en mode normal" << endl;
    cout << " 2. Joc en mode test" << endl;
    cout << " 3. Mostrar puntuacions" << endl;
    cout << " 4. Sortir" << endl;
    cout << " Selecciona una opcio: " ;
    cin >> op;
    cout << endl;

    return op;
}

void Tetris::mostraPuntuacions()
{
    cout << "Encara no implementat...";
}