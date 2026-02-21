// Spaceship

#include <allegro5/allegro5.h>

typedef struct
{
    float screenX;
    float screenY;
    float orientation;
    float speed;
    int isKilled;
    ALLEGRO_COLOR color;
} Spaceship;

Spaceship createSpaceship();
Spaceship drawSpaceship(Spaceship*);
