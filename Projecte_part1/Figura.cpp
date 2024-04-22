#include "Figura.h"

Figura::Figura()
{
	m_color = NO_COLOR;
	m_tipus = NO_FIGURA;
	m_posicioActual[0] = 0;
	m_posicioActual[1] = 0;
	m_formaActual = 0;
	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
			m_formaActualEnMatriu[i][j] = false;
	}
}

void Figura::inicialitzarMatriuAuxiliar()
{
	switch (m_tipus)
	{
	case FIGURA_O:
		m_formaActualEnMatriu[0][0] = true;
		m_formaActualEnMatriu[0][1] = true;
		m_formaActualEnMatriu[1][0] = true;
		m_formaActualEnMatriu[1][1] = true;
		break;
	case FIGURA_I:
		m_formaActualEnMatriu[1][0] = true;
		m_formaActualEnMatriu[1][1] = true;
		m_formaActualEnMatriu[1][2] = true;
		m_formaActualEnMatriu[1][3] = true;
		break;
	case FIGURA_T:
		m_formaActualEnMatriu[0][1] = true;
		m_formaActualEnMatriu[1][0] = true;
		m_formaActualEnMatriu[1][1] = true;
		m_formaActualEnMatriu[1][2] = true;
		break;
	case FIGURA_L:
		m_formaActualEnMatriu[0][2] = true;
		m_formaActualEnMatriu[1][0] = true;
		m_formaActualEnMatriu[1][1] = true;
		m_formaActualEnMatriu[1][2] = true;
		break;
	case FIGURA_J:
		m_formaActualEnMatriu[0][0] = true;
		m_formaActualEnMatriu[1][0] = true;
		m_formaActualEnMatriu[1][1] = true;
		m_formaActualEnMatriu[1][2] = true;
		break;
	case FIGURA_Z:
		m_formaActualEnMatriu[0][0] = true;
		m_formaActualEnMatriu[0][1] = true;
		m_formaActualEnMatriu[1][1] = true;
		m_formaActualEnMatriu[1][2] = true;
		break;
	case FIGURA_S:
		m_formaActualEnMatriu[0][1] = true;
		m_formaActualEnMatriu[0][2] = true;
		m_formaActualEnMatriu[1][0] = true;
		m_formaActualEnMatriu[1][1] = true;
		break;
	}
}

void Figura::getMatriuFormaAct(bool matriuFormaAct[MAX_ALCADA][MAX_AMPLADA]) const
{
	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
			matriuFormaAct[i][j] = m_formaActualEnMatriu[i][j];
	}
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
	if (m_tipus != NO_FIGURA && m_tipus != FIGURA_O)	//si és el quadrat no el girem, ja que es queda igual
	{
		int casMax = nombreCaselles(m_tipus);
		bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
		getMatriuFormaAct(matriuAux);

		if (casMax == 3)
		{
			for (int i = 0; i < casMax; i++)	//transposar
			{
				for (int j = 0; j < casMax; j++)
				{
					m_formaActualEnMatriu[i][j] = matriuAux[j][i];
				}
			}
		}
		else //nCasMax == 4 (no hi ha més casos)
		{
			for (int i = 0; i < casMax; i++)	//transposar
			{
				for (int j = 0; j < casMax; j++)
				{
					m_formaActualEnMatriu[i][j] = matriuAux[j][i];
				}
			}
		}

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