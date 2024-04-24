#ifndef FIGURA_H
#define FIGURA_H

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
    Figura();

    ColorFigura getColor() const { return m_color; }
    TipusFigura getTipus() const { return m_tipus; }
    int getPosActFil() const { return m_posicioActual[0]; }
    int getPosActCol() const { return m_posicioActual[1]; }
    int getFormaAct() const { return m_formaActual; }
    void getMatriuFormaAct(bool matriuFormaAct[MAX_ALCADA][MAX_AMPLADA]) const;

    void setColor(ColorFigura color) { m_color = color; }
    void setTipus(TipusFigura tipus) { m_tipus = tipus; }
    void setPosActFil(int fila) { m_posicioActual[0] = fila; }
    void setPosActCol(int col) { m_posicioActual[1] = col; }
    void setFormaAct(int formaAct) { m_formaActual = formaAct; }

    void inicialitzarMatriuAuxiliar();  //s'inicialitza la matriu auxiliar sense girs
    int nombreCaselles(TipusFigura tipus) const;    //nombre màxim de caselles en horitzontal o vertical que pot arribar a ocupar una figura (lletra I = 4, O = 2, la resta = 3)
    void moureLateralment(int dirX); //+1 esq, -1 dreta
    void baixarFigura() { m_posicioActual[0]++; }
    void girarFigura(DireccioGir dir);
private:
    ColorFigura m_color;
    TipusFigura m_tipus;
    int m_posicioActual[2]; //array que guarda les coordenades del centre de la figura dins del tauler, primera posició: fila, segona posició: columna
    int m_formaActual;  //0 – 3, segons ordre dels girs en sentit horari a la descripció de les figures (pàgina 8 del pwp de la 1a part)
    bool m_formaActualEnMatriu[MAX_ALCADA][MAX_AMPLADA];    //matriu que guarda la forma de la figura, true = hi ha peça, false = no hi ha
    void transposarMatriu(int nCasMax);
    void invertirColumnes(int nCasMax);
    void invertirFiles(int nCasMax);
};

#endif