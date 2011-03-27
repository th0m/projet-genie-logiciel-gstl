#include "r1.hpp"
#include "shape.hpp"

R1::R1(SDL_Surface *window)
: Race(window)
{
    /* # On forge notre race1, de fa�on tr�s g�om�trique pour pouvoir boucler facilement */

    /* # On place les limites hautes & basses de la piste */
    for(int i = 1; i < m_nbRows - 1; ++i)
        m_map[1][i] = m_map[m_nbLines - 1][i] = Shape::Limits;

    /* # On place les limites gauches & droites de la piste */
    for(int i = 2; i < m_nbLines - 1; ++i)
        m_map[i][0] = m_map[i][m_nbRows - 1] = Shape::Limits;


    /* # Les quatres bords blanc */
    m_map[1][0] = m_map[1][m_nbRows - 1] = Shape::White;
    m_map[m_nbLines - 1][0] = m_map[m_nbLines - 1][m_nbRows - 1] = Shape::White;

    /* # Et maintenant les limites internes ! */
    for(int i = (m_nbRows / 2) - 3; i < m_nbRows - 4; ++i)
        m_map[m_nbLines / 2][i] = Shape::Limits;

    /* # La ligne d'arriv�e/de d�part */
    for(int i = m_nbLines / 2 + 1; i < m_nbLines - 1; ++i)
        m_map[i][(m_nbRows / 2) - 1] = Shape::StartingFinishLine;

    /* # Le bolide du joueur */
    m_map[m_nbLines / 2 + 1][(m_nbRows/2)] = Shape::PlayerCar;
}
