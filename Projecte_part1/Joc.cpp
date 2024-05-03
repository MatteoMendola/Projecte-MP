#include "Joc.h"
#include <fstream>

Joc::Joc()
{
	m_figuraActual.inicialitzar(); 
	m_tauler.inicialitzar();
}

TipusFigura Joc::convertirEnTipusFigura(int tipus) const //transforma un 'int' en un 'TipusFigura', per la funció d'inicialitzar a partir d'un fitxer
{
	TipusFigura t = NO_FIGURA;

	switch (tipus)
	{
	case FIGURA_O: t = FIGURA_O;
		break;
	case FIGURA_I: t = FIGURA_I;
		break;
	case FIGURA_T: t = FIGURA_T;
		break;
	case FIGURA_L: t = FIGURA_L;
		break;
	case FIGURA_J: t = FIGURA_J;
		break;
	case FIGURA_Z: t = FIGURA_Z;
		break;
	case FIGURA_S: t = FIGURA_S;
		break;
	}

	return t;
}

ColorFigura Joc::convertirEnColorFigura(int color) const //transforma un 'int' en un 'ColorFigura', per la funció d'inicialitzar a partir d'un fitxer
{
	ColorFigura c = NO_COLOR;
	
	switch (color)
	{
	case COLOR_NEGRE: c = COLOR_NEGRE;
		break;
	case COLOR_GROC: c = COLOR_GROC;
		break;
	case COLOR_BLAUCEL: c = COLOR_BLAUCEL;
		break;
	case COLOR_MAGENTA: c = COLOR_MAGENTA;
		break;
	case COLOR_TARONJA: c = COLOR_TARONJA;
		break;
	case COLOR_BLAUFOSC: c = COLOR_BLAUFOSC;
		break;
	case COLOR_VERMELL: c = COLOR_VERMELL;
		break;
	case COLOR_VERD: c = COLOR_VERD;
		break;
	}

	return c;
}

void Joc::inicialitza(const string& nomFitxer) //inicialitza una l'estat d'una partida a partir d'un fitxer
{
	ifstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		int tipusAux, fila, columna, nGirs;
		fitxer >> tipusAux >> fila >> columna >> nGirs;
		
		//primer, els atributs de la figuraActual:
		m_figuraActual.setTipus(convertirEnTipusFigura(tipusAux));
		m_figuraActual.setPosActFil(fila);
		m_figuraActual.setPosActCol(columna);
		m_figuraActual.setFormaAct(0);	//això ho modifiquem a l'hora de girar la figura
		m_figuraActual.setColor(convertirEnColorFigura(tipusAux));
		m_figuraActual.inicialitzarMatriuAuxiliar();
		for (int i = 0; i < nGirs; i++)
			m_figuraActual.girarFigura(GIR_HORARI); //girem la figura

		//inicialitzem el tauler:
		ColorFigura color;
		int colorAux;
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer >> colorAux;
				color = convertirEnColorFigura(colorAux);
				m_tauler.setColorTauler(color, i, j);
			}
		}

		m_tauler.inserirFigura(m_figuraActual); //inserim la figura

		fitxer.close();
	}
}

bool Joc::giraFigura(DireccioGir direccio) //retorna un booleà depenent si la figura s'ha pogut girar o no
{
	bool valid = false;

	if (m_figuraActual.getTipus() != FIGURA_O) //només girem si la figura no és la O (el quadrat), ja que es queda igual
		valid = m_tauler.giraFigura(direccio, m_figuraActual); //girem la figura, si es pot
	
	return valid;
}

bool Joc::mouFigura(int dirX) //retorna un booleà depenent si la figura s'ha pogut moure o no
{
	bool valid = m_tauler.comprovarLimitsLaterals(dirX, m_figuraActual); //comprova si es pot moure o no

	if (valid) //si es pot moure
		m_tauler.mouFigura(dirX, m_figuraActual); //mou la figura

	return valid;
}

int Joc::baixaFigura() //retorna un 'int' amb el nombre de files eliminades
{
	if (m_tauler.comprovarLimitsInferiors(m_figuraActual)) //comprova si es pot baixar o no
		m_tauler.baixaFigura(m_figuraActual); //baixa la figura

	int nCasMax = m_figuraActual.nombreCaselles(m_figuraActual.getTipus()); //màxim de peces que ocupa la figura
	int fila = 0, noUse = 0;
	m_figuraActual.calcularPosicioTauler(fila, noUse);
	
	bool filesEliminadesArray[MAX_ALCADA]; //array que indica si una fila ha estat eliminada o no (els índexs son les files)
	int filesEliminades = m_tauler.eliminaFiles(filesEliminadesArray, nCasMax, m_figuraActual); //elimina les files que es puguin eliminar
	
	if (filesEliminades > 0) //si s'han eliminat files
		m_tauler.baixarFiles(filesEliminadesArray, nCasMax, fila, m_figuraActual); //baixa les files que calgui a partir de les eliminades
		
	return filesEliminades;
}

void Joc::escriuTauler(const string& nomFitxer) //escriu l'estat d'una partida a un fitxer
{
	ofstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
				fitxer << m_tauler.getColorTauler(i, j) << " ";
			fitxer << endl;
		}

		fitxer.close();
	}
}