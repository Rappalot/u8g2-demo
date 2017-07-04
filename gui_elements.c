/*
 * (C) Copyright 2017 Leo C. <erbl259-lmu@yahoo.de>
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "gui_elements.h"
#include "draw_disc_sector.h"
#include "u8g2.h"

#ifndef DISPLAY_WIDTH
#define DISPLAY_WIDTH   256
#endif
#define DISPLAY_HIGHT   64

#if 1
#define POT_R           37
#define POT_WIDTH       5
#define POT_X0          (DISPLAY_WIDTH-POT_R)
#define POT_Y0          37

#else /* (testing) */

#define POT_R           30
#define POT_WIDTH       5
#define POT_X0          64
#define POT_Y0          32
#endif

#define POT_MSG_FONT    u8g2_font_crox5t_tr     //u8g2_font_timR18_tf


void draw_pot(u8g2_t *p, uint_fast8_t val, char *text)
{
    unsigned v = (val * 270) / 255;

    u8g2_DrawDisc_sector(p, POT_X0, POT_Y0, POT_R, 135, 135 + v);
    u8g2_DrawCircle(p, POT_X0, POT_Y0, POT_R-(POT_WIDTH/2), U8G2_DRAW_ALL);
    uint_fast8_t dc = p->draw_color;
    u8g2_SetDrawColor(p, dc ? 0 : 1);        // complement draw color
    u8g2_DrawDisc(p, POT_X0, POT_Y0, POT_R-POT_WIDTH, U8G2_DRAW_ALL);
    u8g2_SetDrawColor(p, dc);        // set draw color to old value

    u8g2_SetFont(p, POT_MSG_FONT);
    u8g2_SetFontPosCenter(p);
    int xpos = u8g2_GetStrWidth(p, text)/2;
    u8g2_DrawStr(p, POT_X0 - xpos, POT_Y0, text);
}
