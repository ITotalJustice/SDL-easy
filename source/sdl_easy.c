/*
* I wrote this header to be as portable as possible for other homebrew switch projects
* The only thing that needs to be changed will be the name / number of textures you want to load
* If you decide to use this header and add functions, please consider opening a pr for said functions
* I would greatly appreaciate it :)
*
* TotalJustice.
*/

#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdint.h>
#include <stdarg.h>
#include <switch.h>

#include "sdl_easy.h"


static SDL_Window   *main_window;
static SDL_Renderer *main_renderer;


SDL_Colour colours[] =
{
    { 255, 255, 255 },          //white
    { 140, 140, 140, 255 },     //grey
    { 81, 81, 81 },             //dark grey
    { 0, 0, 0 },                //black
    { 255, 192, 203 },          //pink
    { 253, 52, 131, 1 },        //neon pink
    { 255, 105, 180 },          //hotpink
    { 255, 165, 0 },            //orange
    { 255, 255, 0 },            //yellow
    { 255, 215, 0 },            //gold
    { 139, 69, 19 },            //brown
    { 255, 0, 0 },              //red
    { 139, 0, 0 },              //dark red
    { 0, 128, 0 },              //green
    { 50, 205, 50 },            //lime green
    { 0, 255, 255 },            //aqua
    { 0, 128, 128 },            //teal
    { 0, 191, 255 },            //light blue
    { 0, 0, 255 },              //blue
    { 131, 177, 218 },          //jordy blue
    { 97, 115, 255 },           //faint blue
    { 28, 33, 73 },             //dark blue
    { 160, 32, 240 },           //purple
    { 75, 0, 130 },             //indigo
    { 245, 245, 220 },          //beige
    { 45, 45, 45 },             //n_black
    { 50, 50, 50 },             //n_light_black
    { 128, 128, 128 },          //n_silver
    { 77, 77, 77 },             //n_grey
    { 251, 251, 251 },          //n_white
    { 0, 255, 200 },            //n_cyan
    { 143, 253, 252 },          //n_teal
    { 36, 141, 199 }            //n_blue
};


SDL_Colour SDL_EasyGetColour(Colour colour_option)
{
    return colours[colour_option];
}

SDL_Window *SDL_EasyGetWindow(void)
{
    return main_window;
}

void SDL_EasyImageLoad(SDL_Texture **texture, const char *path)
{
	SDL_Surface *surface = IMG_Load(path);
    SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    *texture = SDL_CreateTextureFromSurface(main_renderer, surface);
	SDL_FreeSurface(surface);
}

void SDL_EasyImageLoadMem(SDL_Texture **texture, void *data, int size)
{
	SDL_Surface *surface = IMG_Load_RW(SDL_RWFromMem(data, size), 1);
    SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
    *texture = SDL_CreateTextureFromSurface(main_renderer, surface);
	SDL_FreeSurface(surface);
}

void SDL_EasyDrawText(TTF_Font *font, int x, int y, Colour colour, const char *text, ...)
{
    char textBuffer[256];
    va_list argv;
    va_start(argv, text);
    vsnprintf(textBuffer, sizeof(textBuffer), text, argv);
    va_end(argv);

    SDL_Colour col = SDL_EasyGetColour(colour);
    SDL_Surface *Surface = TTF_RenderUTF8_Blended_Wrapped(font, textBuffer, col, SCREEN_W);
    SDL_Texture *Tex = SDL_CreateTextureFromSurface(main_renderer, Surface);
    SDL_Rect pos = { pos.x = x, pos.y = y, pos.w = Surface ->w, pos.h = Surface->h };

    SDL_RenderCopy(main_renderer, Tex, NULL, &pos);
    SDL_DestroyTexture(Tex);
    SDL_FreeSurface(Surface);
}

void SDL_EasyDrawButton(TTF_Font *font, uint16_t btn, int x, int y, Colour colour)
{
    SDL_Colour col = SDL_EasyGetColour(colour);
    SDL_Surface *Surface = TTF_RenderGlyph_Blended(font, btn, col);
    SDL_Texture *Tex = SDL_CreateTextureFromSurface(main_renderer, Surface);
    SDL_Rect pos = { pos.x = x, pos.y = y, pos.w = Surface ->w, pos.h = Surface->h };

    SDL_RenderCopy(main_renderer, Tex, NULL, &pos);
    SDL_DestroyTexture(Tex);
    SDL_FreeSurface(Surface);
}

void SDL_EasyDrawImage(SDL_Texture *texture, int x, int y)
{
    SDL_Rect pos = { pos.x = x, pos.y = y };
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(main_renderer, texture, NULL, &pos);
}

void SDL_EasyDrawImageRotate(SDL_Texture *texture, int x, int y, double rotate)
{
    SDL_Rect pos;
    SDL_Point center;

	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);

    pos.x = 0;
    pos.y = 0;

    int halfwidth = pos.w / 2;

    center.x = halfwidth;
    center.y = pos.h - halfwidth;

    SDL_RenderCopyEx(main_renderer, texture, NULL, &pos, rotate, &center, SDL_FLIP_NONE);
}

