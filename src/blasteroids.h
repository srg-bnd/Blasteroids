// Core

#include <stdlib.h>
#include <stdbool.h>

#include <allegro5/allegro5.h>

typedef struct
{
    bool redraw;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;
} Game;

int Blasteroids();
Game* initGame();
int closeGame(Game* game);
int registerEvents(Game* game);
void handleEventKeyDown(Game *game);
