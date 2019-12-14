#include <switch.h>
#include "sdl_easy.h"
#include "sdl_ui_debug.h"


//#define ROMFS_LOAD


void app_init()
{
    // shared fonts.
    if (R_FAILED(plInitialize()))   fatalThrow(0xE0E0);

    #ifdef ROMFS_LOAD
    if (R_FAILED(romfsInit()))      fatalThrow(0xE0E1);
    #endif
    
    SDL_EasyInit();
}

void app_exit()
{
    plExit();
    #ifdef ROMFS_LOAD
    romfsExit();
    #endif
    SDL_EasyExit();
}

int main(int argc, char *argv[])
{
    app_init();

    ui_debug_shape_edit();

    app_exit();
    return 0;
}