/*
* I wrote this header to be as portable as possible for other homebrew switch projects
* The only thing that needs to be changed will be the name / number of textures you want to load
* If you decide to use this header and add functions, please consider opening a pr for said functions
* I would greatly appreaciate it :)
*
* TotalJustice.
*/

#include <stdint.h>
#include <switch.h>
#include <sdl_easy.h>
#include "sdl_ui_debug.h"



/*
*   Poll Input.
*/

void ui_debug_poll_input(ui_debug_input_t *k)
{
    hidScanInput();
    k->down = hidKeysDown(CONTROLLER_P1_AUTO);
    k->held = hidKeysHeld(CONTROLLER_P1_AUTO);
}



/*
*   Change colours.
*/

uint8_t ui_debug_next_colour(uint8_t colour)
{
    return colour + 1 > COLOUR_MAX ? 0 : colour + 1;
}

uint8_t ui_debug_previous_colour(uint8_t colour)
{
    return colour == 0 ? COLOUR_MAX : colour - 1;
}



/*
* Increase Shape Size.
*/

int ui_debug_shape_increase_x(ui_debug_shape_t *shape)
{
    return shape->x + 5 > SCREEN_W ? 0 : shape->x + 5;
}

int ui_debug_shape_increase_y(ui_debug_shape_t *shape)
{
    return shape->y + 5 > SCREEN_H ? 0 : shape->y + 5;
}

int ui_debug_shape_increase_w(ui_debug_shape_t *shape)
{
    return shape->w + shape->x + 5 > SCREEN_W ? shape->w : shape->w + 5;
}

int ui_debug_shape_increase_h(ui_debug_shape_t *shape)
{
    return shape->y + shape->h + 5 > SCREEN_H ? shape->h: shape->h + 5;
}



/*
* Decrease Shape Size.
*/

int ui_debug_shape_decrease_x(ui_debug_shape_t *shape)
{
    return shape->x < 5 ? 0 : shape->x - 5;
}

int ui_debug_shape_decrease_y(ui_debug_shape_t *shape)
{
    return shape->y < 5 ? SCREEN_H : shape->y - 5;
}

int ui_debug_shape_decrease_w(ui_debug_shape_t *shape)
{
    return shape->x -shape->w < SCREEN_W * -1 ? shape->w : shape->w - 5;
}

int ui_debug_shape_decrease_h(ui_debug_shape_t *shape)
{
    return shape->y - shape->h < SCREEN_H * -1 ? shape->h : shape->h - 5;
}



/*
*   Init the shape to the deafult values.
*/

void ui_debug_shape_init(ui_debug_shape_t *shape)
{
    shape->x = SCREEN_W / 4;
    shape->y = SCREEN_H / 4;
    shape->w =  SCREEN_W / 4;
    shape->h = SCREEN_H  / 4;
    shape->colour = Colour_White;
}



/*
*   Dump shape info to the screen.
*/

void ui_debug_shape_dump(ui_debug_shape_t *shape)
{
    while (appletMainLoop())
    {
        ui_debug_input_t k;
        ui_debug_poll_input(&k);

        SDL_ClearRenderer();

        SDL_DrawShape(Colour_Nintendo_Black, 0, 0, SCREEN_W, SCREEN_H);
        SDL_DrawText(fntSmall, 100, 50, Colour_Nintendo_White, "Debug Shape Dump:");

        SDL_DrawText(fntSmall, 125, 150, Colour_Nintendo_Cyan, "x = %d", shape->x);
        SDL_DrawText(fntSmall, 125, 250, Colour_Nintendo_Cyan, "y = %d", shape->y);
        SDL_DrawText(fntSmall, 125, 350, Colour_Nintendo_Cyan, "w = %d", shape->w);
        SDL_DrawText(fntSmall, 125, 450, Colour_Nintendo_Cyan, "h = %d", shape->h);
        SDL_Colour colour = SDL_GetColour(shape->colour);
        SDL_DrawText(fntSmall, 125, 550, Colour_Nintendo_Cyan, "colour: r = %u g = %u b = %u a = %u", colour.r, colour.g, colour.b, colour.a);

        SDL_UpdateRenderer();

        if (k.down & KEY_B || k.down & KEY_PLUS)
            break;
    }
}


void ui_debug_render_shape(ui_debug_shape_t *shape)
{
    SDL_ClearRenderer();
    SDL_DrawShape(Colour_Nintendo_Black, 0, 0, SCREEN_W, SCREEN_H);

    int w_remainder = 0;
    int h_renainder = 0;

    if (shape->x + shape->w > SCREEN_W)
        w_remainder = SCREEN_W - (shape->x + shape->w);
    if (shape->y + shape->h > SCREEN_H)
        h_renainder = SCREEN_W - (shape->y + shape->h);

    if (w_remainder || h_renainder)
        SDL_DrawShape(shape->colour, 0, 0, w_remainder, h_renainder);

    SDL_DrawShape(shape->colour, shape->x, shape->y, shape->w, shape->h);

    SDL_UpdateRenderer();
}


/*
*   Debug shape draw (change size and colour).
*/

void ui_debug_shape_edit(void)
{
    ui_debug_shape_t shape;
    ui_debug_shape_init(&shape);


    while (appletMainLoop())
    {
        ui_debug_input_t k;
        ui_debug_poll_input(&k);


        /*
        *   Render shape.
        */
        
        ui_debug_render_shape(&shape);

        /*
        *   Change shape position.
        */

        if (k.held & KEY_LSTICK_UP)
            shape.y = ui_debug_shape_decrease_y(&shape);
        
        if (k.held & KEY_LSTICK_DOWN)
            shape.y = ui_debug_shape_increase_y(&shape);
        
        if (k.held & KEY_LSTICK_RIGHT)
            shape.x = ui_debug_shape_increase_x(&shape);
        
        if (k.held & KEY_LSTICK_LEFT)
            shape.x = ui_debug_shape_decrease_x(&shape);
        

        /*
        *   Change shape size.
        */

        if (k.held & KEY_RSTICK_UP)
            shape.h = ui_debug_shape_increase_h(&shape);

        if (k.held & KEY_RSTICK_DOWN)
            shape.h = ui_debug_shape_decrease_h(&shape);
        
        if (k.held & KEY_RSTICK_RIGHT)
            shape.w = ui_debug_shape_increase_w(&shape);

        if (k.held & KEY_RSTICK_LEFT)
            shape.w = ui_debug_shape_decrease_w(&shape);
        

        /*
        *   Change shape colour.
        */

        if (k.down & KEY_R)
            shape.colour = ui_debug_next_colour(shape.colour);

        if (k.down & KEY_L)
            shape.colour = ui_debug_previous_colour(shape.colour);


        /*
        *   Dump shape info.
        */

        if (k.down & KEY_A)
            ui_debug_shape_dump(&shape);


        /*
        *   Reset the shape.
        */

        if (k.down & KEY_MINUS)
            ui_debug_shape_init(&shape);
        

        /*
        *   Exit...
        */

        if (k.down & KEY_PLUS)
            break;
    }
}