#include <SDL_easy.h>
#include <switch.h>

#define MAX_POINTS      9
#define MOVE_DISTANCE   5
#define MAX_UPPER_Y     70
#define MAX_LOWER_Y     (SCREEN_H - (70 * 2))
#define DEV_MODE

typedef struct
{
    uint64_t down;
    uint64_t held;
} input_t;

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
    int x;
    int y;
    int r;
    uint8_t colour;
} ball_t;

typedef struct
{
    shape_t shape;
    uint8_t score;
} player_t;

player_t player1;
player_t player2;
ball_t ball;


void poll_input(input_t *k)
{
    hidScanInput();
    k->down = hidKeysDown(CONTROLLER_P1_AUTO);
    k->held = hidKeysHeld(CONTROLLER_P1_AUTO);
}

void setup_ball(void)
{
    ball.x = 300;           // will randomise whose side the ball spawns on later.
    ball.y = SCREEN_H / 2;  // needs to be slighly more up.
    ball.r = 25;
    ball.colour = Colour_Nintendo_Cyan;
}

void setup_players(void)
{
    player1.shape.x = 80;
    player1.shape.y = SCREEN_H / 2; // will be a bit less after.
    player1.shape.w = 10;
    player1.shape.h = 50;
    player1.shape.colour = Colour_Nintendo_White;
    player1.score = 0;

    player2.shape.x = SCREEN_W - 80;
    player2.shape.y = SCREEN_H / 2; // will be a bit less after.
    player2.shape.w = 10;
    player2.shape.h = 50;
    player2.shape.colour = Colour_Nintendo_White;
    player2.score = 0;
}

void render_ball(void)
{
    SDL_DrawCircle(ball.colour, ball.x, ball.y, ball.r);
}

void render_players(void)
{
    SDL_DrawShape(player1.shape.colour, player1.shape.x, player1.shape.y, player1.shape.w, player1.shape.h);
    SDL_DrawShape(player2.shape.colour, player2.shape.x, player2.shape.y, player2.shape.w, player2.shape.h);

    #ifdef DEV_MODE
    {
        SDL_DrawText(fntSmall, 70, SCREEN_H - 35, Colour_Nintendo_Grey, "p1: x %d, y %d.                p2: x %d, y %d.                ball: x %d, y %d, r %d",
                    player1.shape.x, player1.shape.y, player2.shape.x, player2.shape.y, ball.x, ball.y, ball.r);
    }
    #endif
}

void render_score(void)
{
    SDL_DrawText(fntSmall, 200, 15, Colour_Nintendo_White, "Score Player 1: %u", player1.score);
    SDL_DrawText(fntSmall, 800, 15, Colour_Nintendo_White, "Score Player 2: %u", player2.score);
}

void render_background(void)
{
    SDL_DrawShape(Colour_Nintendo_Black, 0, 0, SCREEN_W, SCREEN_H);
    SDL_DrawShape(Colour_Nintendo_White, 30, 45, SCREEN_W - (30 * 2), 2);
    SDL_DrawShape(Colour_Nintendo_White, 30, SCREEN_H - 45, SCREEN_W - (30 * 2), 2);
}

void render_game(void)
{
    SDL_ClearRenderer();
    render_background();
    render_score();
    render_players();
    render_ball();
    SDL_UpdateRenderer();
}

void move_player_down(player_t *p)
{
    p->shape.y = p->shape.y + MOVE_DISTANCE > MAX_LOWER_Y ? MAX_LOWER_Y : p->shape.y + MOVE_DISTANCE;
}

void move_player_up(player_t *p)
{
    p->shape.y = p->shape.y - MOVE_DISTANCE < MAX_UPPER_Y ? MAX_UPPER_Y : p->shape.y - MOVE_DISTANCE;
}

void main_game_loop(void)
{
    while (appletMainLoop()) // have this instead check for score value.
    {
        input_t k;
        poll_input(&k);

        if (k.held & KEY_LSTICK_DOWN)
            move_player_down(&player1);
        if (k.held & KEY_LSTICK_UP)
            move_player_up(&player1);

        if (k.held & KEY_RSTICK_DOWN)
            move_player_down(&player2);
        if (k.held & KEY_RSTICK_UP)
            move_player_up(&player2);

        #ifdef DEV_MODE
        {
            if (k.down & KEY_PLUS)
                break;

            if (k.down & KEY_MINUS)
            {
                setup_players();
                setup_ball();
            }
        }
        #endif

        render_game();

        // todo:
        // update ball position.
        // check if player scored.
        // update score.
        // check score against score max.
    }
}

int main(int argc, char *argv[])
{
    // init sdl easy.
    SDL_EasyInit();

    // setup the players and the ball.
    setup_players();
    setup_ball();

    // main game loop.
    main_game_loop();

    // exit sdl easy.
    SDL_EasyExit();
    return 0;
}