/**
 * \file game.hpp
 * \brief Gestion du jeu
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <string>

/* # Pour eviter le probleme des inclusions cycliques : classe A a besoin de la classe B, et la classe B a besoin de la classe A */
class Race;

/**
 * \class Game
 * \brief Classe qui va permettre de gérer l'ensemble du jeu, l'enchainement entre les courses, les victoires etc.
*/
class Game
{
    public:

        /**
         * \fn explicit Game()
         * \brief Constructeur de la classe, instanciation de la fenêtre etc
         */
        explicit Game();

        /**
         * \fn ~Game()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouées
         */
        ~Game();

        /**
         * \fn void start()
         * \brief Fonction qui démarre le jeu
         */
        void start();


        /**
         * \fn static Uint32 getNbHorizontalSprites()
         * \brief Fonction qui permet de récuperer le nombre de sprites à disposer à l'horizontale
         *
         * \return Le nombre de shapes par ligne.
         */
        static Uint32 getNbHorizontalSprites();

        /**
         * \fn static Uint32 getNbVerticalSprites()
         * \brief Fonction qui permet de récuperer le nombre de sprites à disposer à la verticale
         *
         * \return Le nombre de shapes par colonne.
         */
        static Uint32 getNbVerticalSprites();

        /**
         * \fn static Uint32 getShapeSize()
         * \brief Fonction qui permet de récuperer la taille d'un sprite
         *
         * \return La taille en pixel d'une shape (NB: une shape est carrée)
         */
        static Uint32 getShapeSize();

        /**
         * \fn static float getFwdSpeed()
         * \brief Fonction accesseur permettant de connaître la vitesse de croisière en marche avant
         *
         * \return La vitesse en marche avant de la voiture (NB: n'est rien d'autre qu'un nombre de pixels)
         */
        static float getFwdSpeed();

        /**
         * \fn static Uint32 getSpeedIA()
         * \brief Permet de connaître la vitesse des IAs
         *
         * \return La vitesse des IAs (NB: n'est rien d'autre qu'un nombre de pixels)
         */
        static Uint32 getSpeedIA();

        /**
         * \fn static float getDifficultyIAPercentage()
         * \brief Permet de savoir le pourcentage de difficulté qu'une IA doit avoir par rapport à une autre
         *
         * \return La vitesse des IAs (NB: n'est rien d'autre qu'un nombre de pixels)
         */
        static float getDifficultyIAPercentage();

    private:

        /**
         * \enum RaceNumber
         * \brief Indique le numéro de la course sur laquelle on joue
         *
         */
        enum RaceNumber
        {
            Race1, /*!< Course numéro 1 */
            Race2, /*!< Course numéro 2 */
            Race3 /*!< Course numéro 3 */
        };

        /**
         * \struct Input
         * \brief Tableau représentant l'êtat des touches du clavier à un instant t
         *
         */
        struct Input
        {
            char key[SDLK_LAST];
        };

        /**
         * \fn void eventloop()
         * \brief La boucle principale d'évènement
         */
        void eventloop();

        /**
         * \fn void cleanScreen()
         * \brief Fonction qui permet de nettoyer l'écran principal
         */
        void cleanScreen();

        /**
         * \fn void updateEvents(Input* in, bool& continuer)
         * \brief Fonction qui permet de mettre à jour les évènements
         *
         * \param in Le tableau représentant l'êtat de toutes les touches du clavier
         * \param continuer Un booleen qui va nous servir à savoir si nous devons quitter ou pas l'application
         */
        void updateEvents(Input* in, bool& continuer);

        /**
         * \fn void handleScore()
         * \brief Fonction qui va gérer l'ajout des scores
         */
        void handleScore();

        /**
         * \fn void time_left(Uint32 &next_time)
         * \brief Fonction qui détermine le temps à sleep avant le prochain rafraîchissement
         *
         * \param next_time Le prochain rafraîchissement
         *
         * \return Le temps à sleep avant le prochain rafraîchissement
         */
        Uint32 time_left(Uint32 &next_time);



        Race *m_currentRace; /*!< Pointeur vers la course sur laquelle on joue */

        bool m_isOk; /*!< Sommes-nous toujours dans la boucle d'évènement ? */

        SDL_Surface *m_window, *m_ico; /*!< Pointeurs sur la surface du jeu, et sur l'icône */

        static const Uint32 m_width, m_height; /*!< Largeur et hauteur de la fenetre graphique */

        static const Uint32 m_shapeSize; /*!< La taille en pixel d'une shape */

        static const Uint32 m_turboTime; /*!< La durée en millisecondes d'un turbo */

        static const Uint32 m_nbLap; /*!< Le nombre de tours à effectuer pour valider une course */

        static const Uint32 m_framerate; /*!< Le nombre de rafraîchissements par minute */

        static const Uint32 m_time2SpeedMax; /*!< La durée en millisecondes qu'il faut rester appuyé sur les gaz pour atteindre la vitesse de croisière */

        static const float m_fwdSpeed, m_revSpeed; /*!< Vitesse en marche avant et en marche arrière  */

        static const float m_difficultyIApercentage; /*!< Le pourcentage d'augmentation de la vitesse des IAs en fonction de leur difficulté */

        static const std::string m_title; /*!< Le titre de la fenêtre */

        static float m_speedIA; /*!< Le facteur de vitess des IAs qui va augmenter à chaque fois qu'on complète les 3 courses */

        RaceNumber m_rNumber; /*!< Membre qui permet de connaitre laquelle des trois courses est chargée */

        Uint32 m_score; /*!< Le score du joueur */
};

#endif
