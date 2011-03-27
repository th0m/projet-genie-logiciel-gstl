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
        fprintf(stdout, "Exception catched, a run-time error occured.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
