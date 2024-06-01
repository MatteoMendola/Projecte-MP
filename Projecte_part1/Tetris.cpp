#include "Tetris.h"

int Tetris::mostraMenu()
{
    int op;

    cout << "MENU" << endl;
    cout << "1 - Mode NORMAL" << endl;
    cout << "2 - Mode TEST" << endl;
    cout << "3 - Llista de millors puntuacions" << endl;
    cout << "4 - SORTIR" << endl;
    cout << "Selecciona una opcio: " ;
    cin >> op;

    return op;
}
