#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <string>

/* # Pour eviter le probleme des inclusions cycliques : classe A a besoin de la classe B, et la classe B a besoin de la classe A */
class Race;

class Game
{
    public:

        explicit Game();

        ~Game();

        /* # Fonction qui d�marre le jeu */
        void start();

        /* # Fonction qui permet de r�cuperer le nombre de sprite � disposer sur l'horizontale */
        static Uint32 getNbHorizontalSprites();

        /* # Fonction qui permet de r�cuperer le nombre de sprite � disposer sur la verticale */
        static Uint32 getNbVerticalSprites();

        /* # Fonction qui permet de r�cuperer la taille d'un sprite */
        static Uint32 getShapeSize();

        static Uint32 getTurboTime();

        static float getFwdSpeed();

        static float getRevSpeed();

        static Uint32 getSpeedFactorIA();

        static float getDifficultyIAPercentage();

    private:

        enum RaceNumber
        {
            Race1,
            Race2,
            Race3
        };

        struct Input
        {
            char key[SDLK_LAST];
        };

        /* # La boucle principale d'evenement */
        void eventloop();

        /* # Fonction qui permet de nettoyer l'�cran principal */
        void cleanScreen();

        /* # La fonction qui gere les evenements */
        void UpdateEvents(Input* in, bool& continuer);

        /* # Fonction qui va g�rer l'ajout des scores */
        void handleScore();

        /* # Fonction qui donne le temps a sleep avant le prochaine rafraichissement */
        Uint32 time_left(Uint32 &next_time);

        /* # La course courante */
        Race *m_currentRace;

        /* # Sommes-nous toujours dans la boucle d'evenement ? */
        bool m_isOk;

        /* # Pointeur sur notre fenetre de jeu */
        SDL_Surface *m_window, *m_ico;

        /* # La largeur et la hauteur de notre fenetre */
        static const Uint32 m_width, m_height;

        /* # La taille en pixel d'une shape */
        static const Uint32 m_shapeSize;

        /* # La dur�e en milliseconde d'un turbo */
        static const Uint32 m_turboTime;

        /* # Le nombre de tour � effectuer pour valider une course */
        static const Uint32 m_nbLap;

        /* # Le nombre de raffraichissement par minute */
        static const Uint32 m_framerate;

        /* # La dur�e en milliseconde qu'il faut rester appuyer sur les gaz pour attendre la vitesse de croisiere */
        static const Uint32 m_time2SpeedMax;

        /* # Vitesses marche avant et marche arriere */
        static const float m_fwdSpeed, m_revSpeed;

        /* # Le pourcentage d'augmentation de la vitesse des IAs en fonction de leurs difficult�s */
        static const float m_difficultyIApercentage;

        /* # Le titre de la fenetre */
        static const std::string m_title;

        /* # Le facteur de vitesse des IAs qui va augmenter � chaque fois qu'on complete les 3 courses */
        static float m_speedFactorIA;

        /* # Membre qui permet de connaitre laquelle des trois courses est charg�es */
        RaceNumber m_rNumber;

        /* # Le score du joueur */
        Uint32 m_score;
};

#endif
