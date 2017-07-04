
#include "draw_disc_sector.h"
#include "u8g2.h"
#include <stdio.h>
#include <string.h>


#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH   256
#endif
#define DISPLAY_HIGHT   64

#if 0
#define POT_R           37
#define POT_WIDTH       5
#define POT_X0          (DISPLAY_WIDTH-POT_R)
#define POT_Y0          37

#else /* (testing) */

#define POT_R           29
#define POT_WIDTH       5
#define POT_X0          64
#define POT_Y0          32
#endif

/*--------------------------------------------------------------------------*/

u8g2_t u8g2;
int current_page;

/*--------------------------------------------------------------------------*/

void draw_scale_line(u8g2_t *p, int angel)
{
    u8g2_int_t x0, y0, x1, y1;

    x0 = (cos_512(angel) * (POT_R+1) + 255) / 512;
    y0 = (sin_512(angel) * (POT_R+1) + 255) / 512;
    x1 = (cos_512(angel) * (POT_R+2) + 255) / 512;
    y1 = (sin_512(angel) * (POT_R+2) + 255) / 512;
    u8g2_DrawLine(p, POT_X0 + x0, POT_Y0 + y0, POT_X0 + x1, POT_Y0 + y1);
}

void draw_scale_dot(u8g2_t *p, int angel)
{
    u8g2_int_t x1, y1;

    x1 = (cos_512(angel) * (POT_R+2) + 255) / 512;
    y1 = (sin_512(angel) * (POT_R+2) + 255) / 512;
    u8g2_DrawPixel(p, POT_X0 + x1, POT_Y0 + y1);
}

void draw_mydisc_sector(u8g2_t *p, int start, int stop)
{

//    draw_scale_line(p, start);
//    draw_scale_line(p, stop);
    draw_scale_dot(p, start );
    draw_scale_dot(p, stop);

    u8g2_DrawDisc_sector(p, POT_X0, POT_Y0, POT_R, start, stop);
}

/*--------------------------------------------------------------------------*/

int main (int argc, char * const argv[])
{
    (void) argc;
    int update = 1;
    int start = 0;
    int stop = 0;
    int k;

    u8g2_SetupBuffer_SDL_128x64_4(&u8g2, &u8g2_cb_r0);
    u8x8_InitDisplay(u8g2_GetU8x8(&u8g2));
    u8x8_SetPowerSave(u8g2_GetU8x8(&u8g2), 0);


    printf("%s: test disc sector \n", argv[0]);

    while (1) {

        if (update) {
            printf("start: %4d, stop: %4d\n", start, stop);

            u8g2_FirstPage(&u8g2);
            current_page = 0;
            do {

                draw_mydisc_sector(&u8g2, start, stop);

                current_page++;
            } while (u8g2_NextPage(&u8g2));
        }


        do {
            k = u8g_sdl_get_key();
        } while( k < 0 );

        if (k == 'q') break;

        update = 1;
        switch (k) {
            case 273: stop += 1;   break;
            case 274: stop -= 1;   break;
            case 275: stop += 10;  break;
            case 276: stop -= 10;  break;
            case 'k': start += 1;  break;
            case 'j': start -= 1;  break;
            case 'l': start += 10; break;
            case 'h': start -= 10; break;
            case 'x': stop = -180; break;
            default:
                update = 0;
                break;
            }
        if (stop >  360) stop = 360;
        if (stop <    0) stop = 0;
        if (start > 360) start = 360;
        if (start <   0) start = 0;
    }

    return 0;
}
