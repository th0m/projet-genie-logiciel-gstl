#include "checkpoint.hpp"
#include "game.hpp"
#include <stdio.h>

Checkpoint::Checkpoint(int x1, int y1, int x2, int y2)
{
    m_pointBegin.x = x1;
    m_pointBegin.y = y1;
    m_pointEnd.x = x2;
    m_pointEnd.y = y2;
    m_isValidated = false;
}


bool Checkpoint::isValidated() const
{
    return m_isValidated;
}

void Checkpoint::reset()
{
    m_isValidated = false;
}


void Checkpoint::checkC1(int lex, int ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    int x = lex + 20, y = ley + 20;
    int pixelParSeconde = Game::getFwdSpeed() * 2;
    /* # le checpoint est horizontal */


    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y > y && y > m_pointBegin.y - pixelParSeconde)
        m_isValidated = true;
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y < y && y < m_pointBegin.y + pixelParSeconde)
        m_isValidated = false;

    printf("Verif checkpoint C1 : %d\n",m_isValidated );
    fflush(stdout);

}

void Checkpoint::checkC2(int lex, int ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    int x = lex + 20, y = ley + 20;
    int pixelParSeconde = Game::getFwdSpeed() * 2;
    /* # le checpoint est vertical */
    /* # pour savoir quel point est le plus haut */
    if(m_pointBegin.x < x && x < m_pointBegin.x + pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = true;
    if(m_pointBegin.x > x && x > m_pointBegin.x - pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = false;

    printf("Verif checkpoint C2 : %d\n",m_isValidated );
    fflush(stdout);
}



void Checkpoint::checkC3(int lex, int ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    int x = lex + 20, y = ley + 20;
    int pixelParSeconde = Game::getFwdSpeed() * 2;
    /* # le checpoint est horizontal */


    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y > y && y > m_pointBegin.y - pixelParSeconde)
        m_isValidated = false;
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y < y && y < m_pointBegin.y + pixelParSeconde)
        m_isValidated = true;

    printf("Verif checkpoint C3 : %d\n",m_isValidated );
    fflush(stdout);
}



void Checkpoint::checkCF(int lex, int ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    int x = lex + 20, y = ley + 20;
    int pixelParSeconde = Game::getFwdSpeed() * 2;
    /* # le checpoint est vertical */
    /* # pour savoir quel point est le plus haut */
    if(m_pointBegin.x > x && x > m_pointBegin.x - pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = true;
    if(m_pointBegin.x < x && x < m_pointBegin.x + pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = false;

    printf("Verif checkpoint CF : %d\n",m_isValidated );
    fflush(stdout);

}
