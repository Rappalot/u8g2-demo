/*
 * Test for draw_pot()
 */

#include "u8g2.h"
#include "gui_elements.h"
#include <stdio.h>
#include <string.h>

int current_page;
u8g2_t u8g2;

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

    printf("%s: volume control test\n", argv[0]);

    while (1) {

        if (update) {
            printf("start: %4d, stop: %4d\n", start, stop);
            int vol = stop;
            if (vol > 255)
                vol = 255;

            char msg[8];
            sprintf(msg, "%ddB", (63 - 255 + vol)/2);

            u8g2_FirstPage(&u8g2);
            current_page = 0;
            do {
                draw_pot(&u8g2, vol, msg);
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
