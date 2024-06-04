#include "./Partida.h"

class Tetris
{
public:
    void inicialitza(int mode, const string& nomFitxer, const string& nomFitxer2, const string& nomFitxer3);
    bool juga(int mode, double deltaTime);
    int mostraMenu() const;
    void mostraPuntuacions();
private:
    Partida m_partida;
};
