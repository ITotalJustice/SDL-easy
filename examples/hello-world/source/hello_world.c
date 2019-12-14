#include "sdl_easy.h"
#include <switch.h>


int main(int arcg, char *argv[])
{
    // init sdl easy.
    SDL_EasyInit();

    // draw the background.
    SDL_EasyDrawShape(Colour_Nintendo_Black, 0, 0, SCREEN_W, SCREEN_H);

    // draw "hello world!"
    SDL_EasyDrawText(fntMedium, 530, 300, Colour_Nintendo_White, "hello world!");

    // refresh the screen.
    SDL_EasyUpdateRenderer();


    // loop until you press B to exit.
    while (1)
    {
        hidScanInput();
        uint64_t input = hidKeysDown(CONTROLLER_P1_AUTO);
        if (input & KEY_B)
            break;
    }

    // exit sdl easy.
    SDL_EasyExit();
    return 0;
}