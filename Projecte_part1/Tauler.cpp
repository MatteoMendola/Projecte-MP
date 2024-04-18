#include "Tauler.h"

void Tauler::giraFigura(Figura& f, DireccioGir dir)
{
	if (f.getTipus() != NO_FIGURA && f.getTipus() != FIGURA_O)	//el quadrat quan es gira es queda igual
	{
		int nCasMax = f.nombreCaselles(f.getTipus());

		if (nCasMax == 3)
		{
			for (int i = 0; i < nCasMax; i++)	//transposar
			{
				for (int j = 0; j < nCasMax; j++)
				{

				}
			}
		}
		else //nCasMax == 4 (no hi ha més casos)
		{
			for (int i = 0; i < nCasMax; i++)	//transposar
			{
				for (int j = 0; j < nCasMax; j++)
				{

				}
			}
		}
		
		switch (dir)
		{
		case GIR_HORARI:
			//invertir columnes
			break;
		case GIR_ANTI_HORARI:
			//invertir files
			break;
		}

		f.girarFigura(dir);
	}
}