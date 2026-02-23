// Blast

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include "../config.h"
#include "blast.h"

static int speedBlast(Blast*, float);

Blast* createBlast(Spaceship* spaceship)
{
    Blast* blast = malloc(sizeof(Blast));

    blast->isDone = false;
    blast->color = al_color_name("grey");

    blast->screenX = spaceship->screenX;
    blast->screenY = spaceship->screenY;
    blast->orientation = spaceship->orientation;
    blast->speed = 20;

    return blast;
}

int drawBlast(Blast* blast)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, DEG_TO_RAD(blast->orientation));
    al_translate_transform(&transform, blast->screenX, blast->screenY);
    al_use_transform(&transform);

    al_draw_line(0, 0, 0, 10, blast->color, 3.0f);

    return 0;
}

int pushBlast(Blast* blast)
{
    speedBlast(blast, blast->speed * 1.0f/CONFIG_FPS);

    if (blast->screenX > CONFIG_SCREEN_WEIGHT || blast->screenX < 0 || blast->screenY < 0 || blast->screenY > CONFIG_SCREEN_HIGHT)
    {
        blast->isDone = true;
    }

    return 0;
}

// Helpers

static int speedBlast(Blast* blast, float speed)
{
    float deltaScreenX = 0.f;
    float deltaScreenY = 0.f;

    if (blast->orientation == 0.f)
    {
        deltaScreenY = -speed;
    }
    else if(blast->orientation == 90.f)
    {
        deltaScreenX = speed;
    }
    else if(blast->orientation == 180.f)
    {
        deltaScreenY = speed;
    }
    else if(blast->orientation == 270.f)
    {
        deltaScreenX = -speed;
    }
    else
    {
        if (blast->orientation > 0.f && blast->orientation < 90.f)
        {
            deltaScreenX = speed;
            deltaScreenY = -speed;
        }
        else if (blast->orientation > 90.f && blast->orientation < 180.f)
        {
            deltaScreenX = speed;
            deltaScreenY = speed;
        }
        else if (blast->orientation > 180.f && blast->orientation < 270.f)
        {
            deltaScreenX = -speed;
            deltaScreenY = speed;
        }
        else
        {
            deltaScreenX = -speed;
            deltaScreenY = -speed;
        }
    }

    blast->screenX += deltaScreenX;
    blast->screenY += deltaScreenY;

    return 0;
}
