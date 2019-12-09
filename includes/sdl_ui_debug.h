/*
* I wrote this header to be as portable as possible for other homebrew switch projects
* The only thing that needs to be changed will be the name / number of textures you want to load
* If you decide to use this header and add functions, please consider opening a pr for said functions
* I would greatly appreaciate it :)
*
* TotalJustice.
*/

#ifndef _SDL_UI_DEBUG_H_
#define _SDL_UI_DEBUG_H_


#include <stdint.h>

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    uint8_t colour;
} ui_debug_shape_t;

typedef struct
{
    uint64_t down;
    uint64_t held;
} ui_debug_input_t;

typedef enum
{
    ShapeStep_Small     = 1,
    ShapeStep_Normal    = 25,
    ShapeStep_Large     = 100,
} ShapeStep;    // not implimented yet...


//
void ui_debug_poll_input(ui_debug_input_t *k);

//
uint8_t ui_debug_next_colour(uint8_t colour);
uint8_t ui_debug_previous_colour(uint8_t colour);

//
int ui_debug_shape_increase_x(ui_debug_shape_t *shape);
int ui_debug_shape_increase_y(ui_debug_shape_t *shape);
int ui_debug_shape_increase_w(ui_debug_shape_t *shape);
int ui_debug_shape_increase_h(ui_debug_shape_t *shape);

//
int ui_debug_shape_decrease_x(ui_debug_shape_t *shape);
int ui_debug_shape_decrease_y(ui_debug_shape_t *shape);
int ui_debug_shape_decrease_w(ui_debug_shape_t *shape);
int ui_debug_shape_decrease_h(ui_debug_shape_t *shape);

//
void ui_debug_shape_init(ui_debug_shape_t *shape);
void ui_debug_shape_dump(ui_debug_shape_t *shape);
void ui_debug_render_shape(ui_debug_shape_t *shape);
void ui_debug_shape_edit(void);

#endif