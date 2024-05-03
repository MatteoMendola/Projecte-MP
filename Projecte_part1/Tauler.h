#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
	Tauler() { inicialitzar(); }
	void inicialitzar();

	ColorFigura getColorTauler(int fil, int col) const { return m_tauler[fil][col]; }
	void setColorTauler(ColorFigura color, int fil, int col) { m_tauler[fil][col] = color; }

	void inserirFigura(const Figura& f);
	void eliminarFigura(const Figura& f);

	bool comprovarLimitsInferiors(const Figura& f) const;
	void baixaFigura(Figura& f);
	int eliminaFiles(bool filesEliminadesArray[], int longitud, Figura& f);
	void baixarFiles(bool filesEliminadesArray[], int longitud, int filaFigura, Figura& f);

	bool comprovarLimitsLaterals(int dirX, const Figura& f) const;
	void mouFigura(int dirX, Figura& f);

	bool comprovarLimitsGir(DireccioGir dir, Figura& f);
private:
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
};

#endif