#include "game.hpp"
#include "server.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char** argv)
{
    if (game.start() != 0)
        return -1;

    int retcode = game.getServer()->start();

    if (retcode == 0)
    {
        // Fix crash-on-exit bug on Windows by calling TerminateProcess manually
        #ifdef _WIN32
	        TerminateProcess(GetCurrentProcess(), EXIT_SUCCESS);
        #endif
        return 0;
    }
    else
        return retcode;
}
