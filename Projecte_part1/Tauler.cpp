#include "Tauler.h"

void Tauler::inicialitzar()
{
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
			m_tauler[i][j] = COLOR_NEGRE;
	}
}

void Tauler::inserirFigura(const Figura& f)	//insereix una figura al tauler (si es pot)
{
	bool esPotInserir = true;
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);
	
	if (fila < 0 || fila > MAX_FILA - 1 || columna < 0 || columna > MAX_COL - 1) //comprova si la figura est� fora dels l�mits del tauler
		esPotInserir = false;

	if (esPotInserir)
	{
		int nCasMax = f.nombreCaselles(f.getTipus()); //m�xim de peces que ocupa la figura
		bool matriuAux[MAX_ALCADA][MAX_AMPLADA]; //matriu de la figura a inserir
		f.getMatriuFormaAct(matriuAux);
		int i = 0, j = 0;

		while (i < nCasMax && esPotInserir) //fem una cerca de la matriu mirant si on volem inserir-la al tauler ja hi ha peces o no
		{
			while (j < nCasMax && esPotInserir)
			{
				if (matriuAux[i][j]) //si la matriu t� pe�a
				{
					if (m_tauler[fila + i][columna + j] != COLOR_NEGRE) //comprova si la posici� on va la pe�a est� plena o no
						esPotInserir = false;
				}
				j++;
			}

			j = 0;
			i++;
		}

		if (esPotInserir) //insereix la figura
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
}

void Tauler::eliminarFigura(const Figura& f) //elimina una figura del tauler
{
	int nCasMax = f.nombreCaselles(f.getTipus()); //m�xim de peces que ocupa la figura
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA]; //matriu de la figura
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	for (int i = 0; i < nCasMax; i++)
	{
		for (int j = 0; j < nCasMax; j++)
		{
			if (matriuAux[i][j]) //si hi ha pe�a
				m_tauler[fila + i][columna + j] = COLOR_NEGRE; //eliminem del tauler
		}
	}
}

bool Tauler::comprovarLimitsInferiors(const Figura& f) const //comprova si una figura pot baixar o no
{
	int nCasMax = f.nombreCaselles(f.getTipus()); //m�xim de peces que ocupa la figura
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA]; //matriu de la figura
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	int i = 0, j = 0;
	bool aux = true;

	while (i < nCasMax && aux)	//fem una cerca en la matriu 
	{
		while (j < nCasMax && aux)
		{
			if (matriuAux[i][j])	//si hi ha pe�a
			{
				if (!matriuAux[i + 1][j])	//si a sota la pe�a no hi ha pe�a
				{
					if (m_tauler[fila + i + 1][columna + j] != COLOR_NEGRE || (fila + i + 1) == MAX_FILA)	//comprova si la posici� sota la pe�a est� buida o si ens trobem a la �ltima fila del tauler
						aux = false;
				}
			}
			j++;
		}

		j = 0;
		i++;
	}

	return aux;
}

void Tauler::baixaFigura(Figura& f)
{
	int nCasMax = f.nombreCaselles(f.getTipus()); //m�xim de peces que ocupa la figura
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA]; //matriu de la figura
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	for (int i = nCasMax - 1; i >= 0; i--) //rec�rrer la figura d'abaix a dalt
	{
		for (int j = 0; j < nCasMax; j++)
		{
			if (matriuAux[i][j]) //si hi ha pe�a
			{
				m_tauler[fila + i + 1][columna + j] = m_tauler[fila + i][columna + j]; //baixem la pe�a
				m_tauler[fila + i][columna + j] = COLOR_NEGRE; //buidem la posici� on estaba la pe�a que hem baixat
			}
		}
	}

	f.baixarFigura(); //modifiquem la posici� (la fila y la columna) de la figura
}

