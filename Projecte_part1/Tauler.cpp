#include "Tauler.h"

void Tauler::calcularPosicioTauler(int nCasMax, int& fila, int& columna, const Figura& f) const
{
	fila = f.getPosActFil();
	columna = f.getPosActCol();

	switch (nCasMax)
	{
	case 2:
		break;
	case 3:
		fila -= 1;
		columna -= 1;
		break;
	case 4:
		if (f.getFormaAct() == 0)
		{
			fila -= 1;
			columna -= 2;
		}
		else
			if (f.getFormaAct() == 1)
			{
				fila -= 2;
				columna -= 2;
			}
			else
				if (f.getFormaAct() == 2)
				{
					fila -= 2;
					columna -= 1;
				}
				else
				{
					fila -= 1;
					columna -= 1;
				}
	}
}

void Tauler::inserirFigura(const Figura& f)
{
	int nCasMax = f.nombreCaselles(f.getTipus());
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	ColorFigura color = f.getColor();
	calcularPosicioTauler(nCasMax, fila, columna, f);

	for (int i = 0; i < nCasMax; i++)
	{
		for (int j = 0; j < nCasMax; j++)
		{
			if (matriuAux[i][j])
				m_tauler[fila + i][columna + j] = color;
		}
	}
}

void Tauler::eliminarFigura(const Figura& f)
{
	int nCasMax = f.nombreCaselles(f.getTipus());
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	calcularPosicioTauler(nCasMax, fila, columna, f);

	for (int i = 0; i < nCasMax; i++)
	{
		for (int j = 0; j < nCasMax; j++)
		{
			if (matriuAux[i][j])
				m_tauler[fila + i][columna + j] = COLOR_NEGRE;
		}
	}
}

bool Tauler::comprovarLimitsInferiors(const Figura& f)
{
	int nCasMax = f.nombreCaselles(f.getTipus());
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	calcularPosicioTauler(nCasMax, fila, columna, f);

	int i = 0, j = 0;
	bool aux = true;

	if (f.getTipus() != FIGURA_I)
	{
		while (i < nCasMax && aux)	//fem una cerca en la matriu 
		{
			while (j < nCasMax && aux)
			{
				if (matriuAux[i][j])	//si hi ha peça
				{
					if (!matriuAux[i + 1][j])	//si a sota de la peça no hi ha peça
					{
						if (m_tauler[fila + i + 1][columna + j] != COLOR_NEGRE || (fila + i + 1) == MAX_FILA)	//comprovar si la posició sota de la peça està buida o si ens trobem a la última fila del tauler
							aux = false;
					}
				}
				j++;
			}

			j = 0;
			i++;
		}
	}
	else    //figura "I"
		if (f.getFormaAct() == 0 || f.getFormaAct() == 2)	//la "I" està en horitzontal
		{
			int filaI = f.getPosActFil();

			while (j < nCasMax && aux)	//estan totes les peces en la mateixa fila, hem de recórrer les columnes
			{
				if (m_tauler[filaI + 1][columna + j] != COLOR_NEGRE || (filaI + 1) == MAX_FILA)	//comprovar si la posició sota de la peça està buida o si ens trobem a la última fila del tauler
					aux = false;
				j++;
			}
		}
		else    //la "I" està en vertical
		{
			int columnaI = f.getPosActCol();

			if (m_tauler[fila + 4][columnaI] != COLOR_NEGRE || (fila + 4) == MAX_FILA)	//estan totes les peces en la mateixa columna, només hem de comprovar que sota la última peça estigui buit o si ens trobem a la última fila del tauler
				aux = false;
		}

	return aux;
}