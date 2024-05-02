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

void Figura::getMatriuFormaAct(bool matriuFormaAct[MAX_ALCADA][MAX_AMPLADA]) const
{
	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
			matriuFormaAct[i][j] = m_formaActualEnMatriu[i][j];
	}
}

void Figura::setMatriuFormaAct(bool matriuFormaAct[MAX_ALCADA][MAX_AMPLADA], int longitud)
{
	for (int i = 0; i < longitud; i++)
	{
		for (int j = 0; j < longitud; j++)
			m_formaActualEnMatriu[i][j] = matriuFormaAct[i][j];
	}
}

void Figura::inicialitzarMatriuAuxiliar()
{
	for (int i = 0; i < MAX_ALCADA; i++)	//la inicialitzem tota a false ja que, com els tests es fan seguits, es guarden els true dels tests anteriors
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
			m_formaActualEnMatriu[i][j] = false;
	}

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

void Figura::moureLateralment(int dirX)
{
	switch (dirX)
	{
	case 1: m_posicioActual[1]++;
		break;
	case -1: m_posicioActual[1]--;
		break;
	}
}

void Figura::transposarMatriu(int nCasMax)
{
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	getMatriuFormaAct(matriuAux);

	for (int i = 0; i < nCasMax; i++)
	{
		for (int j = 0; j < nCasMax; j++)
			m_formaActualEnMatriu[i][j] = matriuAux[j][i];
	}
}

void Figura::invertirColumnes(int nCasMax)
{
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	getMatriuFormaAct(matriuAux);
	
	int fixe = 2;

	if (nCasMax == 4)	//si es la figura "I"
	{
		for (int i = 0; i < nCasMax; i++)
		{
			m_formaActualEnMatriu[i][1] = matriuAux[i][fixe];	//intercanviar la 2a i la 3a columna
			m_formaActualEnMatriu[i][fixe] = matriuAux[i][1];	//intercanviar la 3a i la 2a columna
		}
		
		fixe = 3;
	}
		
	for (int i = 0; i < nCasMax; i++)	//per totes les figures (menys el quadrat, que mai entrarà en aquesta funció, ja que no es gira)
	{
		m_formaActualEnMatriu[i][0] = matriuAux[i][fixe];	//intercanviar la primera i la última columna
		m_formaActualEnMatriu[i][fixe] = matriuAux[i][0];	//intercanviar la última i la primera columna;
	}
}

void Figura::invertirFiles(int nCasMax)
{
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	getMatriuFormaAct(matriuAux);

	int fixe = 2;

	if (nCasMax == 4)	//si es la figura "I"
	{
		for (int i = 0; i < nCasMax; i++)
		{
			m_formaActualEnMatriu[1][i] = matriuAux[fixe][i];	//intercanviar la 2a i la 3a fila
			m_formaActualEnMatriu[fixe][i] = matriuAux[1][i];	//intercanviar la 3a i la 2a fila
		}

		fixe = 3;
	}

	for (int i = 0; i < nCasMax; i++)	//per totes les figures (menys el quadrat, que mai entrarà en aquesta funció, ja que no es gira)
	{
		m_formaActualEnMatriu[0][i] = matriuAux[fixe][i];	//intercanviar la primera i la última fila
		m_formaActualEnMatriu[fixe][i] = matriuAux[0][i];	//intercanviar la última i la primera fila
	}
}

void Figura::girarFigura(DireccioGir dir)
{
	if (m_tipus != NO_FIGURA && m_tipus != FIGURA_O)	//si és el quadrat no el girem, ja que es queda igual
	{
		int nCasMax = nombreCaselles(m_tipus);
		transposarMatriu(nCasMax);

		if (m_tipus == FIGURA_I)
			modificarCentreFiguraI(dir);

		switch (dir)
		{
		case GIR_HORARI:
			invertirColumnes(nCasMax);
			if (m_formaActual != 3)
				m_formaActual++;
			else
				m_formaActual = 0;
			break;
		case GIR_ANTI_HORARI:
			invertirFiles(nCasMax);
			if (m_formaActual != 0)
				m_formaActual--;
			else
				m_formaActual = 3;
			break;
		}
	}
}

void Figura::modificarCentreFiguraI(DireccioGir dir)
{
	switch (dir)
	{
	case GIR_HORARI:
		switch (m_formaActual)
		{
		case 0: m_posicioActual[1]++;
			break;
		case 1: m_posicioActual[0]++;
			break;
		case 2: m_posicioActual[1]--;
			break;
		case 3: m_posicioActual[0]--;
			break;
		}
		break;
	case GIR_ANTI_HORARI:
		switch (m_formaActual)
		{
		case 0: m_posicioActual[0]++;
			break;
		case 1: m_posicioActual[1]--;
			break;
		case 2: m_posicioActual[0]--;
			break;
		case 3: m_posicioActual[1]++;
			break;
		}
		break;
	}
}

void Figura::calcularPosicioTauler(int& fila, int& columna) const
{
	fila = m_posicioActual[0];
	columna = m_posicioActual[1];

	switch (nombreCaselles(m_tipus))
	{
	case 2:
	case 3:
		fila -= 1;
		columna -= 1;
		break;
	case 4:
		if (m_formaActual == 0)
		{
			fila -= 1;
			columna -= 1;
		}
		else
			if (m_formaActual == 1)
			{
				fila -= 1;
				columna -= 2;
			}
			else
				if (m_formaActual == 2)
				{
					fila -= 2;
					columna -= 2;
				}
				else
				{
					fila -= 2;
					columna -= 1;
				}
	}
}