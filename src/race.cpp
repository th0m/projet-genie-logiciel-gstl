#include "race.hpp"
#include "shape.hpp"
#include "checkpoint.hpp"

Race::Race(SDL_Surface *window)
: m_window(window), m_playercar(NULL), m_nbRows(Game::getNbVerticalSprites()), m_nbLines(Game::getNbHorizontalSprites()), m_map(NULL),
  m_c1(NULL), m_c2(NULL), m_c3(NULL)
{
    unsigned int i = 0;

    /* # On alloue la mémoire necessaire à stocker le niveau */
    m_map = new Uint8*[m_nbLines];

    for(unsigned int j = 0; j < m_nbLines; ++j)
        m_map[j] = new Uint8[m_nbRows];

    /* # On sait d'or et deja que la première ligne est reserve à afficher les turbos, nous avons du blanc au depart */
    for(; i < m_nbRows - 3; ++i)
        m_map[0][i] = Shape::WHITE;

    /* # Puis les turbos */
    for(; i < m_nbRows; ++i)
        m_map[0][i] = Shape::TURBO;

    /* # Et on initialise le reste de la carte avec du sable */
    for(unsigned int j = 1; j < m_nbLines; ++j)
        for(unsigned int k = 0; k < m_nbRows; ++k)
            m_map[j][k] = Shape::SAND;

    /* # Instanciation du timer des IAs */
    m_IATimer = SDL_AddTimer(10, &IACar::move, NULL);
}

Race::~Race()
{
    for(unsigned int i = 0; i < m_nbLines; ++i)
        delete[] m_map[i];
    delete [] m_map;

    for(std::list<Shape*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); ++it)
        delete (*it);

    if(m_playercar != NULL)
        delete m_playercar;
}

void Race::refresh()
{
    /* # On efface l'ecran avant de ré-afficher les shapes */
    SDL_FillRect(m_window, NULL, SDL_MapRGB(m_window->format, 0xff, 0xff, 0xff));

    /* # On parcourt l'ensemble des surfaces et nous les actualisons sauf la voiture, il faut qu'elle soit *au dessus* */
    for(std::list<Shape*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
    {
        if((*it)->isHidden() == false)
            (*it)->actualize();
    }

    /* # On affiche maintenant la voiture */
    m_playercar->actualize();

    SDL_Flip(m_window);
}

void Race::load()
{
    Shape *ptr = NULL;
    Sint32 x = 0, y = 0;
    Uint32 shapeSize = Game::getShapeSize();

    for(unsigned int i = 0; i < m_nbLines; ++i)
    {
        x = 0;
        for(unsigned int j = 0; j < m_nbRows; j++)
        {
            if(m_map[i][j] == Shape::PLAYERCAR)
            {
                /* On a un cas special ici, car on doit blitter la voiture *au dessus* du sable */
                ptr = Shape::getInstance(Shape::SAND, x, y, m_window);
                m_surfaces.push_back(ptr);

                m_playercar = static_cast<PlayerCar*>(Shape::getInstance(Shape::PLAYERCAR, x, y, m_window));
            }
            else
            {
                ptr = Shape::getInstance((Shape::shape_type)m_map[i][j], x, y, m_window);
                if(m_map[i][j] == Shape::LIMITH)
                    m_limitsH.push_back(static_cast<Limit*>(ptr));
                else
                    m_limitsV.push_back(static_cast<Limit*>(ptr));

                m_surfaces.push_back(ptr);
            }

            x += shapeSize;
        }

        y += shapeSize;
    }
}

void Race::useTurbo()
{
    /* # On parcourt l'ensemble des surfaces a la recherche du turbo a cacher */
    for(std::list<Shape*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
    {
        if((*it)->getType() == "turbo" && !(*it)->isHidden())
        {
            (*it)->hide();
            m_playercar->enableTurboMode();
            break;
        }
    }
}

void Race::movePlayerCar(SDLKey key)
{
    /* # On bouge la voiture */
    m_playercar->move(key, m_limitsH, m_limitsV);

    /* # On recharge les formes */
    refresh();
}
