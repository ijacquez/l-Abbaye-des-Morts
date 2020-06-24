/*-
 * Abbaye des Morts, version 2.0
 *
 * Copyright (c) 2010 Locomalito & Gryzor87
 * Copyright (C) 2013 David "Nevat" Lara
 * Copyright (c) 2020 Israel Jacquez
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include "render_manager.h"
#include "sound_manager.h"

void screen_ending(uint *state);
void screen_game(uint *state);
void screen_gameover(uint *state);
void screen_history(uint *state);
void screen_start(uint *state);

int main (int argc, char **argv)

{
    uint exit = 0;
    uint state = 0;

    render_mgr_init();
    sound_mgr_init();

    render_mgr_render_set(RENDER_TYPE_WINDOW);

    while (exit != 1) {
        switch (state) {
        case 0:
            screen_start(&state);
            break;

        case 1:
            screen_history(&state);
            break;

        case 2:
            screen_game(&state);
            break;

        case 3:
            screen_gameover(&state);
            break;

        case 4:
            screen_ending(&state);
            break;

        case 6:
            exit = 1;
            break;
        }
    }

    render_mgr_deinit();

    return 0;
}

int WinMain(void)
{
    main(0, NULL);
}
