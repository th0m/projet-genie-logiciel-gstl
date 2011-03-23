#include "race.hpp"

#include "sand.hpp"
#include "white.hpp"
#include "turbo.hpp"
#include "startingfinishline.hpp"

Race::Race(SDL_Surface *window)
: m_window(window), m_nbRows(Game::getNbVerticalSprites()), m_nbLines(Game::getNbHorizontalSprites())
{
    int i = 0;

    /* # On alloue la mémoire necessaire à stocker le niveau */
    m_map = new Uint8*[m_nbLines];

    for(int i = 0; i < m_nbLines; ++i)
        m_map[i] = new Uint8[m_nbRows];

    /* # On sait d'or et deja que la première ligne est reserve à afficher les turbos, nous avons du blanc au depart */
    for(; i < m_nbRows - 3; ++i)
        m_map[0][i] = Shape::White;

    /* # Puis les turbos */
    for(; i < m_nbRows; ++i)
        m_map[0][i] = Shape::Turbo;

    /* # Et on initialise le reste de la carte avec du sable */
    for(int j = 1; j < m_nbLines; ++j)
        for(int k = 0; k < m_nbRows; ++k)
            m_map[j][k] = Shape::Sand;
}

Race::~Race()
{
    for(int i = 0; i < m_nbLines; ++i)
        delete[] m_map[i];
    delete [] m_map;
}

void Race::refresh()
{
    Shape *ptr = NULL;

    /* # On parcourt l'ensemble des surfaces et nous les actualisons */
    for(std::list<Shape*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
        (*it)->actualize();
}

PlayerCar* Race::getPlayerCar()
{
    return m_playercar;
}

void Race::load()
{
    Shape *ptr = NULL;
    Uint32 x = 0, y = 0, shapeSize = Game::getShapeSize();

    for(int i = 0; i < m_nbLines; ++i)
    {
        x = 0;
        for(int j = 0; j < m_nbRows; j++)
        {
            switch(m_map[i][j])
            {
                case Shape::Sand :
                {
                    ptr = new Sand(x, y, m_window);
                    break;
                }

                case Shape::White :
                {
                    ptr = new White(x, y, m_window);
                    break;
                }

                case Shape::Turbo :
                {
                    ptr = new Turbo(x, y, m_window);
                    break;
                }

                case Shape::StartingFinishLine :
                {
                    ptr = new StartingFinishLine(x, y, m_window);
                    break;
                }

                case Shape::PlayerCar :
                {
                    ptr = m_playercar = new PlayerCar(x, y, m_window);
                    break;
                }
            }

            m_surfaces.push_back(ptr);
            x += shapeSize;
        }

        y += shapeSize;
    }
}
