/*
* I wrote this header to be as portable as possible for other homebrew switch projects
* The only thing that needs to be changed will be the name / number of textures you want to load
* If you decide to use this header and add functions, please consider opening a pr for said functions
* I would greatly appreaciate it :)
*
* TotalJustice.
*/

#ifndef _SHAPE_EDITOR_H_
#define _SHAPE_EDITOR_H_


#include <stdint.h>

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    uint8_t colour;
} shape_t;

typedef struct
{
    uint64_t down;
    uint64_t held;
} input_t;

typedef enum
{
    ShapeStep_Small     = 1,
    ShapeStep_Normal    = 25,
    ShapeStep_Large     = 100,
} ShapeStep;    // not implimented yet...


//
void poll_input(input_t *k);

//
uint8_t next_colour(uint8_t colour);
uint8_t previous_colour(uint8_t colour);

//
int shape_increase_x(shape_t *shape);
int shape_increase_y(shape_t *shape);
int shape_increase_w(shape_t *shape);
int shape_increase_h(shape_t *shape);

//
int shape_decrease_x(shape_t *shape);
int shape_decrease_y(shape_t *shape);
int shape_decrease_w(shape_t *shape);
int shape_decrease_h(shape_t *shape);

//
void shape_init(shape_t *shape);
void shape_dump(shape_t *shape);
void render_shape(shape_t *shape);
void shape_edit(void);

#endif