void SDL_EasyDrawImageScale(SDL_Texture *texture, int x, int y, int w, int h)
{
    SDL_Rect pos = { pos.x = x, pos.y = y, pos.w = w, pos.h = h };
	SDL_RenderCopy(main_renderer, texture, NULL, &pos);
}

void SDL_EasyDrawShape(Colour colour, int x, int y, int w, int h)
{
    SDL_Colour col = SDL_EasyGetColour(colour);
    SDL_Rect pos = { pos.x = x, pos.y = y, pos.w = w, pos.h = h };
    SDL_SetRenderDrawColor(main_renderer, col.r, col.g, col.b, col.a);
    SDL_RenderFillRect(main_renderer, &pos);
}

void SDL_EasyDrawShapeOutline(Colour colour, int x, int y, int w, int h)
{
    SDL_Colour col = SDL_EasyGetColour(colour);
    rectangleRGBA(main_renderer, x, y,x + w, y + h, col.r, col.g, col.b, 255);
}

void SDL_EasyDrawShapeRounded(Colour colour, int x, int y, int w, int h, int r)
{
    SDL_Colour col = SDL_EasyGetColour(colour);
    roundedBoxRGBA(main_renderer, x, y,x + w, y + h, r, col.r, col.g, col.b, 255);
}

void SDL_EasyDrawShapeRoundedOutline(Colour colour, int x, int y, int w, int h, int r)
{
    SDL_Colour col = SDL_EasyGetColour(colour);
    roundedRectangleRGBA(main_renderer, x, y,x + w, y + h, r, col.r, col.g, col.b, 255);
}

void SDL_EasyDrawCircle(Colour colour, int x, int y, int r)
{
    SDL_Colour col = SDL_EasyGetColour(colour);
    filledCircleRGBA(main_renderer, x, y, r, col.r, col.g, col.b, 255);
}

void SDL_EasyDrawCircleOutline(Colour colour, int x, int y, int r)
{
    SDL_Colour col = SDL_EasyGetColour(colour);
    circleRGBA(main_renderer, x, y, r, col.r, col.g, col.b, 255);
}

void SDL_EasyScreenShotToTexture(SDL_Texture **texture)
{
    SDL_Surface *Surface = SDL_CreateRGBSurface(0, SCREEN_W, SCREEN_H, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(main_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, Surface->pixels, Surface->pitch);
    SDL_ConvertSurfaceFormat(Surface, SDL_PIXELFORMAT_RGBA8888, 0);
    *texture = SDL_CreateTextureFromSurface(main_renderer, Surface);
	SDL_FreeSurface(Surface);
}

void SDL_EasyScreenShotToFile(const char *save_path)
{
    SDL_Surface *Surface = SDL_CreateRGBSurface(0, SCREEN_W, SCREEN_H, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(main_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, Surface->pixels, Surface->pitch);
    SDL_SaveBMP(Surface, save_path);
	SDL_FreeSurface(Surface);
}

int SDL_EasyGetTextureWidth(SDL_Texture *texture)
{
    int w;
    SDL_QueryTexture(texture, NULL, NULL, &w, NULL);
    return w;
}

int SDL_EasyGetTextureHeight(SDL_Texture *texture)
{
    int h;
    SDL_QueryTexture(texture, NULL, NULL, NULL, &h);
    return h;
}

void SDL_EasyLoadFonts(void)
{
    // Get the fonts from system
    PlFontData font;
    PlFontData button_data;
    plGetSharedFontByType(&font, PlSharedFontType_Standard);
    plGetSharedFontByType(&button_data, PlSharedFontType_NintendoExt);

    fntSmall        = TTF_OpenFontRW(SDL_RWFromMem(font.address, font.size), 1, 28);
    fntMedium       = TTF_OpenFontRW(SDL_RWFromMem(font.address, font.size), 1, 36);
    fntLarge        = TTF_OpenFontRW(SDL_RWFromMem(font.address, font.size), 1, 44);
    fntButton       = TTF_OpenFontRW(SDL_RWFromMem(button_data.address, button_data.size), 1, 28);
    fntButtonBig    = TTF_OpenFontRW(SDL_RWFromMem(button_data.address, button_data.size), 1, 36);
}

void SDL_CloseFonts(void)
{
    TTF_CloseFont(fntSmall);
    TTF_CloseFont(fntMedium);
    TTF_CloseFont(fntLarge);
    TTF_CloseFont(fntButton);
    TTF_CloseFont(fntButtonBig);
}

void SDL_EasyLoadTextures(void)
{
    //SDL_EasyImageLoad(&example, "romfs:/example.jpg");
}

void SDL_EasyDestroyTextures(void)
{
    //SDL_DestroyTexture(example);
}

void SDL_EasyClearRenderer(void)
{
    SDL_RenderClear(main_renderer);
}

void SDL_EasyUpdateRenderer(void)
{
    SDL_RenderPresent(main_renderer);
}

void SDL_EasyInit(void)
{
    TTF_Init();
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    main_window = SDL_CreateWindow("totaljustice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    
    // highest quality
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    plInitialize();
    romfsInit();
    
    SDL_EasyLoadFonts();
    SDL_EasyLoadTextures();
}

void SDL_EasyExit(void)
{
    SDL_EasyCloseFonts();
    SDL_EasyDestroyTextures();
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(main_window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    plExit();
    romfsExit();
}