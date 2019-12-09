#include <switch.h>
#include "sdl_easy.h"
#include "sdl_ui_debug.h"


void app_init()
{
    // shared fonts.
    if (R_FAILED(plInitialize()))   fatalThrow(0xE0E0);

    // for loading textures.
    //if (R_FAILED(romfsInit()))      fatalThrow(0xE0E1);
    
    SDL_EasyInit();
}

void app_exit()
{
    plExit();
    //romfsExit();
    SDL_EasyExit();
}

int main(int argc, char *argv[])
{
    app_init();

    // enter shape edit mode.
    ui_debug_shape_edit();

    app_exit();
    return 0;
}