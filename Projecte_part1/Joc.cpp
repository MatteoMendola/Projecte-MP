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
		m_figuraActual.setFormaAct(0);	//això ho modifiquem a l'hora de girar la figura
		m_figuraActual.setColor(convertirEnColorFigura(tipusAux));
		m_figuraActual.inicialitzarMatriuAuxiliar();
		for (int i = 0; i < nGirs; i++)
			m_figuraActual.girarFigura(GIR_HORARI);

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

bool Joc::giraFigura(DireccioGir direccio)	//afegir explicacions
{
	bool valid = false;

	if (m_figuraActual.getTipus() != FIGURA_O)
	{
		valid = m_tauler.comprovarLimitsGir(direccio, m_figuraActual);

		if (valid)
		{
			m_tauler.eliminarFigura(m_figuraActual);
			m_figuraActual.girarFigura(direccio);
			m_tauler.inserirFigura(m_figuraActual);
		}
	}
	
	return valid;
}

bool Joc::mouFigura(int dirX)
{
	bool valid = m_tauler.comprovarLimitsLaterals(dirX, m_figuraActual);

	if (valid)
		m_tauler.mouFigura(dirX, m_figuraActual);

	return valid;
}

int Joc::baixaFigura()
{
	if (m_tauler.comprovarLimitsInferiors(m_figuraActual))
		m_tauler.baixaFigura(m_figuraActual);

	int nCasMax = m_figuraActual.nombreCaselles(m_figuraActual.getTipus()), fila = 0, noUse = 0;
	m_figuraActual.calcularPosicioTauler(fila, noUse);
	bool filesEliminadesArray[MAX_ALCADA];
	int filesEliminades = m_tauler.eliminaFiles(filesEliminadesArray, nCasMax, m_figuraActual);
	if (filesEliminades > 0)
		m_tauler.baixarFiles(filesEliminadesArray, nCasMax, fila, m_figuraActual);
		
	return filesEliminades;
}

void Joc::escriuTauler(const string& nomFitxer)
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