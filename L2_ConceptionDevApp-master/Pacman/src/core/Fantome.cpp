#include "Fantome.h"
#include <stdlib.h>

Fantome::Fantome() : m_x(1), m_y(1), m_dir(0)
{
}

void Fantome::versPacman(const Terrain &t, const Pacman &p)
{
    int dx = p.getX() - m_x;
    int dy = p.getY() - m_y;
    if (dx > 0)
        dx = 1;
    if (dx < 0)
        dx = -1;
    if (dy > 0)
        dy = 1;
    if (dy < 0)
        dy = -1;
    if (t.estPositionPersoValide(m_x + dx, m_y + dy))
    {
        m_x = m_x + dx;
        m_y = m_y + dy;
    }
}

void Fantome::bougeAuto(const Terrain &t)
{
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int xtmp, ytmp;
    xtmp = m_x + dx[m_dir];
    ytmp = m_y + dy[m_dir];
    if (t.estPositionPersoValide(xtmp, ytmp))
    {
        m_x = xtmp;
        m_y = ytmp;
    }
    else
        m_dir = rand() % 4;
}
