#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* XXX: For input */
#include <SDL2/SDL.h>
/* XXX: Lack of sprite support */
#include <SDL2/SDL_image.h>

#include "render_manager.h"
#include "sound_manager.h"

/* XXX: Remove! */
extern SDL_Renderer *renderer;

void screen_history(uint *state)
{
    SDL_Event keyp;

    /* Loading PNG */
    SDL_Texture *tiles = IMG_LoadTexture(renderer, "graphics/tiles.png");

    SDL_Rect srcjean = {384, 88, 16, 24};
    SDL_Rect desjean = {0, 100, 16, 24};
    SDL_Rect srcenem = {96, 64, 16, 24};
    SDL_Rect desenem = {0, 100, 16, 24};

    uint exit = 0;
    float posjean = -16;
    float posenem[4] = {-17, -17, -17, -17};
    uint animation = 0;
    uint i = 0;
    uint musicload = 0;

    render_type_t render_type = render_mgr_render_get();

    while (exit != 1) {
        render_mgr_clear();

        /* Play music at start */
        if (musicload == 0) {
            musicload = 1;
            sound_mgr_bgm_play(BGM_TYPE_MANHUNTN, /* loop: */ false);
        }

        render_mgr_screen_render(SCREEN_TYPE_HISTORY);

        /* XXX: Change this */
        int changetiles = render_mgr_style_get();

        /* Animation control */
        if (animation < 13) {
            animation ++;
        } else {
            animation = 0;
        }

        /* Jean running */
        if (posjean < 257) {
            posjean += 0.75;
            desjean.x = posjean;
            srcjean.x = 384 + ((animation / 7) * 16); /* Walking animation */
            srcjean.y = 88 + (changetiles * 120); /* 8 or 16 bits sprite */
            SDL_RenderCopy(renderer, tiles, &srcjean, &desjean);
        }

        /* Crusaders running */
        /* When start running */
        for (i = 0; i < 4; i++) {
            if (posjean > (35 + (30 * i))) {
                posenem[i] += 0.65;
            }
        }

        /* Draw */
        for (i = 0; i < 4; i++) {
            if ((posenem[i] > -17) && (posenem[i] < 257)) {
                desenem.x = posenem[i];
                srcenem.x = 96 + ((animation / 7) * 16);
                srcenem.y = 64 + (changetiles * 120);
                SDL_RenderCopy(renderer, tiles, &srcenem, &desenem);
            }
        }

        /* Check keyboard */
        if ( SDL_PollEvent(&keyp) ) {
            if (keyp.type == SDL_KEYDOWN) { /* Key pressed */
                if (keyp.key.keysym.sym == SDLK_c) { /* Change graphic set */
                    render_mgr_style_next();
                }

                if (keyp.key.keysym.sym == SDLK_f) { /* Switch fullscreen/windowed */
                    if (render_type == RENDER_TYPE_WINDOW) {
                        render_type = RENDER_TYPE_FULLSCREEN;
                    } else {
                        render_type = RENDER_TYPE_WINDOW;
                    }
                }

                if (keyp.key.keysym.sym == SDLK_SPACE) { /* Start game */
                    *state = 2;
                    exit = 1;
                }

                if (keyp.key.keysym.sym == SDLK_ESCAPE) { /* Exit game */
                    exit = 1;
                    *state = 6;
                }
            }
        }

        if (posenem[3] > 256) { /* Ending history */
            exit = 1;
            *state = 2;
        }

        render_mgr_render_set(render_type);

        render_mgr_display();
    }

    /* Cleaning */
    SDL_DestroyTexture(tiles);
}
