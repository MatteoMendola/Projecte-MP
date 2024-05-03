#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

class Joc
{
public:
	//CONSTRUCTOR:
	Joc();

	//FUNCIONS PRINCIPALS - LLEGIR I ESCRIURE:
	void inicialitza(const string& nomFitxer); //inicialitza una l'estat d'una partida a partir d'un fitxer
	void escriuTauler(const string& nomFitxer); //escriu l'estat d'una partida a un fitxer
	
	//FUNCIONS PRINCIPALS:
	bool mouFigura(int dirX); //retorna un booleà depenent si la figura s'ha pogut moure o no
	int baixaFigura(); //retorna un 'int' amb el nombre de files eliminades
	bool giraFigura(DireccioGir direccio); //retorna un booleà depenent si la figura s'ha pogut girar o no
private:
	//ATRIBUTS:
	Tauler m_tauler;
	Figura m_figuraActual;

	//FUNCIONS AUXILIARS:
	TipusFigura convertirEnTipusFigura(int tipus) const; //transforma un 'int' en un 'TipusFigura', per la funció d'inicialitzar a partir d'un fitxer
	ColorFigura convertirEnColorFigura(int color) const; //transforma un 'int' en un 'ColorFigura', per la funció d'inicialitzar a partir d'un fitxer
};

#endif