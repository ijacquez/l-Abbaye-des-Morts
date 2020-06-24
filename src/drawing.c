#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

#include "render_manager.h"
#include "sound_manager.h"

void drawscreen(uint stagedata[][22][32], uint room[], uint counter[])
{
    tile_rect_t tile_rect = {
        .x = 0,
        .y = 0,
        .width = 8,
        .height = 8
    };

    uint32_t out_x = 0;
    uint32_t out_y = 0;

    for (uint32_t coordy = 0; coordy <= 21; coordy++) {
        for (uint32_t coordx = 0; coordx <= 31; coordx++) {
            uint data = stagedata[room[0]][coordy][coordx];

            if ((data > 0) && (data != 99)) {
                out_x = coordx * 8;
                out_y = coordy * 8;

                if (data < 200) {
                    tile_rect.width = 8;
                    tile_rect.height = 8;

                    if (data < 101) {
                        tile_rect.y = 0;

                        if (data == 84) { /* Cross brightness */
                            tile_rect.x = (data - 1) * 8 + (counter[0] / 8 * 8);
                        } else {
                            tile_rect.x = (data - 1) * 8;
                        }
                    } else {
                        if (data == 154) {
                            tile_rect.x = 600 + ((counter[0] / 8) * 16);
                            tile_rect.y = 0;
                            tile_rect.width = 16;
                            tile_rect.height = 24;
                        } else {
                            tile_rect.y = 8;
                            tile_rect.x = (data - 101) * 8;
                        }
                    }
                }

                if ((data > 199) && (data < 300)) {
                    tile_rect.x = (data - 201) * 48;
                    tile_rect.y = 16;
                    tile_rect.width = 48;
                    tile_rect.height = 48;
                }

                if ((data > 299) && (data < 399)) {
                    tile_rect.x = 96 + ((data - 301) * 8);
                    tile_rect.y = 16;
                    tile_rect.width = 8;
                    tile_rect.height = 8;

                    /* Door movement */
                    if ((room[0] == 7) && ((counter[1] > 59) && (counter[1] < 71))) {
                        if ((data == 347) || (data == 348) || (data == 349) || (data == 350)) {
                            out_x += 2;

                            if ((data == 350) && (counter[1] == 70)) {
                                sound_mgr_sfx_play(SFX_TYPE_DOOR_SFX_HANDLES);
                            }
                        }
                    }
                }

                /* Hearts */
                if ((data > 399) && (data < 405)) {
                    tile_rect.x = 96 + ((data - 401) * 8) + (32 * (counter[0] / 15));
                    tile_rect.y = 24;
                    tile_rect.width = 8;
                    tile_rect.height = 8;
                }

                /* Crosses */
                if ((data > 408) && (data < 429)) {
                    tile_rect.x = 96 + ((data - 401) * 8) + (32 * (counter[1] / 23));
                    tile_rect.y = 24;
                    tile_rect.width = 8;
                    tile_rect.height = 8;
                }

                if ((data > 499) && (data < 599)) {
                    tile_rect.x = 96 + ((data - 501) * 8);
                    tile_rect.y = 32;
                    tile_rect.width = 8;
                    tile_rect.height = 8;
                }

                if ((data > 599) && (data < 650)) {
                    tile_rect.x = 96 + ((data - 601) * 8);
                    tile_rect.y = 56;
                    tile_rect.width = 8;
                    tile_rect.height = 8;
                }

                if (data == 650) { /* Cup */
                    tile_rect.x = 584;
                    tile_rect.y = 87;
                    tile_rect.width = 16;
                    tile_rect.height = 16;
                }

                render_mgr_tileset_render(&tile_rect, out_x, out_y);
            }
        }
    }
}

void statusbar(int room[], int lifes, int crosses)
{
    int i = 0;

    const tile_rect_t heart_tile_rect = {
        .x = 448,
        .y = 104,
        .width = 13,
        .height = 12
    };

    const tile_rect_t cross_tile_rect = {
        .x = 461,
        .y = 104,
        .width = 12,
        .height = 12
    };

    render_mgr_tileset_render(&heart_tile_rect, 0, 177);
    render_mgr_tileset_render(&cross_tile_rect, 32, 177);

    title_type_t title_type;

    for (i = 0; i <= 2; i++) {
        switch (i) {
        case 0:
            render_mgr_font_number_render(lifes, 18, 178);
            break;

        case 1:
            render_mgr_font_number_render(crosses, 50, 178);
            break;

        case 2:
            if (room[0] > 0) {
                if (room[0] < 4) {
                    title_type = (room[0] - 1);
                } else if (room[0] > 4) {
                    title_type = (room[0] - 2);
                }

                render_mgr_font_title_render(title_type);
            }

            break;
        }
    }
}

void showparchment(uint parchment)
{
    switch (parchment) {
    case 3:
        render_mgr_screen_render(SCREEN_TYPE_PARCHMENT_1);
        break;

    case 8:
        render_mgr_screen_render(SCREEN_TYPE_PARCHMENT_2);
        break;

    case 12:
        render_mgr_screen_render(SCREEN_TYPE_PARCHMENT_3);
        break;

    case 14:
        render_mgr_screen_render(SCREEN_TYPE_PARCHMENT_4);
        break;

    case 16:
        render_mgr_screen_render(SCREEN_TYPE_PARCHMENT_5);
        break;

    case 21:
        render_mgr_screen_render(SCREEN_TYPE_PARCHMENT_6);
        break;
    }
}

void redparchment(struct hero *jean)
{
    render_mgr_screen_render(SCREEN_TYPE_PARCHMENT_RED);

    jean->flags[6] = 4;
}

void blueparchment(struct hero *jean)
{
    render_mgr_screen_render(SCREEN_TYPE_PARCHMENT_BLUE);
}
