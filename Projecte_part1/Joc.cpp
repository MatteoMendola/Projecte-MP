#include "Joc.h"
#include <fstream>

TipusFigura Joc::convertirEnTipusFigura(int tipus) const
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

ColorFigura Joc::convertirEnColorFigura(int color) const
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

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		int tipusAux, fila, columna, nGirs;
		fitxer >> tipusAux >> fila >> columna >> nGirs;
		
		m_figuraActual.setTipus(convertirEnTipusFigura(tipusAux));
		m_figuraActual.setPosActFil(fila);
		m_figuraActual.setPosActCol(columna);
		//m_figuraActual.setFormaAct(gir);	això ho modifiquem a l'hora d'inserir la figura, que es quan es gira
		m_figuraActual.setColor(convertirEnColorFigura(tipusAux));
		m_figuraActual.inicialitzarMatriuAuxiliar();
		m_figuraActual.girarFigura(GIR_HORARI, nGirs);

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

		m_tauler.inserirFigura(m_figuraActual);

		fitxer.close();
	}
}

bool Joc::giraFigura(DireccioGir direccio)
{

}

bool Joc::mouFigura(int dirX)
{

}

int Joc::baixaFigura()
{

}

void Joc::escriuTauler(const string& nomFitxer)
{

}