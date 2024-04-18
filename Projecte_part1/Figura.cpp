#include "Figura.h"

Figura::Figura()
{
	m_color = NO_COLOR;
	m_tipus = NO_FIGURA;
	m_posicioActual[0] = 0;
	m_posicioActual[1] = 0;
	m_formaActual = 0;
}

void Figura::moureLateralment(int dirX)
{
	switch (dirX)
	{
	case 1: m_posicioActual[1]--;
		break;
	case -1: m_posicioActual[1]++;
		break;
	}
}

void Figura::girarFigura(DireccioGir dir)
{
	switch (dir)
	{
	case GIR_HORARI:
		if (m_formaActual != 3)
			m_formaActual++;
		else
			m_formaActual = 0;
		break;
	case GIR_ANTI_HORARI:
		if (m_formaActual != 0)
			m_formaActual--;
		else
			m_formaActual = 3;
		break;
	}
}

int Figura::nombreCaselles(TipusFigura tipus) const
{	
	int nCas = 0;

	switch (tipus)
	{
	case FIGURA_O: nCas = 2;
		break;
	case FIGURA_I: nCas = 4;
		break;
	case FIGURA_T:
	case FIGURA_L:
	case FIGURA_J:
	case FIGURA_Z:
	case FIGURA_S: nCas = 3;
		break;
	}

	return nCas;
}