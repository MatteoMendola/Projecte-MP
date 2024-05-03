#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

class Joc
{
public:
	Joc();

	void inicialitza(const string& nomFitxer);
	void escriuTauler(const string& nomFitxer);
	
	bool mouFigura(int dirX);
	int baixaFigura();
	bool giraFigura(DireccioGir direccio);
private:
	Tauler m_tauler;
	Figura m_figuraActual;

	TipusFigura convertirEnTipusFigura(int tipus) const;
	ColorFigura convertirEnColorFigura(int color) const;
};

#endif