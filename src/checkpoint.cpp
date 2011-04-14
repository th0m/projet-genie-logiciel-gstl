#include "checkpoint.hpp"
#include "game.hpp"
#include <stdio.h>

Checkpoint::Checkpoint(int x1, int y1, int x2, int y2)
: m_pixelParSeconde(Game::getFwdSpeed() * 4)
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

    /* # le checkpoint est horizontal */
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y > y && y > m_pointBegin.y - m_pixelParSeconde)
        m_isValidated = true;
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y < y && y < m_pointBegin.y + m_pixelParSeconde)
        m_isValidated = false;
}

void Checkpoint::checkC2(int lex, int ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    int x = lex + 20, y = ley + 20;

    /* # le checkpoint est vertical */
    /* # pour savoir quel point est le plus haut */
    if(m_pointBegin.x < x && x < m_pointBegin.x + m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = true;
    if(m_pointBegin.x > x && x > m_pointBegin.x - m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = false;
}

void Checkpoint::checkC3(int lex, int ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    int x = lex + 20, y = ley + 20;

    /* # le checkpoint est horizontal */
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y > y && y > m_pointBegin.y - m_pixelParSeconde)
        m_isValidated = false;
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y < y && y < m_pointBegin.y + m_pixelParSeconde)
        m_isValidated = true;
}

void Checkpoint::checkCF(int lex, int ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    int x = lex + 20, y = ley + 20;

    /* # le checpoint est vertical */
    /* # pour savoir quel point est le plus haut */
    if(m_pointBegin.x > x && x > m_pointBegin.x - m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = true;
    if(m_pointBegin.x < x && x < m_pointBegin.x + m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = false;
}
