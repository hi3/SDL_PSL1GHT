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
#include <SDL.h>
#include "SDL_keyboard.h"
#include <io/kb.h>
#include "../../events/SDL_events_c.h"
#include "keydata.h"

/* Data */
static const PSL1GHT_Key PSL1GHT_KeyMap[] = 
{
/*  NAME                      SDLK               MODIFIER  HIDID               SCANCODE */
    {"No Event",              SDLK_UNKNOWN,      0,        HID_NOEVENT,        0},
    {"Overrun Error",         SDLK_UNKNOWN,      0,        HID_OVERRUN,        0},
    {"POST Fail",             SDLK_UNKNOWN,      0,        HID_POSTFAIL,       0},
    {"Error Undefined",       SDLK_UNKNOWN,      0,        HID_UNDEFINEDERROR, 0},
    {"aA",                    SDLK_a,            0,        HID_a,              0},
    {"bB",                    SDLK_b,            0,        HID_b,              0},
    {"cC",                    SDLK_c,            0,        HID_c,              0},
    {"dD",                    SDLK_d,            0,        HID_d,              0},
    {"eE",                    SDLK_e,            0,        HID_e,              0},
    {"fF",                    SDLK_f,            0,        HID_f,              0},
    {"gG",                    SDLK_g,            0,        HID_g,              0},
    {"hH",                    SDLK_h,            0,        HID_h,              0},
    {"iI",                    SDLK_i,            0,        HID_i,              0},
    {"jJ",                    SDLK_j,            0,        HID_j,              0},
    {"kK",                    SDLK_k,            0,        HID_k,              0},
    {"lL",                    SDLK_l,            0,        HID_l,              0},
    {"mM",                    SDLK_m,            0,        HID_m,              0},
    {"nN",                    SDLK_n,            0,        HID_n,              0},
    {"oO",                    SDLK_o,            0,        HID_o,              0},
    {"pP",                    SDLK_p,            0,        HID_p,              0},
    {"qQ",                    SDLK_q,            0,        HID_q,              0},
    {"rR",                    SDLK_r,            0,        HID_r,              0},
    {"sS",                    SDLK_s,            0,        HID_s,              0},
    {"tT",                    SDLK_t,            0,        HID_t,              0},
    {"uU",                    SDLK_u,            0,        HID_u,              0},
    {"vV",                    SDLK_v,            0,        HID_v,              0},
    {"wW",                    SDLK_w,            0,        HID_w,              0},
    {"xX",                    SDLK_x,            0,        HID_x,              0},
    {"yY",                    SDLK_y,            0,        HID_y,              0},
    {"zZ",                    SDLK_z,            0,        HID_z,              0},
    {"1!",                    SDLK_1,            0,        HID_1,              0},
    {"2@",                    SDLK_2,            0,        HID_2,              0},
    {"3#",                    SDLK_3,            0,        HID_3,              0},
    {"4$",                    SDLK_4,            0,        HID_4,              0},
    {"5%",                    SDLK_5,            0,        HID_5,              0},
    {"6^",                    SDLK_6,            0,        HID_6,              0},
    {"7&",                    SDLK_7,            0,        HID_7,              0},
    {"8*",                    SDLK_8,            0,        HID_8,              0},
    {"9(",                    SDLK_9,            0,        HID_9,              0},
    {"0)",                    SDLK_0,            0,        HID_0,              0},
    {"Return",                SDLK_RETURN,       0,        HID_RETURN,         0},
    {"Escape",                SDLK_ESCAPE,       0,        HID_ESCAPE,         0},
    {"Backspace",             SDLK_BACKSPACE,    0,        HID_BACKSPACE,      0},
    {"Tab",                   SDLK_TAB,          0,        HID_TAB,            0},
    {"Space",                 SDLK_SPACE,        0,        HID_SPACE,          0},
    {"-_",                    SDLK_MINUS,        0,        HID_MINUS,          0},
    {"=+",                    SDLK_PLUS,         0,        HID_PLUS,           0},
    {"[{",                    SDLK_LEFTBRACKET,  0,        HID_LEFTBRACKET,    0},
    {"]}",                    SDLK_RIGHTBRACKET, 0,        HID_RIGHTBRACKET,   0},
    {"\\|",                   SDLK_BACKSLASH,    0,        HID_BACKSLASH,      0},
    {"Europe 1 (Note 2)",     SDLK_UNKNOWN,      0,        HID_EUROPE1_,       0},
    {";:",                    SDLK_SEMICOLON,    0,        HID_SEMICOLON,      0},
    {"'\"",                   SDLK_QUOTE,        0,        HID_QUOTE,          0},
    {"`~",                    SDLK_BACKQUOTE,    0,        HID_BACKQUOTE,      0},
    {",<",                    SDLK_COMMA,        0,        HID_COMMA,          0},
    {".>",                    SDLK_PERIOD,       0,        HID_PERIOD,         0},
    {"/?",                    SDLK_SLASH,        0,        HID_SLASH,          0},
    {"Caps Lock",             SDLK_CAPSLOCK,     0,        HID_CAPSLOCK,       0},
    {"F1",                    SDLK_F1,           0,        HID_F1,             0},
    {"F2",                    SDLK_F2,           0,        HID_F2,             0},
    {"F3",                    SDLK_F3,           0,        HID_F3,             0},
    {"F4",                    SDLK_F4,           0,        HID_F4,             0},
    {"F5",                    SDLK_F5,           0,        HID_F5,             0},
    {"F6",                    SDLK_F6,           0,        HID_F6,             0},
    {"F7",                    SDLK_F7,           0,        HID_F7,             0},
    {"F8",                    SDLK_F8,           0,        HID_F8,             0},
    {"F9",                    SDLK_F9,           0,        HID_F9,             0},
    {"F10",                   SDLK_F10,          0,        HID_F10,            0},
    {"F11",                   SDLK_F11,          0,        HID_F11,            0},
    {"F12",                   SDLK_F12,          0,        HID_F12,            0},
    {"Print Screen (Note 1)", SDLK_PRINT,        0,        HID_PRINT,          0},
    {"Scroll Lock",           SDLK_SCROLLOCK,    0,        HID_SCROLLOCK,      0},
    {"Pause",                 SDLK_PAUSE,        0,        HID_PAUSE,          0},
    {"Insert (Note 1)",       SDLK_INSERT,       0,        HID_INSERT,         0},
    {"Home (Note 1)",         SDLK_HOME,         0,        HID_HOME,           0},
    {"Page Up (Note 1)",      SDLK_PAGEUP,       0,        HID_PAGEUP,         0},
    {"Delete (Note 1)",       SDLK_DELETE,       0,        HID_DELETE,         0},
    {"End (Note 1)",          SDLK_END,          0,        HID_END,            0},
    {"Page Down (Note 1)",    SDLK_PAGEDOWN,     0,        HID_PAGEDOWN,       0},
    {"Right Arrow (Note 1)",  SDLK_RIGHT,        0,        HID_RIGHT,          0},
    {"Left Arrow (Note 1)",   SDLK_LEFT,         0,        HID_LEFT,           0},
    {"Down Arrow (Note 1)",   SDLK_DOWN,         0,        HID_DOWN,           0},
    {"Up Arrow (Note 1)",     SDLK_UP,           0,        HID_UP,             0},
    {"Num Lock",              SDLK_NUMLOCK,      0,        HID_NUMLOCK,        0},
    {"Keypad / (Note 1)",     SDLK_KP_DIVIDE,    0,        HID_KP_DIVIDE,      0},
    {"Keypad *",              SDLK_KP_MULTIPLY,  0,        HID_KP_MULTIPLY,    0},
    {"Keypad -",              SDLK_KP_MINUS,     0,        HID_KP_MINUS,       0},
    {"Keypad +",              SDLK_KP_PLUS,      0,        HID_KP_PLUS,        0},
    {"Keypad Enter",          SDLK_KP_ENTER,     0,        HID_KP_ENTER,       0},
    {"Keypad 1 End",          SDLK_KP1,          0,        HID_KP1,            0},
    {"Keypad 2 Down",         SDLK_KP2,          0,        HID_KP2,            0},
    {"Keypad 3 PageDn",       SDLK_KP3,          0,        HID_KP3,            0},
    {"Keypad 4 Left",         SDLK_KP4,          0,        HID_KP4,            0},
    {"Keypad 5",              SDLK_KP5,          0,        HID_KP5,            0},
    {"Keypad 6 Right",        SDLK_KP6,          0,        HID_KP6,            0},
    {"Keypad 7 Home",         SDLK_KP7,          0,        HID_KP7,            0},
    {"Keypad 8 Up",           SDLK_KP8,          0,        HID_KP8,            0},
    {"Keypad 9 PageUp",       SDLK_KP9,          0,        HID_KP9,            0},
    {"Keypad 0 Insert",       SDLK_KP0,          0,        HID_KP0,            0},
    {"Keypad . Delete",       SDLK_KP_PERIOD,    0,        HID_KP_PERIOD,      0},
    {"Europe 2 (Note 2)",     SDLK_UNKNOWN,      0,        HID_EUROPE2_,       0},
    {"App",                   SDLK_UNKNOWN,      0,        HID_APP,            0},
    {"Keyboard Power",        SDLK_UNKNOWN,      0,        HID_KEYBOARDPOWER,  0},
    {"Keypad =",              SDLK_KP_EQUALS,    0,        HID_KP_EQUALS,      0},
    {"F13",                   SDLK_F13,          0,        HID_F13,            0},
    {"F14",                   SDLK_F14,          0,        HID_F14,            0},
    {"F15",                   SDLK_F15,          0,        HID_F15,            0},
    {"F16",                   SDLK_UNKNOWN,      0,        HID_F16_,           0},
    {"F17",                   SDLK_UNKNOWN,      0,        HID_F17_,           0},
    {"F18",                   SDLK_UNKNOWN,      0,        HID_F18_,           0},
    {"F19",                   SDLK_UNKNOWN,      0,        HID_F19_,           0},
    {"F20",                   SDLK_UNKNOWN,      0,        HID_F20_,           0},
    {"F21",                   SDLK_UNKNOWN,      0,        HID_F21_,           0},
    {"F22",                   SDLK_UNKNOWN,      0,        HID_F22_,           0},
    {"F23",                   SDLK_UNKNOWN,      0,        HID_F23_,           0},
    {"F24",                   SDLK_UNKNOWN,      0,        HID_F24_,           0},
    {"Keyboard Execute",      SDLK_UNKNOWN,      0,        HID_EXECUTE_,       0},
    {"Keyboard Help",         SDLK_HELP,         0,        HID_HELP,           0},
    {"Keyboard Menu",         SDLK_MENU,         0,        HID_MENU,           0},
    {"Keyboard Select",       SDLK_UNKNOWN,      0,        HID_SELECT_,        0},
    {"Keyboard Stop",         SDLK_UNKNOWN,      0,        HID_STOP_,          0},
    {"Keyboard Again",        SDLK_UNKNOWN,      0,        HID_AGAIN_,         0},
    {"Keyboard Undo",         SDLK_UNKNOWN,      0,        HID_UNDO_,          0},
    {"Keyboard Cut",          SDLK_UNKNOWN,      0,        HID_CUT_,           0},
    {"Keyboard Copy",         SDLK_UNKNOWN,      0,        HID_COPY_,          0},
    {"Keyboard Paste",        SDLK_UNKNOWN,      0,        HID_PASTE_,         0},
    {"Keyboard Find",         SDLK_UNKNOWN,      0,        HID_FIND_,          0},
    {"Keyboard Mute",         SDLK_UNKNOWN,      0,        HID_MUTE_,          0},
    {"Keyboard Volume Up",    SDLK_UNKNOWN,      0,        HID_VOLUP_,         0},
    {"Keyboard Volume Dn",    SDLK_UNKNOWN,      0,        HID_VOLDN_,         0},
    {"Keyboard Locking",      SDLK_UNKNOWN,      0,        HID_CAPSLOCK_,      0},
    {"Caps Lock",             SDLK_UNKNOWN,      0,        HID_CAPSLOCK_,      0},
    {"Keyboard Locking",      SDLK_UNKNOWN,      0,        HID_NUMLOCK_,       0},
    {"Num Lock",              SDLK_UNKNOWN,      0,        HID_NUMLOCK_,       0},
    {"Keyboard Locking",      SDLK_UNKNOWN,      0,        HID_SCROLLOCK_,     0},
    {"Scroll Lock",           SDLK_UNKNOWN,      0,        HID_SCROLLOCK_,     0},
    {"Keypad ,",              SDLK_UNKNOWN,      0,        HID_NOEVENT,        0},
    {"(Brazilian Keypad .)",  SDLK_UNKNOWN,      0,        HID_NOEVENT,        0},
    {"Keyboard Equal Sign",   SDLK_UNKNOWN,      0,        HID_NOEVENT,        0},
    {"Keyboard Int'l 1",      SDLK_UNKNOWN,      0,        HID_NOEVENT,        0},
};

