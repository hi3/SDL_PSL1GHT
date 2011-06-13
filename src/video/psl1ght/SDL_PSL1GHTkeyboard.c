/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2009 Sam Lantinga

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

#include "SDL_PSL1GHTevents_c.h"
#include "../../events/SDL_events_c.h"
#include <io/kb.h>

/* Data */
#define PS3_MAX_MODS		8
#define KB_STATUS_CONNECTED	1

/* Debugging
 * 0: No debug messages
 * 1: Video debug messages
 * 2: SPE debug messages
 * 3: Memory adresses
 */
#define KEYBOARD_DEBUG_LEVEL 0

#ifdef KEYBOARD_DEBUG_LEVEL
#define deprintf( level, fmt, args... ) \
    do \
{ \
    if ( (unsigned)(level) <= KEYBOARD_DEBUG_LEVEL ) \
    { \
        fprintf( stdout, fmt, ##args ); \
        fflush( stdout ); \
    } \
} while ( 0 )
#else
#define deprintf( level, fmt, args... )
#endif

/* Map PS3 modifier keys to SDL modifier keys */
static const SDLKey ModifierMap[PS3_MAX_MODS] = {SDLK_LCTRL, SDLK_LSHIFT, SDLK_LALT, SDLK_LSUPER, SDLK_RCTRL, SDLK_RSHIFT, SDLK_RALT, SDLK_RSUPER};

/* Helpers */
static void
CheckKeyboard ()
{
    if(60 < Keyboard.check ++)
    {
        KbInfo KeyboardInfo;
        ioKbGetInfo(&KeyboardInfo);

        if(!Keyboard.have && (KeyboardInfo.status[0] == KB_STATUS_CONNECTED))
        {
            Keyboard.have = 1;

            ioKbSetReadMode(0, KB_RMODE_PACKET);
            ioKbSetCodeType(0, KB_CODETYPE_RAW);
            ioKbClearBuf(0);

            Keyboard.modifiers._KbMkeyU.mkeys = 0;
            memset(Keyboard.state, 0, sizeof(Keyboard.state));
        }
        else if(Keyboard.have && KeyboardInfo.status[0] != KB_STATUS_CONNECTED)
        {
            Keyboard.have = 0;
            SDL_ResetKeyboard();
        }

        Keyboard.check = 0;
    }
}

static void
ProcessModifiers (KbMkey newkey, KbMkey oldkey)
{
    int i = 0;
    if(newkey._KbMkeyU.mkeys != oldkey._KbMkeyU.mkeys)
    {
        for(i = 0; i != PS3_MAX_MODS; i++)
        {
            if((newkey._KbMkeyU.mkeys & (1 << i)) != (oldkey._KbMkeyU.mkeys & (1 << i)))
            {
                PSL1GHT_DoModifierEvent(ModifierMap[i], (newkey._KbMkeyU.mkeys & (1 << i)) ? SDL_PRESSED : SDL_RELEASED);
            }
        }
    }
}

static void
ProcessKeys (uint32_t length, uint16_t* data)
{
    int i = 0;
    /* Only process if the list has data, and the list isn't rollover (too many keys pressed at once) */
    if(length && data[0] != 1)
    {
        Uint8 curstate[PS3_MAX_KEYS];
        memset(curstate, 0, PS3_MAX_KEYS);

        /* Get list of keys down, data[0] == 0 means all keys are released */
        if(data[0] > 1)
        {
            for(i = 0; i != length; i ++)
            {
                if(data[i] < PS3_MAX_KEYS)
                {
                    curstate[data[i]] = data[i];
                }
            }
        }

        /* Send pressed, all downs first, then all ups */
        for(i = 0; i != PS3_MAX_KEYS; i ++)
        {
            if(curstate[i] != Keyboard.state[i] && curstate[i] != 0)
            {
                PSL1GHT_DoKeyEvent((enum HID_ID)i, SDL_PRESSED, Keyboard.modifiers, Keyboard.leds);
            }
        }

        for(i = 0; i != PS3_MAX_KEYS; i ++)
        {
            if(curstate[i] != Keyboard.state[i] && curstate[i] == 0)
            {
                PSL1GHT_DoKeyEvent((enum HID_ID)i, SDL_RELEASED, Keyboard.modifiers, Keyboard.leds);
            }
        }

        memcpy(Keyboard.state, curstate, PS3_MAX_KEYS);
    }
}

/* Implementation */
void
PSL1GHT_KEYBOARD_Process ()
{
    CheckKeyboard();

    KbData data;
    if(Keyboard.have && 0 == ioKbRead(0, &data) && data.nb_keycode)
    {
        ProcessModifiers(data.mkey, Keyboard.modifiers);
        Keyboard.modifiers = data.mkey;
        Keyboard.leds = data.led;
        ProcessKeys(data.nb_keycode, data.keycode);
    }
}

