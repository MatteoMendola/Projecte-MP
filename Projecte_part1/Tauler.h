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

	void inserirFigura(const Figura& f);
	void eliminarFigura(const Figura& f);
	bool comprovarLimitsInferiors(const Figura& f);	//si retorna true, la figura pot baixar, si retorna false, no
	bool comprovarLimitsLaterals(int dirX, const Figura& f);	//si retorna true, la figura es pot moure, si retorna false, no
private:
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
	
	void calcularPosicioTauler(int nCasMax, int& fila, int& columna, const Figura& f) const;	//calcula la primera posició del tauler on comença la figura (cantonada
																								//superior esquerra) a partir del centre de la figura depenent del tipus
																								//de figura que sigui
};

#endif