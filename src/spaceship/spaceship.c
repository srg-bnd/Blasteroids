// Spaceship

#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include "../config.h"
#include "spaceship.h"
#include "../blast/blast.h"

const float STD_ROTATE_DEG = 30.f;

static int rotateSpaceship(Spaceship*, float );
static int speedSpaceship(Spaceship*, float);

Spaceship* createSpaceship()
{
    Spaceship* spaceship = malloc(sizeof(Spaceship));
    spaceship->isKilled = false;
    spaceship->screenX = CONFIG_SCREEN_HIGHT / 2;
    spaceship->screenY = CONFIG_SCREEN_WEIGHT / 2;
    spaceship->speed = 10;
    spaceship->orientation = 0;
    spaceship->color = al_map_rgb_f(0.5, 0.5, 0.5);
    spaceship->lives = 0;

    return spaceship;
}

int drawSpaceship(Spaceship* spaceship)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_rotate_transform(&transform, DEG_TO_RAD(spaceship->orientation));
    al_translate_transform(&transform, spaceship->screenX, spaceship->screenY);
    al_use_transform(&transform);

    al_draw_line(-8, 9, 0, -11, spaceship->color, 3.0f);
    al_draw_line(0, -11, 8, 9, spaceship->color, 3.0f);
    al_draw_line(-6, 4, -1, 4, spaceship->color, 3.0f);
    al_draw_line(6, 4, 1, 4, spaceship->color, 3.0f);

    return 0;
}

int upSpaceship(Spaceship* spaceship)
{
    return speedSpaceship(spaceship, spaceship->speed);
}

int downSpaceship(Spaceship* spaceship)
{
    return speedSpaceship(spaceship, -spaceship->speed);
}

int leftSpaceship(Spaceship* spaceship)
{
    return rotateSpaceship(spaceship, -STD_ROTATE_DEG);
}

int rightSpaceship(Spaceship* spaceship)
{
    return rotateSpaceship(spaceship, STD_ROTATE_DEG);
}

// Blast

int blastSpaceship(Spaceship* spaceship)
{
    BlastNode* blastNode = malloc(sizeof(BlastNode));

    blastNode->blast = createBlast(spaceship);

    if (spaceship->headBlastList == NULL)
    {
        spaceship->headBlastList = blastNode;
        spaceship->lastBlastList = blastNode;
    }
    else
    {
        spaceship->lastBlastList->prev = spaceship->lastBlastList;
        spaceship->lastBlastList->next = blastNode;
        spaceship->lastBlastList = blastNode;
    }

    return 0;
}

int pushBlasts(Spaceship* spaceship)
{
    BlastNode* currentBlastNode = spaceship->headBlastList;

    while (currentBlastNode != NULL)
    {
        if (currentBlastNode->blast->isDone)
        {
            if (currentBlastNode->prev != NULL)
            {
                currentBlastNode->prev = currentBlastNode->next;
            }
            else
            {
                spaceship->headBlastList = currentBlastNode->next;
            }

            BlastNode* doneBlastNode = currentBlastNode;
            currentBlastNode = currentBlastNode->next;

            // if (doneBlastNode->blast != NULL) free(doneBlastNode->blast);
            // if (doneBlastNode != NULL) free(doneBlastNode);
        }
        else
        {
            pushBlast(currentBlastNode->blast);
            currentBlastNode = currentBlastNode->next;
        }
    }

    return 0;
}

int drawBlasts(Spaceship* spaceship)
{
    BlastNode* currentBlastNode = spaceship->headBlastList;

    while (currentBlastNode != NULL)
    {
        drawBlast(currentBlastNode->blast);
        currentBlastNode = currentBlastNode->next;
    }

    return 0;
}

// Helpers

static int speedSpaceship(Spaceship* spaceship, float speed)
{
    float deltaScreenX = 0.f;
    float deltaScreenY = 0.f;

    if (spaceship->orientation == 0.f)
    {
        deltaScreenY = -speed;
    }
    else if(spaceship->orientation == 90.f)
    {
        deltaScreenX = speed;
    }
    else if(spaceship->orientation == 180.f)
    {
        deltaScreenY = speed;
    }
    else if(spaceship->orientation == 270.f)
    {
        deltaScreenX = -speed;
    }
    else
    {
        if (spaceship->orientation > 0.f && spaceship->orientation < 90.f)
        {
            deltaScreenX = speed;
            deltaScreenY = -speed;
        }
        else if (spaceship->orientation > 90.f && spaceship->orientation < 180.f)
        {
            deltaScreenX = speed;
            deltaScreenY = speed;
        }
        else if (spaceship->orientation > 180.f && spaceship->orientation < 270.f)
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

    spaceship->screenX += deltaScreenX;
    spaceship->screenY += deltaScreenY;

    return 0;
}

static int rotateSpaceship(Spaceship* spaceship, float deg)
{
    spaceship->orientation += deg;

    if (spaceship->orientation >= 360)
    {
        spaceship->orientation -= 360;
    }
    else if (spaceship->orientation < 0) {
        spaceship->orientation += 360;
    }

    return 0;
}