int Tauler::eliminaFiles(bool filesEliminadesArray[], int longitud, Figura& f) //elimina les files que estan plenes, return: n�mero de files eliminades
{
	int filesEliminades = 0, j = 0;
	bool casellaNegre = false, hiHaPeca = false;

	bool matriuAux[MAX_ALCADA][MAX_AMPLADA]; //matriu de la figura
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	for (int i = 0; i < longitud; i++) //rec�rrem les files de la matriu
	{
		while (j < longitud && !hiHaPeca) //cerquem si hi ha una pe�a
		{
			if (matriuAux[i][j])
				hiHaPeca = true;

			j++;
		}

		if (hiHaPeca) //si hi ha pe�a, comprovem si aquella fila del tauler est� plena o no
		{
			j = 0;
			hiHaPeca = false;

			while (j < MAX_COL && !casellaNegre) //cerca de la fila
			{
				if (m_tauler[fila + i][j] == COLOR_NEGRE) //si hi ha alguna posici� buida, no es pot eliminar la fila
					casellaNegre = true;

				j++;
			}

			if (!casellaNegre) //si no hi ha cap casella negre (la fila est� plena - s'ha d'eliminar)
			{
				for (j = 0; j < MAX_COL; j++)
					m_tauler[fila + i][j] = COLOR_NEGRE; //eliminem la fila
				for (j = 0; j < longitud; j++)
					matriuAux[i][j] = false; //tamb� eliminem la fila en la matriu auxiliar de la (clase) figura
				filesEliminades++; //aumentem el nombre de files eliminades
				filesEliminadesArray[i] = true; //en l'array de les files que hem eliminat, marquem l'actual com a eliminada (true)
			}
			else
			{ //si la fila no est� plena
				filesEliminadesArray[i] = false; //en l'array de les files que hem eliminat, marquem l'actual com a buida (false)
				casellaNegre = false;
			}
		}
		else //en cas de que no hi hagi cap pe�a en aquesta fila de la matriu, hem de marcar en l'array de files que hem eliminat que la fila est� buida (false)
			filesEliminadesArray[i] = false;

		j = 0;
	}

	f.setMatriuFormaAct(matriuAux, longitud); //actualitzem la posici� de la matriu auxiliar de la figura
	return filesEliminades;
}

void Tauler::baixarFiles(bool filesEliminadesArray[], int longitud, int filaFigura, Figura& f) //baixa les files que estan per sobre de les files eliminades
{
	int cont = 0;

	for (int i = 0; i < longitud; i++) //rec�rrem l'array de les files eliminades
	{
		if (filesEliminadesArray[i]) //si la fila ha estat eliminada
		{
			f.baixarFigura(); //baixem la figura (modificar la posici�)

			for (int fila = filaFigura + i; fila > 0; fila--)
			{
				for (int j = 0; j < MAX_COL; j++)	//baixem totes les files que estaven per sobre de la fila eliminada, comen�ant des d'abaix fins a dalt
					m_tauler[fila][j] = m_tauler[fila - 1][j];
			}

			for (int j = 0; j < MAX_COL; j++) //posem la fila que queda m�s amunt en negre (eliminada), ja que s'ha baixat i s'ha quedat buida
				m_tauler[cont][j] = COLOR_NEGRE;

			cont++;
		}
	}
}

