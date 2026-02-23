// Core

#include <stdlib.h>

#include "config.h"
#include "blasteroids.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include "types.h"
#include "asteroid/asteroid.h"
#include "blast/blast.h"
#include "spaceship/spaceship.h"

Game* game;

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    initGame();
    runGame();
    closeGame();

    return 0;
}

static int initGame(void)
{
    game = malloc(sizeof(Game));

    if (!al_init()) exit(1);
    al_init_primitives_addon();
    al_install_keyboard();

    game->needDraw = true;
    game->timer = al_create_timer(1.0 / CONFIG_FPS);
    game->queue = al_create_event_queue();
    game->display = al_create_display(CONFIG_SCREEN_HIGHT, CONFIG_SCREEN_WEIGHT);

    return 0;
}

static int runGame(void)
{
    registerEvents();

    game->spaceship = createSpaceship();

    al_start_timer(game->timer);

    bool running = true;
    while(running)
    {
        if(game->needDraw && al_is_event_queue_empty(game->queue))
        {
            tick();
            game->needDraw = false;
        }

        al_wait_for_event(game->queue, &game->event);

        switch (game->event.type)
        {
            case ALLEGRO_EVENT_TIMER:
            {
                game->needDraw = true;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN:
            {
                handleEventKeyDown();
                break;
            }
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
            {
                running = false;
                break;
            }
        }
    }

    return 0;
}

static int closeGame(void)
{
    al_destroy_display(game->display);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->queue);

    free(game);

    al_uninstall_system();

    return 0;
}

static int registerEvents(void)
{
    al_register_event_source(game->queue, al_get_keyboard_event_source());
    al_register_event_source(game->queue, al_get_display_event_source(game->display));
    al_register_event_source(game->queue, al_get_timer_event_source(game->timer));

    return 0;
}

static void handleEventKeyDown(void) {
    switch (game->event.keyboard.keycode)
    {
        case ALLEGRO_KEY_LEFT:
        {
            leftSpaceship(game->spaceship);
            break;
        }
        case ALLEGRO_KEY_RIGHT:
        {
            rightSpaceship(game->spaceship);
            break;
        }
        case ALLEGRO_KEY_UP:
        {
            upSpaceship(game->spaceship);
            break;
        }
        case ALLEGRO_KEY_DOWN:
        {
            downSpaceship(game->spaceship);
            break;
        }
        case ALLEGRO_KEY_SPACE:
        {
            blastSpaceship(game->spaceship);
            break;
        }
        default:
        {
            /* code */
            break;
        }
    }
}

static void tick(void)
{
    pushBlasts(game->spaceship);

    draw();

    al_flip_display();
}

static void draw(void) {
    al_clear_to_color(al_color_name(CONFIG_BACKGROUND));

    drawSpaceship(game->spaceship);
    drawBlasts(game->spaceship);
}
