#include "Tauler.h"

void Tauler::inserirFigura(const Figura& f)	//afegir comentaris explicatius
{
	bool esPotInserir = true;
	int fila = f.getPosActFil(), columna = f.getPosActCol(), forma = f.getFormaAct();
	
	switch (f.getTipus())
	{
	case FIGURA_O:
		if (fila < 0 || fila > MAX_FILA - 1 || columna < 0 || columna > MAX_COL - 1)
			esPotInserir = false;
		break;
	case FIGURA_I:
		if (forma == 0 || forma == 2)
		{
			if (fila < 0 || fila > MAX_FILA - 1)
				esPotInserir = false;
			if ((forma == 0 && (columna - 2 < 0 || columna + 1 > MAX_COL - 1)) || (forma == 2 && (columna - 1 < 0 || columna + 2 > MAX_COL - 1)))
				esPotInserir = false;
		}
		else
		{
			if (columna < 0 || columna > MAX_COL - 1)
				esPotInserir = false;
			if ((forma == 1 && (fila - 2 < 0 || fila + 1 > MAX_FILA - 1)) || (forma == 3 && (fila - 1 < 0 || fila + 2 > MAX_FILA - 1)))
				esPotInserir = false;
		}
		break;
	case FIGURA_T:
	case FIGURA_L:
	case FIGURA_J:
	case FIGURA_Z:
	case FIGURA_S:
		if (forma == 0)
		{
			if (fila - 1 < 0 || fila > MAX_FILA - 1 || columna - 1 < 0 || columna + 1 > MAX_COL - 1)
				esPotInserir = false;
		}
		else
			if (forma == 1)
			{
				if (fila - 1 < 0 || fila + 1 > MAX_FILA - 1 || columna < 0 || columna + 1 > MAX_COL - 1)
					esPotInserir = false;
			}
			else
				if (forma == 2)
				{
					if (fila < 0 || fila + 1 > MAX_FILA - 1 || columna - 1 < 0 || columna + 1 > MAX_COL - 1)
						esPotInserir = false;
				}
				else    //forma == 3
				{
					if (fila - 1 < 0 || fila + 1 > MAX_FILA - 1 || columna - 1 < 0 || columna > MAX_COL - 1)
						esPotInserir = false;
				}
		break;
	}

	int nCasMax = f.nombreCaselles(f.getTipus());
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);
	int i = 0, j = 0;

	while (i < nCasMax && esPotInserir)
	{
		while (j < nCasMax && esPotInserir)
		{
			if (matriuAux[i][j])
			{
				if (m_tauler[fila + i][columna + j] != COLOR_NEGRE)
					esPotInserir = false;
			}
			j++;
		}

		j = 0;
		i++;
	}

	if (esPotInserir)
	{
		ColorFigura color = f.getColor();

		for (i = 0; i < nCasMax; i++)
		{
			for (j = 0; j < nCasMax; j++)
			{
				if (matriuAux[i][j])
					m_tauler[fila + i][columna + j] = color;
			}
		}
	}
}

