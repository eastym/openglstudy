#include "fps.hpp"

int main(int args,char *argv[])
{

    FPS fps(atoi(argv[1]));

    while (1)
    {
        fps.GetFPS([](){});

    }
}