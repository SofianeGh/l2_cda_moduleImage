#include "Pacman.h"

Pacman::Pacman()
{
	m_x = m_y = 1;
}

void Pacman::gauche(const Terrain &t)
{
	if (t.estPositionPersoValide(m_x - 1, m_y))
		m_x--;
}

void Pacman::droite(const Terrain &t)
{
	if (t.estPositionPersoValide(m_x + 1, m_y))
		m_x++;
}

void Pacman::haut(const Terrain &t)
{
	if (t.estPositionPersoValide(m_x, m_y + 1))
		m_y++;
}

void Pacman::bas(const Terrain &t)
{
	if (t.estPositionPersoValide(m_x, m_y - 1))
		m_y--;
}