bool Tauler::comprovarLimitsLaterals(int dirX, const Figura& f)	const //comprova si una figura es pot moure lateralment o no
{
	int nCasMax = f.nombreCaselles(f.getTipus()); //m�xim de peces que ocupa la figura
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA]; //matriu de la figura
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	int i = 0, j = 0;
	bool aux = true;

	switch (dirX)
	{
	case 1: //cap a la dreta
		if (f.getTipus() != FIGURA_I) //per la figura I ho fem diferent
		{
			while (i < nCasMax && aux) //fem una cerca en la matriu 
			{
				while (j < nCasMax && aux)
				{
					if (matriuAux[i][j]) //si hi ha pe�a
					{
						if (!matriuAux[i][j + 1]) //si a la dreta de la pe�a no hi ha pe�a
						{
							if (m_tauler[fila + i][columna + j + 1] != COLOR_NEGRE || (columna + j + 1) == MAX_COL) //comprovar si la posici� a la dreta de la pe�a est� buida o si ens trobem a la �ltima columna del tauler
								aux = false;
						}
					}
					j++;
				}

				j = 0;
				i++;
			}
		}
		else //figura "I"
			if (f.getFormaAct() == 0 || f.getFormaAct() == 2) //la "I" est� en horitzontal
			{
				int filaI = f.getPosActFil();

				if (m_tauler[filaI][columna + 4] != COLOR_NEGRE || (columna + 4) == MAX_COL) //estan totes les peces en la mateixa fila, nom�s hem de comprovar que a la dreta de la �ltima pe�a estigui buit o si ens trobem a la �ltima columna del tauler
					aux = false;
			}
			else //la "I" est� en vertical
			{
				int columnaI = f.getPosActCol();

				while (i < nCasMax && aux) //estan totes les peces en la mateixa columna, hem de rec�rrer les files
				{
					if (m_tauler[fila + i][columnaI + 1] != COLOR_NEGRE || (columnaI + 1) == MAX_COL) //comprovar si la posici� a la dreta de la pe�a est� buida o si ens trobem a la �ltima columna del tauler
						aux = false;
					i++;
				}
			}
		break;
	case -1: //cap a l'esquerra
		if (f.getTipus() != FIGURA_I) //per la figura I ho fem diferent
		{
			while (i < nCasMax && aux) //fem una cerca en la matriu 
			{
				while (j < nCasMax && aux)
				{
					if (matriuAux[i][j]) //si hi ha pe�a
					{
						if (!matriuAux[i][j - 1] || j == 0) //si a la esquerra de la pe�a no hi ha pe�a o si ens trobem a la primera columna del tauler
						{
							if (m_tauler[fila + i][columna + j - 1] != COLOR_NEGRE || (columna + j - 1) == -1) //comprovar si la posici� a la esquerra de la pe�a est� buida o si ens trobem a la primera columna del tauler
								aux = false;
						}
					}
					j++;
				}

				j = 0;
				i++;
			}
		}
		else //figura "I"
			if (f.getFormaAct() == 0 || f.getFormaAct() == 2) //la "I" est� en horitzontal
			{
				int filaI = f.getPosActFil();

				if (m_tauler[filaI][columna - 1] != COLOR_NEGRE || (columna - 1) == -1) //estan totes les peces en la mateixa fila, nom�s hem de comprovar que a la esquerra de la primera pe�a estigui buit o si ens trobem a la primera columna del tauler
					aux = false;
			}
			else //la "I" est� en vertical
			{
				int columnaI = f.getPosActCol();

				while (i < nCasMax && aux) //estan totes les peces en la mateixa columna, hem de rec�rrer les files
				{
					if (m_tauler[fila + i][columnaI - 1] != COLOR_NEGRE || (columnaI - 1) == -1) //comprovar si la posici� a la esquerra de la pe�a est� buida o si ens trobem a la primera columna del tauler
						aux = false;
					i++;
				}
			}
		break;
	}

	return aux;
}

void Tauler::mouFigura(int dirX, Figura& f)
{
	int nCasMax = f.nombreCaselles(f.getTipus()); //m�xim de peces que ocupa la figura
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA]; //matriu de la figura
	f.getMatriuFormaAct(matriuAux);
	int fila = 0, columna = 0;
	f.calcularPosicioTauler(fila, columna);

	switch (dirX)
	{
	case 1: //cap a la dreta
		for (int j = nCasMax - 1; j >= 0; j--) //rec�rrem per columnes, comen�ant per la dreta de tot
		{
			for (int i = 0; i < nCasMax; i++)
			{
				if (matriuAux[i][j]) //si hi ha pe�a
				{
					m_tauler[fila + i][columna + j + 1] = m_tauler[fila + i][columna + j]; //movem la pe�a a la dreta
					m_tauler[fila + i][columna + j] = COLOR_NEGRE; //buidem la posici� on estaba la pe�a que hem mogut
				}
			}
		}
		break;
	case -1: //cap a l'esquerra
		for (int j = 0; j < nCasMax; j++) //rec�rrem per columnes
		{
			for (int i = 0; i < nCasMax; i++)
			{
				if (matriuAux[i][j])
				{
					m_tauler[fila + i][columna + j - 1] = m_tauler[fila + i][columna + j]; //movem la pe�a a l'esquerra
					m_tauler[fila + i][columna + j] = COLOR_NEGRE; //buidem la posici� on estaba la pe�a que hem mogut
				}
			}
		}
		break;
	}

	f.moureLateralment(dirX); //modifiquem la posici� (la fila y la columna) de la figura
}

