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
const float Game::m_fwdSpeed = 2;
const float Game::m_revSpeed = m_fwdSpeed / 2;
const Uint32 Game::m_nbLap = 2;
Uint32 Game::m_speedFactorIA = 1;
const std::string Game::m_title = "Projet Genie Logiciel 3A - GSTL";

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

    /* # Pour des raisons d'occupation CPU */
    Sleep(6);
}

void Game::eventloop()
{
    int nbLap = 0;
    Input in = {0};
    bool continuer = true, enavant = false, enarriere = false;

    while(continuer)
    {
        UpdateEvents(&in,continuer);
        m_currentRace->refresh();

        if(!in.key[SDLK_UP])
            enavant = false;

        if(in.key[SDLK_UP])
        {
            if(!enavant)
                Sleep(1000);

            m_currentRace->movePlayerCar(SDLK_UP);

            if(m_currentRace->checkCheckPoint() == Race::Finished)
            {
                nbLap++;
                printf("Fin de tours\n");
                fflush(stdout);

                if(nbLap == Game::m_nbLap)
                {
                    nbLap = 0;
                    printf("Switch de course\n");
                    fflush(stdout);

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
                            /* On vient de finir un cycle, on incremente la difficulte des IAs */
                            Game::m_speedFactorIA *= 2;

                            m_currentRace = new R1(m_window);
                            m_rNumber = Race1;
                        break;
                    }

                    cleanScreen();
                    m_currentRace->load();
                }
            }
            enavant = true;
        }

        if(!in.key[SDLK_DOWN])
            enarriere = false;

        if(in.key[SDLK_DOWN])
        {
            if(!enarriere)
                Sleep(1000);

            m_currentRace->movePlayerCar(SDLK_DOWN);
            enarriere = true;
        }

        if(in.key[SDLK_LEFT])
        {
            m_currentRace->changePlayerCarPosition(SDLK_LEFT);
            in.key[SDLK_LEFT] = 0;
        }

        if(in.key[SDLK_RIGHT])
        {
            m_currentRace->changePlayerCarPosition(SDLK_RIGHT);
            in.key[SDLK_RIGHT] = 0;
        }

        if(in.key[SDLK_SPACE])
        {
            m_currentRace->useTurbo();
            in.key[SDLK_SPACE] = 0;
        }

        /* # Occupation CPU */
        Sleep(1);
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
