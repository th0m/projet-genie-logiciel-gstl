#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <string>

/* # Pour eviter le probleme des inclusions cycliques : classe A a besoin de la classe B, et la classe B a besoin de la classe A */
class R1;

class Game
{
    public:
        explicit Game();
        ~Game();

        void start();

        static Uint32 getNbHorizontalSprites();
        static Uint32 getNbVerticalSprites();
        static Uint32 getShapeSize();

    private:

        /* # La boucle principale d'evenement */
        void eventloop();

        /* # La premiere course */
        R1 *m_r1;

        /* # Sommes-nous toujours dans la boucle d'evenement ? */
        bool m_isOk;

        /* # Pointeur sur notre fenetre de jeu */
        SDL_Surface *m_window, *m_ico;

        /* # La largeur et la hauteur de notre fenetre */
        static const Uint32 m_width, m_height, m_shapeSize;

        /* # Le titre de la fenetre */
        static const std::string m_title;
};

#endif
