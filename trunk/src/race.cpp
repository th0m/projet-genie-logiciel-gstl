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

    /* # On sait d'ores et deja que la première ligne est reserve à afficher les turbos, nous avons du blanc au depart */
    for(; i < m_nbRows - 3; ++i)
        m_map[0][i] = Shape::WHITE;

    /* # Puis les turbos */
    for(; i < m_nbRows; ++i)
        m_map[0][i] = Shape::TURBO;

    /* # Et on initialise le reste de la carte avec du sable */
    for(unsigned int j = 1; j < m_nbLines; ++j)
        for(unsigned int k = 0; k < m_nbRows; ++k)
            m_map[j][k] = Shape::SAND;
}

Race::~Race()
{
    /* # On desalloue proprement chaque colonnes de notre map */
    for(unsigned int i = 0; i < m_nbLines; ++i)
        delete[] m_map[i];

    /* # On desalloue les lignes */
    delete [] m_map;

    /* # On supprime proprement chaque surface utilisé par la map */
    for(std::list<Shape*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); ++it)
        delete (*it);

    /* # On oublie pas de supprimer la voiture du joueur */
    if(m_playercar != NULL)
        delete m_playercar;

    /* # On detruit nos IAs */
    for(std::list<IACar*>::iterator it = m_iacars.begin(); it != m_iacars.end(); ++it)
        delete (*it);

    /* # On detruit nos checkpoints */
    delete m_c1;
    delete m_c2;
    delete m_c3;
    delete m_csfl;
}

void Race::actualize()
{
    /* # On efface l'ecran avant de ré-afficher les shapes */
    SDL_FillRect(m_window, NULL, SDL_MapRGB(m_window->format, 0xff, 0xff, 0xff));

    /* # On parcourt l'ensemble des surfaces et nous les actualisons sauf la voiture, il faut qu'elle soit *au dessus* */
    for(std::list<Shape*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
    {
        if((*it)->isHidden() == false)
            (*it)->actualize();
    }

    /* # On affiche maintenant les voitures */
    m_playercar->actualize();

    for(std::list<IACar*>::iterator it = m_iacars.begin(); it != m_iacars.end(); it++)
        (*it)->actualize();

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
            else if(m_map[i][j] == Shape::IACAR)
            {
                /* On a un cas special ici, car on doit blitter la voiture *au dessus* du sable */
                ptr = Shape::getInstance(Shape::SAND, x, y, m_window);
                m_surfaces.push_back(ptr);

                ptr = Shape::getInstance(Shape::IACAR, x, y, m_window);
                m_iacars.push_back(static_cast<IACar*>(ptr));
                m_ranking.insert(std::pair<IACar*, std::pair<int, int> >(static_cast<IACar*>(ptr), std::pair<int, int>(-1, 0)));
            }
            else
            {
                ptr = Shape::getInstance((Shape::shape_type)m_map[i][j], x, y, m_window);

                if(m_map[i][j] == Shape::LIMIT)
                    m_limits.push_back(static_cast<Limit*>(ptr));
                else if(m_map[i][j] == Shape::FLAQUE)
                    m_flaques.push_back(static_cast<Flaque*>(ptr));
                else;

                m_surfaces.push_back(ptr);
            }

            x += shapeSize;
        }

        y += shapeSize;
    }
}

bool Race::useTurbo()
{
    bool isOk = false;

    /* # On parcourt l'ensemble des surfaces a la recherche du turbo a cacher */
    for(std::list<Shape*>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
    {
        if((*it)->getType() == "turbo" && !(*it)->isHidden())
        {
            (*it)->hide();
            m_playercar->setTurboMode();
            isOk = true;
            break;
        }
    }

    return isOk;
}

void Race::movePlayerCar(SDLKey key)
{
    /* # On bouge la voiture */
    m_playercar->move(key, m_limits, m_flaques, m_iacars);
}

void Race::moveIAs()
{
    for(std::list<IACar*>::const_iterator it = m_iacars.begin(); it != m_iacars.end(); it++)
        (*it)->move(m_playercar->getX(), m_playercar->getY(), m_iacars);

    checkCheckPointIA();
}

void Race::initIAs()
{
    Uint8 i = 3, j = 0;
    Sint8 mutate = 0;
    std::vector<float> copy(m_pts);

    for(std::list<IACar*>::iterator it = m_iacars.begin(); it != m_iacars.end(); it++, j = 0)
    {
        /* # On definit les trajectoires pour toutes les IAs */
        (*it)->setPoints(copy);

        /* # On fixe une difficulte croissante entres les IAs */
        (*it)->setDifficulty(i--);

        /* # On fait evoluer les points pour chaque IAs */
        for(std::vector<float>::iterator it2 = copy.begin(); it2 != copy.end(); it2++)
        {
            /* # On fait muter les coordonnes de façon differente s'il s'agit d'une coordonne x, y */
            switch(j++)
            {
                case 1:
                case 0:
                {
                    mutate = Game::getShapeSize();
                    break;
                }

                case 2:
                case 3:
                {
                    mutate = -Game::getShapeSize();
                    break;
                }

                default:
                break;
            }

            (*it2) += mutate * 3;
        }
    }
}

PlayerCar* Race::getPlayerCar()
{
    return m_playercar;
}

Race::Lap Race::checkCheckPoint()
{
    Lap lap = InProgress;

    float x = m_playercar->getX();
    float y = m_playercar->getY();

    /* # vérification de chaque Checkpoint */
    m_c1->checkC1(x, y);
    m_c2->checkC2(x, y);
    m_c3->checkC3(x, y);
    m_csfl->checkCF(x, y);


    /* # validation d'un tour */
    if(m_c1->isValidated() && m_c2->isValidated() && m_c3->isValidated() && m_csfl->isValidated())
    {
        lap = Finished;
        m_c1->reset();
        m_c2->reset();
        m_c3->reset();
    }

    m_csfl->reset();
    return lap;
}

void Race::checkCheckPointIA()
{
    int i = 0;

    for(std::map<IACar*, std::pair<int, int> >::iterator it = m_ranking.begin(); it != m_ranking.end(); it++)
    {
        i = m_csfl->checkCFIA(it->first->getX(), it->first->getY());

        if(i == Checkpoint::AfterFinishLine && it->second.second != 1)
        {
            it->second.first++;
            it->second.second = 1;
        }

        if(i == Checkpoint::BeforeFinishLine)
            it->second.second = 0;
    }
}

void Race::initNbLapCompetitors()
{
    for(std::map<IACar*, std::pair<int, int> >::iterator it = m_ranking.begin(); it != m_ranking.end(); it++)
    {
        it->second.first = -1;
        it->second.second = 0;
    }
}

int Race::checkSuccessRace()
{
    int nbCompetitors = 0;

    for (std::map<IACar*, std::pair<int,int> >::iterator it = m_ranking.begin(); it != m_ranking.end(); it++)
        if(it->second.first >= 2)
            nbCompetitors++;

    return nbCompetitors + 1;
}
