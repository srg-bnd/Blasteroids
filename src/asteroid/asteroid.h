// Asteroid

#include <allegro5/allegro5.h>

typedef struct
{
    float screenX;
    float screenY;
    float orientation;
    float speed;
    int isKilled;
    float rotation;
    float rotationPerFrame;
    float scale;
    ALLEGRO_COLOR color;
} Asteroid;

Asteroid createAsteroid();
Asteroid drawAsteroid(Asteroid*);
