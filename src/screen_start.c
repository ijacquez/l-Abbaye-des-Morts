#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* XXX: For input */
#include <SDL2/SDL.h>

#include "render_manager.h"
#include "sound_manager.h"

/* XXX: Remove! */
extern SDL_Window *screen;

void screen_start(uint *state, uint *fullscreen)
{
    uint exit = 0;

    SDL_Event keyp;

    render_type_t render_type = render_mgr_render_get();
    screen_type_t screen_type = SCREEN_TYPE_START;

    while (exit != 1) {
        /* Play music if required */
        if (!(sound_mgr_bgm_playing())) {
            sound_mgr_bgm_play(BGM_TYPE_MAINTITLEN, /* loop: */ true);
        }

        render_mgr_clear();

        /* Check keyboard */
        if (SDL_PollEvent(&keyp)) {
            if (keyp.type == SDL_KEYDOWN) { /* Key pressed */
                if (keyp.key.keysym.sym == SDLK_c) { /* Change graphic set */
                    render_mgr_style_next();
                }

                if (keyp.key.keysym.sym == SDLK_i) { /* Show instructions */
                    if (screen_type == SCREEN_TYPE_START) {
                        screen_type = SCREEN_TYPE_HELP;

                        sound_mgr_bgm_pause();
                    } else {
                        screen_type = SCREEN_TYPE_START;

                        sound_mgr_bgm_unpause();
                    }
                }

                if (keyp.key.keysym.sym == SDLK_f) { /* Switch fullscreen/windowed */
                    if (render_type == RENDER_TYPE_WINDOW) {
                        render_type = RENDER_TYPE_FULLSCREEN;
                    } else {
                        render_type = RENDER_TYPE_WINDOW;
                    }
                }

                if (keyp.key.keysym.sym == SDLK_SPACE) { /* Start game */
                    *state = 1;
                    exit = 1;
                }

                if (keyp.key.keysym.sym == SDLK_ESCAPE) { /* Exit game */
                    exit = 1;
                    *state = 6;
                }
            }
        }

        render_mgr_render_set(render_type);
        render_mgr_screen_render(screen_type);

        render_mgr_display();
    }
}
