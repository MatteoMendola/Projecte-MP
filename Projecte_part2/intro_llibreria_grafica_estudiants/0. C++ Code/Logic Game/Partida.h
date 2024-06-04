#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "./InfoJoc.h"
#include "./Joc.h"

using namespace std;

class Partida 
{
public:
    Partida();
    void inicialitza(int mode, const string& nomFitxer, const string& nomFitxer2, const string& nomFitxer3);
    bool actualitza(int mode, double deltaTime);
private:
    double m_temps;
    Joc m_joc;
    int m_moviments[11];
    int m_figures[7][4];
};

#endif 
