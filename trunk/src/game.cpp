#include "game.hpp"
#include "r1.hpp"
#include "r2.hpp"
#include "r3.hpp"

#include <SDL/SDL_image.h>
#include <stdexcept>
#include <Windows.h>

/* On initialise les variables statiques constantes */
const Uint32 Game::m_width = 600;
const Uint32 Game::m_height = 400;
const Uint32 Game::m_shapeSize = 40;
const Uint32 Game::m_turboTime = 2000;
const Uint32 Game::m_time2SpeedMax = 1000;
const float Game::m_fwdSpeed = 2;
const float Game::m_revSpeed = m_fwdSpeed / 2;
const Uint32 Game::m_nbLap = 2;
float Game::m_speedFactorIA = 1;
const std::string Game::m_title = "Projet Genie Logiciel 3A - GSTL";
const Uint32 Game::m_framerate = 60;

Uint32 Game::time_left(Uint32 &next_time)
{
    Uint32 now;
    now = SDL_GetTicks();

    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

Game::Game()
: m_currentRace(NULL), m_isOk(true), m_window(NULL), m_ico(NULL),
  m_rNumber(Race1)
{
    /* # Chargement des composants vidéos de la librairie */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    /* # On charge et on place l'icone de l'application */
    m_ico = IMG_Load("sprites/gstl");
    SDL_WM_SetIcon(m_ico, NULL);

    /* # On utilise le double-buffering et la mémoire vidéo */
    m_window = SDL_SetVideoMode(m_width, m_height, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if(m_window == NULL)
    {
        /* # On gère correctement les erreurs qui peuvent se produire */
        fprintf(stderr, "SDL_SetVideoMode failed with this error : %s.\n", SDL_GetError());

        /* On oublie pas de quitter proprement avec un appel explicite au destructeur */
        this->~Game();

        /* # On informe le code appelant que la construction c'est mal passée */
        throw std::runtime_error("SDL_SetVideoMode failed.");
    }

    /* # On renome la fenetre */
    SDL_WM_SetCaption(m_title.c_str(), NULL);

    /* # On commence par la première course */
    m_currentRace = new R1(m_window);
}

Game::~Game()
{
    /* # On detruit les courses */
    delete m_currentRace;

    /* # On décharge la librarie proprement à la mort de l'instance du jeux */
    SDL_Quit();
}

void Game::start()
{
    /* # Chargement du niveau */
    m_currentRace->load();

    eventloop();
}

void Game::UpdateEvents(Input* in, bool& continuer)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                in->key[event.key.keysym.sym] = 1;
            break;

            case SDL_KEYUP:
                in->key[event.key.keysym.sym] = 0;
            break;

            case SDL_QUIT:
                continuer = false;
            break;

            default:
            break;
        }
    }
}