#define TOTAL_KEYS (sizeof(PSL1GHT_KeyMap) / sizeof(PSL1GHT_KeyMap[0]))

//static uint32_t MouseEventMap[3];

/* Helpers */
static void
FillKeysym (SDL_keysym* keysym, SDLKey key, uint32_t scancode)
{
    memset(keysym, 0, sizeof(SDL_keysym));
    keysym->scancode = scancode;
    keysym->sym = key;
}

/* Implementation */
const PSL1GHT_Key*
PSL1GHT_GetKeyFromHID (enum HID_ID hid)
{
    if(hid < TOTAL_KEYS)
    {
        return &PSL1GHT_KeyMap[hid];
    }

    return &PSL1GHT_KeyMap[0];
}

const PSL1GHT_Key*
PSL1GHT_GetKeyFromSDLK (SDLKey key)
{
    int i = 0;
    for(i = 0; i != TOTAL_KEYS; i ++)
    {
        if(PSL1GHT_KeyMap[i].symbol == key)
        {
            return &PSL1GHT_KeyMap[i];
        }
    }

    return &PSL1GHT_KeyMap[0];
}

void
PSL1GHT_DoKeyEvent (enum HID_ID hid, uint32_t state, KbMkey ps3key, KbLed ps3led)
//PSL1GHT_DoKeyEvent (enum HID_ID hid, uint32_t state, uint32_t ps3key, uint32_t ps3led)
{
    //int SDL_TranslateUNICODE = 0;
    const PSL1GHT_Key* key = PSL1GHT_GetKeyFromHID(hid);
/*
    SDL_keysym sym;
    FillKeysym(&sym, key->symbol, key->scancode);

    if(SDL_TranslateUNICODE)
    {
        sym.unicode = ioKbCnvRawCode(KB_MAPPING_101, ps3key, ps3led, key->HIDID);
    }
*/
    SDL_SendKeyboardKey(state, key->scancode);
}

void
PSL1GHT_DoKeyEventSDLK (enum HID_ID hid, uint32_t state, uint32_t unicode)
{
    //int SDL_TranslateUNICODE = 0;
    const PSL1GHT_Key* key = PSL1GHT_GetKeyFromHID(hid);
/*
    SDL_keysym sym;
    FillKeysym(&sym, key->symbol, key->scancode);

    if(SDL_TranslateUNICODE)
    {
        sym.unicode = unicode;
    }
*/
    SDL_SendKeyboardKey(state, key->scancode);
}

void
PSL1GHT_DoModifierEvent (SDLKey skey, uint32_t state)
{
    //SDL_keysym sym;
    //FillKeysym(&sym, key, 0);
    const PSL1GHT_Key* key = PSL1GHT_GetKeyFromSDLK(skey);
    SDL_SendKeyboardKey(state, key->scancode);
}