void Tauler::eliminarFigura(const Figura& f)
{
	int nCasMax = f.nombreCaselles(f.getTipus());
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

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
	f.calcularPosicioTauler(fila, columna);

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
					if (!matriuAux[i + 1][j])	//si a sota la peça no hi ha peça
					{
						if (m_tauler[fila + i + 1][columna + j] != COLOR_NEGRE || (fila + i + 1) == MAX_FILA)	//comprovar si la posició sota la peça està buida o si ens trobem a la última fila del tauler
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
				if (m_tauler[filaI + 1][columna + j] != COLOR_NEGRE || (filaI + 1) == MAX_FILA)	//comprovar si la posició sota la peça està buida o si ens trobem a la última fila del tauler
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

void Tauler::baixaFigura(Figura& f)
{
	int nCasMax = f.nombreCaselles(f.getTipus());
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	for (int i = nCasMax - 1; i >= 0; i--)
	{
		for (int j = 0; j < nCasMax; j++)
		{
			if (matriuAux[i][j])
			{
				m_tauler[fila + i + 1][columna + j] = m_tauler[fila + i][columna + j];
				m_tauler[fila + i][columna + j] = COLOR_NEGRE;
			}
		}
	}

	f.baixarFigura();
}

bool Tauler::comprovarLimitsLaterals(int dirX, const Figura& f)	//pensar com optimitzar aquesta funció
{
	int nCasMax = f.nombreCaselles(f.getTipus());
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	int i = 0, j = 0;
	bool aux = true;

	switch (dirX)
	{
	case 1:
		if (f.getTipus() != FIGURA_I)
		{
			while (i < nCasMax && aux)	//fem una cerca en la matriu 
			{
				while (j < nCasMax && aux)
				{
					if (matriuAux[i][j])	//si hi ha peça
					{
						if (!matriuAux[i][j + 1])	//si a la dreta de la peça no hi ha peça
						{
							if (m_tauler[fila + i][columna + j + 1] != COLOR_NEGRE || (columna + j + 1) == MAX_COL)	//comprovar si la posició a la dreta de la peça està buida o si ens trobem a la última columna del tauler
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

				if (m_tauler[filaI][columna + 4] != COLOR_NEGRE || (columna + 4) == MAX_COL)	//estan totes les peces en la mateixa fila, només hem de comprovar que a la dreta de la última peça estigui buit o si ens trobem a la última columna del tauler
					aux = false;
			}
			else    //la "I" està en vertical
			{
				int columnaI = f.getPosActCol();

				while (i < nCasMax && aux)	//estan totes les peces en la mateixa columna, hem de recórrer les files
				{
					if (m_tauler[fila + i][columnaI + 1] != COLOR_NEGRE || (columnaI + 1) == MAX_COL)	//comprovar si la posició a la dreta de la peça està buida o si ens trobem a la última columna del tauler
						aux = false;
					i++;
				}
			}
		break;
	case -1:
		if (f.getTipus() != FIGURA_I)
		{
			while (i < nCasMax && aux)	//fem una cerca en la matriu 
			{
				while (j < nCasMax && aux)
				{
					if (matriuAux[i][j])	//si hi ha peça
					{
						if (!matriuAux[i][j - 1] || (columna + j - 1) == -1)	//si a la esquerra de la peça no hi ha peça o si ens trobem a la primera columna del tauler
						{
							if (m_tauler[fila + i][columna + j - 1] != COLOR_NEGRE || (columna + j - 1) == -1)	//comprovar si la posició a la esquerra de la peça està buida o si ens trobem a la primera columna del tauler
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

				if (m_tauler[filaI][columna - 1] != COLOR_NEGRE || (columna - 1) == -1)	//estan totes les peces en la mateixa fila, només hem de comprovar que a la esquerra de la primera peça estigui buit o si ens trobem a la primera columna del tauler
					aux = false;
			}
			else    //la "I" està en vertical
			{
				int columnaI = f.getPosActCol();

				while (i < nCasMax && aux)	//estan totes les peces en la mateixa columna, hem de recórrer les files
				{
					if (m_tauler[fila + i][columnaI - 1] != COLOR_NEGRE || (columnaI - 1) == -1)	//comprovar si la posició a la esquerra de la peça està buida o si ens trobem a la primera columna del tauler
						aux = false;
					i++;
				}
			}
		break;
	}

	return aux;
}

bool Tauler::comprovarLimitsGir(DireccioGir dir, Figura& f)	//afegir explicacions
{
	bool aux = true;
	int fila = f.getPosActFil(), columna = f.getPosActCol(), forma = f.getFormaAct();
	TipusFigura tipus = f.getTipus();

	if ((forma == 0 && fila == (MAX_FILA - 1)) || (tipus == FIGURA_I && forma == 0 && fila == 0))
		aux = false;
	else
		if ((forma == 1 && columna == 0) || (tipus == FIGURA_I && forma == 1 && columna == (MAX_COL - 1)))
			aux = false;
		else
			if ((forma == 2 && fila == 0) || (tipus == FIGURA_I && forma == 2 && fila == (MAX_FILA - 1)))
				aux = false;
			else
				if ((forma == 3 && columna == (MAX_COL - 1)) || (tipus == FIGURA_I && forma == 3 && columna == 0))
					aux = false;
				else
				{
					int nCasMax = f.nombreCaselles(tipus);
					eliminarFigura(f);
					f.girarFigura(dir);
					if (tipus == FIGURA_I)
						f.modificarCentreFiguraI(dir);
					bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
					f.getMatriuFormaAct(matriuAux);

					fila = 0, columna = 0;
					f.calcularPosicioTauler(fila, columna);
					int i = 0, j = 0;

					if (fila < 0)
						fila = 0;
					if (columna < 0)
						columna = 0;

					while (i < nCasMax && aux)
					{
						while (j < nCasMax && aux)
						{
							if (matriuAux[i][j])
							{
								if (m_tauler[fila + i][columna + j] != COLOR_NEGRE)
									aux = false;
							}
							j++;
						}

						j = 0;
						i++;
					}

					switch (dir)
					{
					case GIR_HORARI:
						f.girarFigura(GIR_ANTI_HORARI);
						if (tipus == FIGURA_I)
							f.modificarCentreFiguraI(GIR_ANTI_HORARI);
						break;
					case GIR_ANTI_HORARI:
						f.girarFigura(GIR_HORARI);
						if (tipus == FIGURA_I)
							f.modificarCentreFiguraI(GIR_HORARI);
						break;
					}

					inserirFigura(f);
				}

	return aux;
}

int Tauler::eliminaFiles(bool filesEliminadesArray[], int longitud, Figura& f)
{
	int filesEliminades = 0, j = 0;
	bool casellaNegre = false, hiHaPeça = false;

	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	for (int i = 0; i < longitud; i++)
	{
		while (j < longitud && !hiHaPeça)
		{
			if (matriuAux[i][j])
				hiHaPeça = true;

			j++;
		}

		if (hiHaPeça)
		{
			j = 0;
			hiHaPeça = false;

			while (j < MAX_COL && !casellaNegre)
			{
				if (m_tauler[fila + i][j] == COLOR_NEGRE)
					casellaNegre = true;

				j++;
			}

			if (!casellaNegre)
			{
				for (j = 0; j < MAX_COL; j++)
					m_tauler[fila + i][j] = COLOR_NEGRE;
				for (j = 0; j < longitud; j++)
					matriuAux[i][j] = false;
				filesEliminades++;
				filesEliminadesArray[i] = true;
			}
			else
			{
				filesEliminadesArray[i] = false;
				casellaNegre = false;
			}
		}
		else
			filesEliminadesArray[i] = false;

		j = 0;
	}

	f.setMatriuFormaAct(matriuAux, longitud);
	return filesEliminades;
}

void Tauler::baixarFiles(bool filesEliminadesArray[], int longitud, int filaFigura, Figura& f)
{
	int cont = 0;
	
	for (int i = 0; i < longitud; i++)
	{
		if (filesEliminadesArray[i])
		{
			f.baixarFigura();

			for (int aux = filaFigura + i; aux > 0; aux--)
			{
				for (int j = 0; j < MAX_COL; j++)
					m_tauler[aux][j] = m_tauler[aux - 1][j];
			}

			for (int j = 0; j < MAX_COL; j++)
				m_tauler[cont][j] = COLOR_NEGRE;
		}
	}
}