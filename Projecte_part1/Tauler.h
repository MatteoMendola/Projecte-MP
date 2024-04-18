#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:

	ColorFigura getColorTauler(int fil, int col) const { return m_tauler[fil][col]; }

	void setColorTauler(ColorFigura color, int fil, int col) { m_tauler[fil][col] = color; }

	void giraFigura(Figura& f, DireccioGir dir);
private:
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
};

#endif