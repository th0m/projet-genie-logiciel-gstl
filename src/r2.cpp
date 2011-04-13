#include "r2.hpp"
#include "shape.hpp"

R2::R2(SDL_Surface *window)
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

    /* # Pour reconnaitre la course numero 2 */
    m_map[(m_nbLines / 2) - 1][(m_nbRows / 2) - 3] = Shape::LIMIT;

    /* # Et maintenant les limites internes ! */
    for(unsigned int i = (m_nbRows / 2) - 3; i < m_nbRows - 4; ++i)
        m_map[m_nbLines / 2][i] = Shape::LIMIT;

    /* # La ligne d'arrivée/de départ */
    for(unsigned int i = m_nbLines / 2 + 1; i < m_nbLines - 1; ++i)
        m_map[i][(m_nbRows / 2) - 1] = Shape::STARTINGFINISHLINE;

    /* # Le bolide du joueur */
    m_map[m_nbLines / 2 + 1][(m_nbRows/2)] = Shape::PLAYERCAR;
    m_map[m_nbLines / 2 + 1][(m_nbRows/2) + 1] = Shape::IACAR;

    /* # Réutilisation des checkpoints de la course numéro 1 étant donne que les courses ne changent que *tres* peu */
    m_c1 = new Checkpoint(0, 180, 160, 180);
    m_c2 = new Checkpoint(350, 0, 350, 200);
    m_c3 = new Checkpoint(440, 180, 600, 180);

    m_csfl = new Checkpoint(280, 240, 280, 400);
}

R2::~R2()
{
}

void R2::load()
{
    Race::load();

    std::vector<float> pts;
    pts.push_back(90);
    pts.push_back(80);
    pts.push_back(510);
    pts.push_back(320);

    for(std::list<IACar*>::iterator it = m_iacars.begin(); it != m_iacars.end(); it++)
        (*it)->setPoints(pts);

    launchIAsTimer();
}
