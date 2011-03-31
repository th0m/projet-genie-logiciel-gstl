#include "checkpoint.hpp"
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

void Checkpoint::check(int lex, int ley)
{
    /* # on prend les coordonnées du centre de la voiture */
    int x = lex + 20, y = ley + 20;
    /* # si le checpoint est vertical */
    if(m_pointBegin.x == m_pointEnd.x)
    {
        /* # pour savoir quel point est le plus haut */
        if(m_pointBegin.y < m_pointEnd.y){
            if(m_pointBegin.x == x && m_pointBegin.y <= y && y <= m_pointEnd.y)
                m_isValidated = !m_isValidated;
        }
        else{
            if(m_pointBegin.x == x && m_pointEnd.y <= y && y <= m_pointBegin.y)
                m_isValidated = !m_isValidated;
        }
    }
    /* # si le checpoint est horizontal */
    if(m_pointBegin.y == m_pointEnd.y)
    {
        /* # pour savoir quel point est le plus a gauche */
        if(m_pointBegin.x < m_pointEnd.x){
            if(m_pointBegin.y == y && m_pointBegin.x <= x && x <= m_pointEnd.x)
                m_isValidated = !m_isValidated;
        }
        else{
            if(m_pointBegin.y == y && m_pointEnd.x <= x && x <= m_pointBegin.x)
                m_isValidated = !m_isValidated;
        }
    }
    printf("Verif checkpoint : %d\n",m_isValidated );
}
