#include "r3.hpp"
#include "shape.hpp"

R3::R3(SDL_Surface *window)
: Race(window)
{
    /* # On forge notre race, de façon très géométrique pour pouvoir boucler facilement */

    /* # On place les limites hautes & basses de la piste */
    for(unsigned int i = 1; i < m_nbRows - 1; ++i)
        m_map[1][i] = m_map[m_nbLines - 1][i] = Shape::LIMIT;

    /* # On place les limites gauches & droites de la piste */
    for(unsigned int i = 2; i < m_nbLines - 1; ++i)
        m_map[i][0] = m_map[i][m_nbRows - 1] = Shape::LIMIT;


    /* # Les quatres bords blanc */
    m_map[1][0] = m_map[1][m_nbRows - 1] = Shape::WHITE;
    m_map[m_nbLines - 1][0] = m_map[m_nbLines - 1][m_nbRows - 1] = Shape::WHITE;

    /* # Et maintenant les limites internes ! ; petit changement pour differencier la course 3 */
    for(unsigned int i = (m_nbRows / 2) - 3 + 1; i < m_nbRows - 10; ++i)
        m_map[m_nbLines / 2][i] = Shape::LIMIT;

    /* # La ligne d'arrivée/de départ */
    for(unsigned int i = m_nbLines / 2 + 1; i < m_nbLines - 1; ++i)
        m_map[i][(m_nbRows / 2) - 1] = Shape::STARTINGFINISHLINE;

    /* # Le bolide du joueur */
    m_map[m_nbLines / 2 + 1][(m_nbRows / 2)] = Shape::PLAYERCAR;
    m_map[m_nbLines / 2 + 1][(m_nbRows / 2) + 1] = Shape::IACAR;
    m_map[m_nbLines / 2 + 1][(m_nbRows / 2) + 2] = Shape::IACAR;
    m_map[m_nbLines / 2 + 1][(m_nbRows / 2) + 3] = Shape::IACAR;

    /* # Réutilisation des checkpoints de la course numéro 1 étant donne que les courses ne changent que *tres* peu */
    m_c1 = new Checkpoint(0, 210, 260, 210);
    m_c2 = new Checkpoint(320, 0, 320, 210);
    m_c3 = new Checkpoint(300, 210, 600, 210);

    m_csfl = new Checkpoint(320, 210, 320, 400);
}

R3::~R3()
{
}

void R3::load()
{
    Race::load();

    m_pts.push_back(80);
    m_pts.push_back(60);
    m_pts.push_back(520);
    m_pts.push_back(340);

    initIAs();
}