bool Tauler::giraFigura(DireccioGir dir, Figura& f) //gira una figura en una direcci�, si es pot. Aquesta funci�, al contrari que la de 'moure' i la de 'baixa', no la divideixo en dos,
{													//ja que quan comprovo si es pot girar o no, elimino la figura, llavors aprofito y la torno a inserir aqu�, aix� tenim nom�s una funci�
	bool esPotGirar = true;							//i no repetim les accions d'eliminar i inserir (m�s eficient).
	int fila = f.getPosActFil(), columna = f.getPosActCol(), forma = f.getFormaAct();
	TipusFigura tipus = f.getTipus();

	//depenent de la forma de la figura, comprovem si es surt dels l�mits del tauler o no (la FIGURA_I la fem a part, ja que al ser 4 peces, les comprovacions son diferents de la resta):
	if ((forma == 0 && fila == (MAX_FILA - 1)) || (tipus == FIGURA_I && forma == 0 && (fila == 0 || fila >= MAX_FILA - 2)))
		esPotGirar = false;
	else
		if ((forma == 1 && columna == 0) || (tipus == FIGURA_I && forma == 1 && (columna < 2 || columna >= MAX_COL - 1)))
			esPotGirar = false;
		else
			if ((forma == 2 && fila == 0) || (tipus == FIGURA_I && forma == 2 && (fila < 2 || fila >= MAX_FILA - 1)))
				esPotGirar = false;
			else
				if ((forma == 3 && columna == (MAX_COL - 1)) || (tipus == FIGURA_I && forma == 3 && (columna == 0 || columna >= MAX_COL - 2)))
					esPotGirar = false;
				else
				{ //si no es surt pels l�mits, comprovem si, al girar, colisionaria amb altres figures:
					int nCasMax = f.nombreCaselles(tipus); //m�xim de peces que ocupa la figura
					eliminarFigura(f); //eliminem la figura del tauler, ja que al comprovar no volem que verifiqui posicions que en un futur estaran eliminades
					f.girarFigura(dir); //girem la figura
					bool matriuAux[MAX_ALCADA][MAX_AMPLADA]; //matriu de la figura
					f.getMatriuFormaAct(matriuAux);

					fila = 0, columna = 0;
					f.calcularPosicioTauler(fila, columna);
					int i = 0, j = 0;

					while (i < nCasMax && esPotGirar) //fem una cerca en la matriu
					{
						while (j < nCasMax && esPotGirar)
						{
							if (matriuAux[i][j]) //si hi ha pe�a
							{
								if (m_tauler[fila + i][columna + j] != COLOR_NEGRE) //comprova si la posici� de la pe�a al tauler est� ocupada o no
									esPotGirar = false;
							}
							j++;
						}

						j = 0;
						i++;
					}

					if (!esPotGirar) //si no es pot girar, tornem a posar la figura com estava
					{
						switch (dir)
						{
						case GIR_HORARI:
							f.girarFigura(GIR_ANTI_HORARI);
							break;
						case GIR_ANTI_HORARI:
							f.girarFigura(GIR_HORARI);
							break;
						}
					}

					inserirFigura(f); //inserim la figura, estigui girada o no
				}

	return esPotGirar;
}