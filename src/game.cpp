#include "game.hpp"
#include "r1.hpp"
#include "r2.hpp"
#include "r3.hpp"

#include <SDL/SDL_image.h>
#include <stdexcept>

/* On initialise les variables statiques constantes */
const Uint32 Game::m_width = 600;
const Uint32 Game::m_height = 400;
const Uint32 Game::m_shapeSize = 40;
const Uint32 Game::m_turboTime = 2000;
const float Game::m_fwdSpeed = 5;
const float Game::m_revSpeed = m_fwdSpeed / 2;
const std::string Game::m_title = "Projet Genie Logiciel 3A - GSTL";

Game::Game()
: m_currentRace(NULL), m_r1(NULL), m_r2(NULL), m_r3(NULL), m_isOk(true), m_window(NULL), m_ico(NULL)
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

    /* # On instancie les courses */
    m_r1 = new R1(m_window);

    m_r2 = new R2(m_window);

    m_r3 = new R3(m_window);

    /* # On commence par la première course */
    m_currentRace = m_r1;
}

Game::~Game()
{
    /* # On detruit les courses */
    delete m_r1;
    delete m_r2;
    delete m_r3;

    /* # On décharge la librarie proprement à la mort de l'instance du jeux */
    SDL_Quit();
}

void Game::start()
{
    /* # Chargement du niveau */
    m_currentRace->load();

    eventloop();
}

void Game::eventloop()
{
    SDL_Event ev = {0};

    /* On active la repetition des touches */
    SDL_EnableKeyRepeat(100, 5);

    while(m_isOk)
    {
        SDL_WaitEvent(&ev);
        switch(ev.type)
        {
            case SDL_QUIT :
            {
                m_isOk = false;
                break;
            }

            case SDL_KEYDOWN :
            {
                switch(ev.key.keysym.sym)
                {
                    case SDLK_DOWN :
                    case SDLK_UP :
                    case SDLK_RIGHT :
                    case SDLK_LEFT :
                    {
                        m_currentRace->movePlayerCar(ev.key.keysym.sym);
                        m_currentRace->checkCheckPoint();
                        break;
                    }

                    case SDLK_SPACE :
                    {
                        m_currentRace->useTurbo();
                        m_currentRace->refresh();
                        break;
                    }

                    default:
                    break;
                }

                break;
            }

            default:
            break;
        }
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
