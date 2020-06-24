#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "render_manager.h"
#include "sound_manager.h"

void screen_gameover(uint *state)
{
    render_mgr_clear();
    render_mgr_screen_render(SCREEN_TYPE_GAMEOVER);
    render_mgr_display();

    sound_mgr_bgm_play(BGM_TYPE_GAMEOVERV2N, /* loop: */ false);

    /* Wait */
    sleep(12);

    *state = 0;
}
