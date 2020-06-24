#include <stdio.h>
#include <stdlib.h>

/* XXX: For input */
#include <SDL2/SDL.h>

#include "render_manager.h"
#include "sound_manager.h"

void screen_ending(uint *state)
{
    int i = 0;
    int x = 0;
    int height = 0;
    int width = 0;
    char message[25];

    sound_mgr_bgm_play(BGM_TYPE_PRAYEROFHOPEN, /* loop: */ false);

    render_mgr_tileset_load(NULL, NULL);

    for (i = 0; i < 951; i++) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
        }

        render_mgr_clear();

        if (i < 360) {
            x = i / 60;
        } else {
            x = 5;
        }

        if (i > 365) {
            render_mgr_screen_render(SCREEN_TYPE_ENDING);
        }

        const tile_rect_t tile_rect = {
            .x = 600 + (64 * x),
            .y = 72,
            .width = 64,
            .height = 48
        };

        render_mgr_tileset_render(&tile_rect, 96, 72);

        render_mgr_display();
    }

    render_mgr_tileset_unload();

    *state = 0;
}