void Game::eventloop()
{
    int nbLap = 0;
    Input in = {0};
    bool continuer = true;
    Uint32 tick_interval = 1000 / m_framerate, beforefwd = SDL_GetTicks(),
    beforerev = SDL_GetTicks(), next_time = SDL_GetTicks() + tick_interval, turbo = 0,
    turbotime = m_turboTime, collision = SDL_GetTicks();

    while(continuer)
    {
        /* # On met a jour le tableau des touches enfoncees */
        UpdateEvents(&in, continuer);

        /* # On rafraichit l'affichage et on deplace l'IA */
        m_currentRace->refresh();
        m_currentRace->moveIAs();

        /* # Si le turbo est terminé on retablit la vitesse de croisiere */
        if(turbo != 0 && SDL_GetTicks() >= turbo + turbotime)
        {
            turbo = 0;
            m_currentRace->getPlayerCar()->setNormalSpeed();

            /* # On reaffecte le temps de turbo */
            turbotime = m_turboTime;
        }
        /* # Tant qu'on est bloque on affecte le timer au temps courant */
        if(m_currentRace->getPlayerCar()->isBlocked())
        {
            collision = SDL_GetTicks();
        }
        /* # Tant qu'on n'enfonce pas la touche pour avancer ou reculer ou les deux on affecte nos tick au temps actuel */
        if(!in.key[SDLK_UP])
            beforefwd = SDL_GetTicks();

        if(!in.key[SDLK_DOWN])
            beforerev = SDL_GetTicks();

        if(in.key[SDLK_UP] && in.key[SDLK_DOWN])
        {
            beforefwd = SDL_GetTicks();
            beforerev = SDL_GetTicks();
        }

        /* # Si on appuie sur la touche pour avancer sans appuyer sur celle pour reculer on va pouvoir avancer */
        if(in.key[SDLK_UP] && !in.key[SDLK_DOWN])
        {
            /* # On attend une seconde avant de demarrer */
            if(SDL_GetTicks() > (beforefwd + m_time2SpeedMax))
            {
                if(SDL_GetTicks() < collision+1000)
                {
                    m_currentRace->getPlayerCar()->collisionRecovering();
                }
                m_currentRace->movePlayerCar(SDLK_UP);
                if(m_currentRace->getPlayerCar()->isBlocked() && SDL_GetTicks() >= collision+1000)
                {
                    m_currentRace->getPlayerCar()->setNormalSpeed();
                }

                if(m_currentRace->checkCheckPoint() == Race::Finished)
                {
                    nbLap++;

                    if(nbLap == Game::m_nbLap)
                    {
                        nbLap = 0;
                        beforefwd = SDL_GetTicks();

                        delete m_currentRace;

                        switch(m_rNumber)
                        {
                            case Race1 :
                                m_currentRace = new R2(m_window);
                                m_rNumber = Race2;
                            break;

                            case Race2 :
                                m_currentRace = new R3(m_window);
                                m_rNumber = Race3;
                            break;

                            case Race3 :
                                /* # On vient de finir un cycle, on incremente la difficulte des IAs */
                                m_speedFactorIA += m_speedFactorIA * (20.0 / 100);

                                m_currentRace = new R1(m_window);
                                m_rNumber = Race1;
                            break;
                        }

                        cleanScreen();
                        m_currentRace->load();
                    }
                }
            }
        }

        /* # Si on appuie sur la touche pour reculer sans appuyer sur celle pour avancer on va pouvoir reculer */
        if(in.key[SDLK_DOWN] && !in.key[SDLK_UP])
        {
            /* On attend une seconde avant de demarrer */
            if(SDL_GetTicks() > (beforerev + m_time2SpeedMax))
                m_currentRace->movePlayerCar(SDLK_DOWN);
        }

        /* # Si on enfonce la touche droite ou gauche on change la direction de la voiture */
        if(in.key[SDLK_LEFT])
        {
            m_currentRace->getPlayerCar()->loadAnotherPosition(SDLK_LEFT);
            in.key[SDLK_LEFT] = 0;
        }

        if(in.key[SDLK_RIGHT])
        {
            m_currentRace->getPlayerCar()->loadAnotherPosition(SDLK_RIGHT);
            in.key[SDLK_RIGHT] = 0;
        }

        /* # Si on appuie sur espace ca pousse ! */
        if(in.key[SDLK_SPACE])
        {
            /* # Si il reste des turbos en stock */
            if(m_currentRace->useTurbo())
            {
                /* # Si on a deja un turbo d'active on incremente le temps de turbo */
                if(turbo != 0)
                    turbotime += Game::m_turboTime;
                else
                    turbo = SDL_GetTicks();
            }

            in.key[SDLK_SPACE] = 0;
        }

        /* # On fait un delay (ie un sleep) avec le temps qu'il nous reste avant le prochain rafraichissement pour avoir un framerate fixe */
        SDL_Delay(time_left(next_time));
        next_time += tick_interval;
    }
}



Uint32 Game::getNbHorizontalSprites()
{
    return m_height / m_shapeSize;
}

Uint32 Game::getNbVerticalSprites()
{
    return m_width / m_shapeSize;
}

Uint32 Game::getShapeSize()
{
    return m_shapeSize;
}

Uint32 Game::getSpeedFactorIA()
{
    return m_speedFactorIA;
}

float Game::getFwdSpeed()
{
    return m_fwdSpeed;
}

float Game::getRevSpeed()
{
    return m_revSpeed;
}

Uint32 Game::getTurboTime()
{
    return m_turboTime;
}

void Game::cleanScreen()
{
    SDL_FillRect(m_window, NULL, SDL_MapRGB(m_window->format, 0xff, 0xff, 0xff));
}
