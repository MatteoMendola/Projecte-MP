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

void Joc::inserirFigura(Figura& f, int nGirs)
{
	if (f.getTipus() != NO_FIGURA)
	{
		//inserir figura
		/*
		for (int i = 0; i < nGirs; i++)
		{
			m_tauler.giraFigura(f, GIR_HORARI);
		}
		*/
	}
}

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		int tipusAux, fila, columna, nGirs;
		fitxer >> tipusAux >> fila >> columna >> nGirs;
		TipusFigura tipus = convertirEnTipusFigura(tipusAux);

		m_figuraActual.setTipus(tipus);
		m_figuraActual.setPosActFil(fila);
		m_figuraActual.setPosActCol(columna);
		m_figuraActual.setFormaAct(0);
		m_figuraActual.setColor(convertirEnColorFigura(tipus));

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

		inserirFigura(m_figuraActual, nGirs);

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