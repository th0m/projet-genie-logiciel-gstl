/**
 * \file shape.hpp
 * \brief Gestion des shapes : "pixels" permettant l'affichage de la carte.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 */

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <SDL/SDL.h>
#include <string>

/**
 * \class Shape
 * \brief Classe qui va permettre de gérer l'affichage graphique via des formes différentes.
*/
class Shape
{
    public:

        /**
         * \enum shape_type
         * \brief Indique le type de la forme.
         *
         */
        enum shape_type
        {
            SAND, /*!< Sable */
            WHITE, /*!< Blanc */
            TURBO, /*!< Turbo */
            LIMIT, /*!< Limite */
            STARTINGFINISHLINE, /*!< Ligne de depart / arrivee */
            PLAYERCAR, /*!< Voiture du joueur */
            FLAQUE, /*!< Flaque */
            IACAR /*!< Voiture de l'IA */
        };

        /**
         * \fn explicit Shape(float x, float y, std::string type, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y, de son type et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonnée x du placement de la forme.
         * \param y Coordonnée y du placement de la forme.
         * \param type Type de la forme.
         * \param window Pointeur sur la fenetre principale.
         */
        explicit Shape(float x, float y, std::string type, SDL_Surface *window);

        /**
         * \fn ~Shape()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouees.
         */
        ~Shape();

        /**
         * \fn bool isHidden() const
         * \brief Fonction qui nous renvoit l'etal visuel de la forme.
         *
         * \return Booleen immuable qui indique si la forme est cachee ou non
         */
        bool isHidden() const;

        /**
         * \fn void hide()
         * \brief Fonction qui permet de cacher une forme.
         */
        void hide();

        /**
         * \fn void actualize()
         * \brief Fonction qui repositionne la forme selon ses coordonnées.
         */
        void actualize();

        /**
         * \fn float getX() const
         * \brief Fonction qui retourne la coordonnee en x de la forme.
         *
         * \return Abscisse immuable de la forme.
         */
        float getX() const;

        /**
         * \fn float getY() const
         * \brief Fonction qui retourne la coordonnee en y de la forme.
         *
         * \return Ordonnee immuable de la forme.
         */
        float getY() const;

        /**
         * \fn std::string getType() const
         * \brief Fonction qui retourne le type de la shape sous la forme d'une chaine.
         *
         * \return Chaine immuable representant le type de la forme.
         */
        std::string getType() const;

        /**
         * \fn static Shape* getInstance(Shape::shape_type type, float x, float y, SDL_Surface *window)
         * \brief Factory design pattern - fonction d'instanciation.
         *
         * \param type Type de la forme
         * \param x Coordonnée en abscisse de la forme.
         * \param y Coordonnée en ordonnée de la forme.
         * \param window Pointeur sur la fenetre principale.
         *
         * \return Pointeur sur l'instance de la forme generee.
         */
        static Shape* getInstance(Shape::shape_type type, float x, float y, SDL_Surface *window);

    protected:

        std::string m_type; /*!< Le type de sprite */

        bool m_isHidden; /*!< Le sprite est-il visible ? */

        float m_x; /*!< Coordonnée en abscisse de la forme */

        float m_y; /*!< Coordonnée en ordonnée de la forme */

        SDL_Surface *m_img; /*!< Le sprite */

        SDL_Surface *m_window; /*!< La fenêtre */

        bool m_free; /*!< Booleen qui permet de savoir si la classe mère doit détruire elle même l'image.*/
};

#endif
