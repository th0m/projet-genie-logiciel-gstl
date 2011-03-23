#include <iostream>
#include "game.hpp"

int main(int argc, char* argv[])
{
    try
    {
        Game g;
        g.start();
    }
    catch(...)
    {
    }

    return EXIT_SUCCESS;
}
