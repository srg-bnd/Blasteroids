// Blast

#include <allegro5/allegro5.h>

typedef struct
{
    float screenX;
    float screenY;
    float orientation;
    float speed;
    int isDone;
    ALLEGRO_COLOR color;
} Blast;

Blast createBlast();
Blast drawBlast(Blast*);
