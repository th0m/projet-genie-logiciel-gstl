/**
 * \file sort.hpp
 * \brief Classe Sort.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Foncteur qui va réaliser le trie du conteneur de score.
 *
 */

#ifndef SORT_HPP
#define SORT_HPP

#include <utility>
#include <string>

class Sort
{
    public:

        /**
         * \fn bool operator()(std::pair<unsigned int, std::string> const &a, std::pair<unsigned int, std::string> const &b) const
         * \brief Operateur() qui va permettre de trier deux pairs de scores/joueurs.
         *
         * \return Un booléen qui nous renseigne si l'objet a est plus petit que le b.
         */
        bool operator()(std::pair<unsigned int, std::string> const &a, std::pair<unsigned int, std::string> const &b) const;
};

#endif
