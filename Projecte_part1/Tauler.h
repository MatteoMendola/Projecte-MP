#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
	//CONSTRUCTOR:
	Tauler() { inicialitzar(); }
	void inicialitzar();

	//GETTER:
	ColorFigura getColorTauler(int fil, int col) const { return m_tauler[fil][col]; }
	
	//SETTER:
	void setColorTauler(ColorFigura color, int fil, int col) { m_tauler[fil][col] = color; }

	//FUNCIONS AUXILIARS:
	void inserirFigura(const Figura& f); //insereix una figura al tauler (si es pot)
	void eliminarFigura(const Figura& f); //elimina una figura del tauler

	//FUNCIONS PRINCIPALS - BAIXAR FIGURA:
	bool comprovarLimitsInferiors(const Figura& f) const; //comprova si una figura pot baixar o no
	void baixaFigura(Figura& f);
	int eliminaFiles(bool filesEliminadesArray[], int longitud, Figura& f); //elimina les files que estan plenes, return: número de files eliminades
	void baixarFiles(bool filesEliminadesArray[], int longitud, int filaFigura, Figura& f); //baixa les files que estan per sobre de les files eliminades

	//FUNCIONS PRINCIPALS - MOURE FIGURA:
	bool comprovarLimitsLaterals(int dirX, const Figura& f) const; //comprova si una figura es pot moure lateralment o no
	void mouFigura(int dirX, Figura& f);

	//FUNCIONS PRINCIPALS - GIRAR FIGURA:
	bool giraFigura(DireccioGir dir, Figura& f); //gira una figura en una direcció, si es pot
private:
	//ATRIBUTS:
	ColorFigura m_tauler[MAX_FILA][MAX_COL];
};

#endif