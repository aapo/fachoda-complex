// -*- c-basic-offset: 4; c-backslash-column: 79; indent-tabs-mode: nil -*-
// vim:sw=4 ts=4 sts=4 expandtab
/* Copyright 2012
 * This file is part of Fachoda.
 *
 * Fachoda is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fachoda is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fachoda.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include "file.h"
#include "proto.h"

struct kc gkeys[NBKEYS] = {
    { SDLK_BACKSPACE, "Quit" },
    { SDLK_y, "Yes" },
    { SDLK_n, "No" },

    { SDLK_w, "Motor +5%" },
    { SDLK_e, "Motor -5%" },

    { SDLK_r, "External views" },
    { SDLK_t, "Travelling view" },
    { SDLK_y, "Internal views" },
    { SDLK_F1, "Zoom out" }, // in external views
    { SDLK_F2, "Zoom in" },  // in external views
    { SDLK_o, "View next plane" },
    { SDLK_p, "View previous plane" },
    { SDLK_s, "View your plane or closest ennemy" },
    { SDLK_m, "View next bomb" },
    { SDLK_a, "Rise your head" },
    { SDLK_z, "Lower your head" },
    { SDLK_LEFT, "Turn left your head" },
    { SDLK_RIGHT, "Turn right your head" },
    { SDLK_d, "Look ahead" },
    { SDLK_x, "Look backward" },
    { SDLK_F3, "Look at left" }, //almost same than turn left
    { SDLK_F4, "Look at right" }, //almost same than turn right
    { SDLK_F5, "Look up" },  //almost same than turn up
    { SDLK_F6, "Look at the instrument panel" },

    { SDLK_g, "Gear" },
    { SDLK_f, "Flaps" },
    { SDLK_b, "Brakes" },
    { SDLK_h, "Autopilot" },
    { SDLK_c, "Buy a plane" },
    { SDLK_v, "Nose down" },
    { SDLK_n, "Nose up" },
    { SDLK_F4, "Roll left" },  //
    { SDLK_F6, "Roll right" }, //
    { SDLK_F6, "Center stick" }, //
    { SDLK_SPACE, "Fire" },
    { SDLK_j, "Change weapon" },

    { SDLK_q, "Pause" }, //
    { SDLK_F1, "See Highscores" }, //not so important
    { SDLK_F8, "Accelerated mode" }, //not so important
    { SDLK_F9, "Set navpoint to home base" }, //
    { SDLK_k, "Map mode" }, //
    { SDLK_F9, "Suicide" }, //not so important
    { SDLK_l, "Flag the map at plane's position" },//

    { SDLK_F8, "Emergency UP! (...?)" }, //
    { SDLK_F7, "Gun this plane (...?)" }//
};

static FILE *keyfile_open(char const *perms)
{
    return file_open_try(".fachoda-keys", getenv("HOME"), perms);
}

void keys_save(void)
{
    FILE *f = keyfile_open("w+");
    if (! f) return;

    for (unsigned i = 0; i < ARRAY_LEN(gkeys); i++) {
        ssize_t ret = fwrite(&gkeys[i].kc, sizeof(gkeys[i].kc), 1, f);
        if (ret < 1) {
            fprintf(stderr, "Cannot write key\n");
        }
    }

    fclose(f);
}

void keys_load(void)
{
    FILE *f = keyfile_open("r");
    if (! f) return;

    for (unsigned i = 0; i < ARRAY_LEN(gkeys); i++) {
        ssize_t ret = fread(&gkeys[i].kc, sizeof(gkeys[i].kc), 1, f);
        if (ret < 1) {
            fprintf(stderr, "Cannot read key\n");
        }
    }

    fclose(f);
}

