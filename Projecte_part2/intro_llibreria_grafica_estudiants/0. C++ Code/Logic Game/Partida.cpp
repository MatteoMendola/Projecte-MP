#include "./Partida.h"
#include "./InfoJoc.h"
#include "./GraphicManager.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

Partida::Partida()
{
    m_temps = 0;
}

void Partida::inicialitza(int mode, const string& nomFitxer, const string& nomFitxer2, const string& nomFitxer3)
{
    m_temps = 0;
    m_joc.inicialitza(mode, nomFitxer);

	if (mode == 2)
	{
		ifstream fitxer1, fitxer2;
		fitxer1.open(nomFitxer2);
		fitxer2.open(nomFitxer3);

		if (fitxer1.is_open() && fitxer2.is_open())
		{
			int mov;

			for (int i = 0; i < 11; i++)
			{
				fitxer2 >> mov;
				m_moviments[i] = mov;
			}

			int tipus, fila, columna, nGirs;

			for (int i = 0; i < 7; i++)
			{
				fitxer1 >> tipus >> fila >> columna >> nGirs;
				m_figures[i][0] = tipus;
				m_figures[i][1] = fila;
				m_figures[i][2] = columna;
				m_figures[i][3] = nGirs;
			}

			fitxer1.close();
			fitxer2.close();
		}
	}
	else //mode normal
	{
		std::srand(std::time(0));
		int randomNumber = std::rand() % 7 + 1;
		m_joc.apareixerFigura(randomNumber, 1, 5, 0);
	}
}

bool Partida::actualitza(int mode, double deltaTime)
{
	bool final = false;

	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

	m_joc.dibuixa();

	string msg = "Puntuacio: 0		Nivell: 1";
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);	//no funciona

	m_temps += deltaTime;
	if (m_temps > 1.0)
	{
		if (mode == 2)
		{
			int i = 0;
			bool trobat = false;

			while (i < 11 && !trobat)
			{
				if (m_moviments[i] != -1)
					trobat = true;
				else
					i++;
			}

			if (trobat)
			{
				bool potBaixar = true;
				switch (m_moviments[i])
				{
				case TECLA_ESQUERRA: m_joc.mouFigura(-1);
					break;
				case TECLA_DRETA: m_joc.mouFigura(1);
					break;
				case TECLA_AMUNT: m_joc.giraFigura(GIR_HORARI);
					break;
				case TECLA_ABAIX: m_joc.giraFigura(GIR_ANTI_HORARI);
					break;
				case TECLA_ESPAI: 
					m_joc.baixaFigura(potBaixar);
					if (!potBaixar)
					{
						int aux = 0;
						while (m_figures[aux][0] == -1)
							aux++;
						final = m_joc.apareixerFigura(m_figures[aux][0], m_figures[aux][1], m_figures[aux][2], m_figures[aux][3]);
						m_figures[aux][0] = -1;
					}
					break;
				case TECLA_ESCAPE:
					m_joc.baixarFinal();
					int aux = 0;
					while (m_figures[aux][0] == -1)
						aux++;
					final = m_joc.apareixerFigura(m_figures[aux][0], m_figures[aux][1], m_figures[aux][2], m_figures[aux][3]);
					m_figures[aux][0] = -1;
					break;
				}

				m_moviments[i] = -1;
			}
			else
				final = true; //final partida
		}
		else //mode normal
		{
			bool esPotBaixar = true;

			m_joc.baixaFigura(esPotBaixar);

			if (!esPotBaixar)
			{
				int randomNumber = std::rand() % 7 + 1;
				final = m_joc.apareixerFigura(randomNumber, 1, 5, 0);
			}
		}
		
		m_temps = 0.0;
	}    

	if (mode == 1)
	{
		int key = -1;
		if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
			key = KEYBOARD_RIGHT;
		else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
			key = KEYBOARD_LEFT;
		else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
			key = KEYBOARD_DOWN;
		else if (Keyboard_GetKeyTrg(KEYBOARD_UP))
			key = KEYBOARD_UP;
		else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
			key = KEYBOARD_SPACE;

		switch (key)
		{
		case KEYBOARD_RIGHT:
			m_joc.mouFigura(1);
			break;
		case KEYBOARD_LEFT:
			m_joc.mouFigura(-1);
			break;
		case KEYBOARD_DOWN:
			m_joc.giraFigura(GIR_ANTI_HORARI);
			break;
		case KEYBOARD_UP:
			m_joc.giraFigura(GIR_HORARI);
			break;
		case KEYBOARD_SPACE:
			m_joc.baixarFinal();
			break;
		default:
			break;
		}
	}

	return final;
} 