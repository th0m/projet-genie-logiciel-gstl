#include "checkpoint.hpp"
#include "game.hpp"
#include <stdio.h>
#include "iacar.hpp"
#include <list>
#include "shape.hpp"

Checkpoint::Checkpoint(float x1, float y1, float x2, float y2)
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

void Checkpoint::checkC1(float lex, float ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    float x = lex + 20, y = ley + 20;

    /* # le checkpoint est horizontal */
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y > y && y > m_pointBegin.y - m_pixelParSeconde)
        m_isValidated = true;
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y < y && y < m_pointBegin.y + m_pixelParSeconde)
        m_isValidated = false;
}

void Checkpoint::checkC2(float lex, float ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    float x = lex + 20, y = ley + 20;

    /* # le checkpoint est vertical */
    if(m_pointBegin.x < x && x < m_pointBegin.x + m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = true;
    if(m_pointBegin.x > x && x > m_pointBegin.x - m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = false;
}

void Checkpoint::checkC3(float lex, float ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    float x = lex + 20, y = ley + 20;

    /* # le checkpoint est horizontal */
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y > y && y > m_pointBegin.y - m_pixelParSeconde)
        m_isValidated = false;
    if(m_pointBegin.x < x && x < m_pointEnd.x && m_pointBegin.y < y && y < m_pointBegin.y + m_pixelParSeconde)
        m_isValidated = true;
}

void Checkpoint::checkCF(float lex, float ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    float x = lex + 20, y = ley + 20;

    /* # le checpoint est vertical */
    if(m_pointBegin.x > x && x > m_pointBegin.x - m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = true;
    if(m_pointBegin.x < x && x < m_pointBegin.x + m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        m_isValidated = false;
}


int Checkpoint::checkCFIA(float x, float y)
{
    /* # on prend les coordonnées du centre de la voiture */
    x += 20;
    y += 20;

    /* # l'advresaire a passer le checkpoint */
    if(m_pointBegin.x > x && x > m_pointBegin.x - m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        return 2;
    /* # l'advresaire est avant le checkpoint */
    if(m_pointBegin.x < x && x < m_pointBegin.x + m_pixelParSeconde && m_pointBegin.y < y && y < m_pointEnd.y)
        return 1;
    /* # l'advresaire est ailleurs sur le circuit */
    else
        return 0;
}

