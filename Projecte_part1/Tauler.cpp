#include "Tauler.h"

void Tauler::inserirFigura(const Figura& f)
{
	int nCasMax = f.nombreCaselles(f.getTipus());
	bool matriuAux[MAX_ALCADA][MAX_AMPLADA];
	f.getMatriuFormaAct(matriuAux);
	int fila = f.getPosActFil();
	int columna = f.getPosActCol();
	ColorFigura color = f.getColor();

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

	for (int i = 0; i < nCasMax; i++)
	{
		for (int j = 0; j < nCasMax; j++)
		{
			if (matriuAux[i][j])
				m_tauler[fila + i][columna + j] = color;
		}
	}
}