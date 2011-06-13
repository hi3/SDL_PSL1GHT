/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2010 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

#include "SDL_PSL1GHTvideo.h"
#include <io/kb.h>
#include "keydata.h"

struct _keyboard
{
    uint32_t have;
    uint32_t check;

    KbMkey modifiers;
    KbLed leds;
    uint8_t state[PS3_MAX_KEYS];
} Keyboard;

extern void PSL1GHT_KEYBOARD_Process();

extern void PSL1GHT_PumpEvents(_THIS);
extern void PSL1GHT_InitSysEvent(_THIS);
extern void PSL1GHT_QuitSysEvent(_THIS);

/* vi: set ts=4 sw=4 expandtab: */
