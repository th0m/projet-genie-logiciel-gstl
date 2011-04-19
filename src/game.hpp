/**
 * \file game.hpp
 * \brief Gestion du jeux.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de gérer l'ensemble du jeux, l'enchainement entres les courses, les victoires etc.
 *
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <string>

/* # Pour eviter le probleme des inclusions cycliques : classe A a besoin de la classe B, et la classe B a besoin de la classe A */
class Race;

class Game
{
    public:

        /**
         * \fn explicit Game()
         * \brief Constructeur de la classe, instanciation de la fenetre etc.
         */
        explicit Game();

        /**
         * \fn ~Game()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouees.
         */
        ~Game();

        /**
         * \fn void start()
         * \brief Fonction qui démarre le jeu.
         */
        void start();


        /**
         * \fn static Uint32 getNbHorizontalSprites()
         * \brief Fonction qui permet de récuperer le nombre de sprite à disposer sur l'horizontale.
         *
         * \return Le nombre de shape par ligne.
         */
        static Uint32 getNbHorizontalSprites();

        /**
         * \fn static Uint32 getNbVerticalSprites()
         * \brief Fonction qui permet de récuperer le nombre de sprite à disposer sur la verticale.
         *
         * \return Le nombre de shape par colonne.
         */
        static Uint32 getNbVerticalSprites();

        /**
         * \fn static Uint32 getShapeSize()
         * \brief Fonction qui permet de récuperer la taille d'un sprite.
         *
         * \return La taille en pixel d'une shape (NB: une shape est carrée).
         */
        static Uint32 getShapeSize();

        /**
         * \fn static float getFwdSpeed()
         * \brief Fonction accesseur permettant de connaitre la vitesse de croisière en marche avant.
         *
         * \return La vitesse en marche avant de la voiture (NB: n'est rien d'autre qu'un nombre de pixel).
         */
        static float getFwdSpeed();

        /**
         * \fn static Uint32 getSpeedIA()
         * \brief Permet de connaitre la vitesse des IAs.
         *
         * \return La vitesse des IAs (NB: n'est rien d'autre qu'un nombre de pixel).
         */
        static Uint32 getSpeedIA();

        /**
         * \fn static float getDifficultyIAPercentage()
         * \brief Permet de savoir le pourcentage de difficulte qu'une IA doit avoir par rapport à une autre.
         *
         * \return La vitesse des IAs (NB: n'est rien d'autre qu'un nombre de pixel).
         */
        static float getDifficultyIAPercentage();

    private:

        /**
         * \enum RaceNumber
         * \brief Indique la course que l'on est en train de jouer.
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
         * \brief Tableau representant l'etat des touches du clavier à un instant t.
         *
         */
        struct Input
        {
            char key[SDLK_LAST];
        };

        /**
         * \fn void eventloop()
         * \brief La boucle principale d'evenement.
         */
        void eventloop();

        /**
         * \fn void cleanScreen()
         * \brief Fonction qui permet de nettoyer l'écran principal.
         */
        void cleanScreen();

        /**
         * \fn void updateEvents(Input* in, bool& continuer)
         * \brief Fonction qui permet de mettre à jour les evenements.
         *
         * \param in Le tableau de l'état de toutes les touches du clavier.
         * \param continuer Un booleen qui va nous servir à savoir si nous devons quitter ou pas l'application.
         */
        void updateEvents(Input* in, bool& continuer);

        /**
         * \fn void handleScore()
         * \brief Fonction qui va gérer l'ajout des scores.
         */
        void handleScore();

        /**
         * \fn void time_left(Uint32 &next_time)
         * \brief Fonction qui donne le temps a sleep avant le prochaine rafraichissement.
         *
         * \param next_time Le prochain raffraichissement.
         */
        Uint32 time_left(Uint32 &next_time);



        Race *m_currentRace; /*!< Pointeur vers la course que l'on est en train de jouer */

        bool m_isOk; /*!< Sommes-nous toujours dans la boucle d'evenement ? */

        SDL_Surface *m_window, *m_ico; /*!< Pointeur sur la surfa ce jeux, et sur l'icone */

        static const Uint32 m_width, m_height; /*!< Largeur et hauteur de la fenetre graphique */

        static const Uint32 m_shapeSize; /*!< La taille en pixel d'une shape */

        static const Uint32 m_turboTime; /*!< La durée en millisecondes d'un turbo */

        static const Uint32 m_nbLap; /*!< Le nombre de tour à effectuer pour valider une course */

        static const Uint32 m_framerate; /*!< Le nombre de raffraichissement par minute */

        static const Uint32 m_time2SpeedMax; /*!< La durée en milliseconde qu'il faut rester appuyer sur les gaz pour attendre la vitesse de croisiere */

        static const float m_fwdSpeed, m_revSpeed; /*!< Vitesses marche avant et marche arriere  */

        static const float m_difficultyIApercentage; /*!< Le pourcentage d'augmentation de la vitesse des IAs en fonction de leurs difficultés */

        static const std::string m_title; /*!< Le titre de la fenetre */

        static float m_speedIA; /*!< Le facteur de vitesse des IAs qui va augmenter à chaque fois qu'on complete les 3 courses */

        RaceNumber m_rNumber; /*!< Membre qui permet de connaitre laquelle des trois courses est chargées */

        Uint32 m_score; /*!< Le score du joueur */
};

#endif
