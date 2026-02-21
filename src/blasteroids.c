// Core

#include "blasteroids.h"
#include "asteroid/asteroid.h"
#include "blast/blast.h"
#include "spaceship/spaceship.h"

int main() {
    Blasteroids();

    return 0;
}

int Blasteroids()
{
    Game* game = initGame();

    registerEvents(game);
    al_start_timer(game->timer);

    bool running = true;
    while(running)
    {
        al_wait_for_event(game->queue, &game->event);

        switch (game->event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            game->redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            handleEventKeyDown(game);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            running = false;
            break;
        }

        if(game->redraw && al_is_event_queue_empty(game->queue))
        {
            al_flip_display();
            game->redraw = false;
        }
    }

    closeGame(game);

    return 0;
}

Game* initGame()
{
    Game* game = malloc(sizeof(Game));

    al_init();
    al_install_keyboard();

    game->redraw = true;
    game->timer = al_create_timer(1.0 / 30.0);
    game->queue = al_create_event_queue();
    game->display = al_create_display(1200, 800);

    return game;
}

int closeGame(Game* game)
{
    al_destroy_display(game->display);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->queue);

    free(game);

    al_uninstall_system();

    return 0;
}

int registerEvents(Game* game)
{
    al_register_event_source(game->queue, al_get_keyboard_event_source());
    al_register_event_source(game->queue, al_get_display_event_source(game->display));
    al_register_event_source(game->queue, al_get_timer_event_source(game->timer));

    return 0;
}

void handleEventKeyDown(Game *game) {
    switch (game->event.keyboard.keycode)
    {
    case ALLEGRO_KEY_LEFT:
        /* code */
        break;
    case ALLEGRO_KEY_RIGHT:
        /* code */
        break;
    case ALLEGRO_KEY_UP:
        /* code */
        break;
    case ALLEGRO_KEY_DOWN:
        /* code */
        break;
    case ALLEGRO_KEY_SPACE:
        /* code */
        break;
    default:
        break;
    }
}
