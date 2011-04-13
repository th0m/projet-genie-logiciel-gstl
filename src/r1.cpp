#include "r1.hpp"
#include "shape.hpp"

R1::R1(SDL_Surface *window)
: Race(window)
{
    /* # On forge notre race1, de fa�on tr�s g�om�trique pour pouvoir boucler facilement */

    /* # On place les limites hautes & basses de la piste */
    for(unsigned int i = 1; i < m_nbRows - 1; ++i)
        m_map[1][i] = m_map[m_nbLines - 1][i] = Shape::LIMIT;

    /* # On place les limites gauches & droites de la piste */
    for(unsigned int i = 2; i < m_nbLines - 1; ++i)
        m_map[i][0] = m_map[i][m_nbRows - 1] = Shape::LIMIT;


    /* # Les quatres bords blanc */
    m_map[1][0] = m_map[1][m_nbRows - 1] = Shape::WHITE;
    m_map[m_nbLines - 1][0] = m_map[m_nbLines - 1][m_nbRows - 1] = Shape::WHITE;

    /* # Et maintenant les limites internes ! */
    for(unsigned int i = (m_nbRows / 2) - 3; i < m_nbRows - 4; ++i)
        m_map[m_nbLines / 2][i] = Shape::LIMIT;

    /* # La ligne d'arriv�e/de d�part */
    for(unsigned int i = m_nbLines / 2 + 1; i < m_nbLines - 1; ++i)
        m_map[i][(m_nbRows / 2) - 1] = Shape::STARTINGFINISHLINE;

    /* # Deux flaques */
    m_map[m_nbLines / 2 + 2][(m_nbRows/2)-3] = Shape::FLAQUE;
    m_map[m_nbLines / 2 + 2][(m_nbRows/2)-4] = Shape::FLAQUE;

    /* # Le bolide du joueur */
    m_map[m_nbLines / 2 + 1][(m_nbRows/2)] = Shape::PLAYERCAR;
    m_map[m_nbLines / 2 + 1][(m_nbRows/2 +1)] = Shape::IACAR;

    /* # attention ;
        m_c1 : premier checkpoint recontr�
        m_c2 : second checkpoint recontr�
        m_c3 : troisieme checkpoint recontr�
        l'ordre sert par la suite pour la validation du tour
    */
    m_c1 = new Checkpoint(0, 180, 160, 180);
    m_c2 = new Checkpoint(350, 0, 350, 200);
    m_c3 = new Checkpoint(440, 180, 600, 180);

    m_csfl = new Checkpoint(280, 240, 280, 400);
}

R1::~R1()
{
}

void R1::load()
{
    Race::load();

    std::vector<float> pts;
    pts.push_back(80);
    pts.push_back(80);
    pts.push_back(520);
    pts.push_back(320);

    for(std::list<IACar*>::iterator it = m_iacars.begin(); it != m_iacars.end(); it++)
        (*it)->setPoints(pts);
}
