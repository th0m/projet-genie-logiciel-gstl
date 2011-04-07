#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <string>

/* # Pour eviter le probleme des inclusions cycliques : classe A a besoin de la classe B, et la classe B a besoin de la classe A */
class R1;
class R2;
class R3;
class Race;

class Game
{
    public:

        explicit Game();

        ~Game();

        /* # Fonction qui démarre le jeu */
        void start();

        /* # Fonction qui permet de récuperer le nombre de sprite à disposer sur l'horizontale */
        static Uint32 getNbHorizontalSprites();

        /* # Fonction qui permet de récuperer le nombre de sprite à disposer sur la verticale */
        static Uint32 getNbVerticalSprites();

        /* # Fonction qui permet de récuperer la taille d'un sprite */
        static Uint32 getShapeSize();

        static Uint32 getTurboTime();

        static float getFwdSpeed();

        static float getRevSpeed();

    private:

        typedef enum RaceNumber
        {
            Race1,
            Race2,
            Race3
        };

        /* # La boucle principale d'evenement */
        void eventloop();

        void cleanScreen();

        /* # La course courante */
        Race *m_currentRace;

        /* # Sommes-nous toujours dans la boucle d'evenement ? */
        bool m_isOk;

        /* # Pointeur sur notre fenetre de jeu */
        SDL_Surface *m_window, *m_ico;

        /* # La largeur et la hauteur de notre fenetre */
        static const Uint32 m_width, m_height, m_shapeSize, m_turboTime, m_nbLap;

        /* # Vitesses marche avant et marche arriere */
        static const float m_fwdSpeed, m_revSpeed;

        /* # Le titre de la fenetre */
        static const std::string m_title;

        RaceNumber m_rNumber;
};

#endif
