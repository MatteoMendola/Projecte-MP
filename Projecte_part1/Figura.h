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

    void setColor(ColorFigura color) { m_color = color; }   //puc posar "const ColorFigura& color"?
    void setTipus(TipusFigura tipus) { m_tipus = tipus; }   //puc posar "const TipusFigura& tipus"?

    //moureLateralmentEsq();
    //moureLateralmentDreta();
    //baixarFigura();
    //girarFigura(DireccioGir dir);
private:
    ColorFigura m_color;
    TipusFigura m_tipus;
    //m_posicioActual;
    //m_formaActual;
};

#endif