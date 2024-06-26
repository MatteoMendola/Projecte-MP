#ifndef FIGURA_H
#define FIGURA_H
#include "./InfoJoc.h"
#include "./GraphicManager.h"

/*
typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;

typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S,
} TipusFigura;
*/

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

class Figura
{
public:
    //CONSTRUCTOR:
    Figura() { inicialitzar(); }
    void inicialitzar();

    //GETTERS:
    ColorFigura getColor() const { return m_color; }
    TipusFigura getTipus() const { return m_tipus; }
    int getPosActFil() const { return m_posicioActual[0]; }
    int getPosActCol() const { return m_posicioActual[1]; }
    int getFormaAct() const { return m_formaActual; }
    void getMatriuFormaAct(bool matriuFormaAct[MAX_ALCADA][MAX_AMPLADA]) const;

    //SETTERS:
    void setColor(ColorFigura color) { m_color = color; }
    void setTipus(TipusFigura tipus) { m_tipus = tipus; }
    void setPosActFil(int fila) { m_posicioActual[0] = fila; }
    void setPosActCol(int col) { m_posicioActual[1] = col; }
    void setFormaAct(int formaAct) { m_formaActual = formaAct; }
    void setMatriuFormaAct(bool matriuFormaAct[MAX_ALCADA][MAX_AMPLADA], int longitud);

    //FUNCIONS AUXILIARS:
    void inicialitzarMatriuAuxiliar(); //s'inicialitza la matriu auxiliar sense girs depenent de la figura
    int nombreCaselles(TipusFigura tipus) const; //nombre m�xim de caselles en horitzontal o en vertical que pot arribar a ocupar una figura (lletra I = 4, O = 2, la resta = 3)
    void calcularPosicioTauler(int& fila, int& columna) const; //calcula la primera posici� del tauler on comen�a la figura (cantonada
                                                               //superior esquerra) a partir del centre de la figura depenent del tipus
                                                               //de figura que sigui
    //FUNCIONS PRINCIPALS:
    void baixarFigura() { m_posicioActual[0]++; }
    void moureLateralment(int dirX); //-1 esq, +1 dreta
    void girarFigura(DireccioGir dir);
    void dibuixa() const;
private:
    //ATRIBUTS:
    ColorFigura m_color;
    TipusFigura m_tipus;
    int m_posicioActual[2]; //array que guarda les coordenades del centre de la figura dins del tauler, primera posici�: fila, segona posici�: columna
    int m_formaActual; //0 � 3, segons ordre dels girs en sentit horari a la descripci� de les figures (p�gina 8 del pwp de la 1a part)
    bool m_formaActualEnMatriu[MAX_ALCADA][MAX_AMPLADA]; //matriu que guarda la forma de la figura, true = hi ha pe�a, false = no hi ha
    
    //FUNCIONS AUXILIARS:
    void transposarMatriu(int nCasMax); //per girar les figures
    void invertirColumnes(int nCasMax); //per girar les figures
    void invertirFiles(int nCasMax); //per girar les figures
    void modificarCentreFiguraI(DireccioGir dir); //modifica el centre de la FIGURA_I
};

#endif