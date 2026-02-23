#include <stdbool.h>
#include <allegro5/allegro5.h>

#ifndef TYPES_H
#define TYPES_H

#define DEG_TO_RAD(deg) ((deg) * 0.017453292519943295f)

typedef struct Blast
{
    float screenX;
    float screenY;
    float orientation;
    float speed;
    bool isDone;

    ALLEGRO_COLOR color;
} Blast;

typedef struct BlastNode
{
    Blast* blast;
    struct BlastNode* next;
    struct BlastNode* prev;
} BlastNode;

typedef struct Spaceship
{
    float screenX;
    float screenY;
    float orientation;
    float speed;
    bool isKilled;
    int lives;

    ALLEGRO_COLOR color;

    BlastNode* headBlastList;
    BlastNode* lastBlastList;
} Spaceship;

typedef struct Asteroid
{
    float screenX;
    float screenY;
    float orientation;
    float speed;
    bool isKilled;
    float rotation;
    float rotationPerFrame;
    float scale;

    ALLEGRO_COLOR color;
} Asteroid;

typedef struct Game
{
    bool needDraw;

    ALLEGRO_EVENT event;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* display;

    Spaceship* spaceship;
} Game;

#endif
