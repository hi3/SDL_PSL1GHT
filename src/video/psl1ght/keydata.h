#ifndef PSL1GHT_keydata_h
#define PSL1GHT_keydata_h

#include <SDL.h>

/* Symbols ending in _ have no known SDLK equal. I have not looked too hard though */
/* Other symbols have the same name as their SDLK equal except with SDLK replaced by HID */
enum HID_ID
{
    HID_NOEVENT, HID_OVERRUN, HID_POSTFAIL, HID_UNDEFINEDERROR,

    //Letters
    HID_a, HID_b, HID_c, HID_d, HID_e, HID_f, HID_g, HID_h, HID_i, HID_j, HID_k, HID_l, HID_m, 
    HID_n, HID_o, HID_p, HID_q, HID_r, HID_s, HID_t, HID_u, HID_v, HID_w, HID_x, HID_y, HID_z,

    //Numbers
    HID_1, HID_2, HID_3, HID_4, HID_5, HID_6, HID_7, HID_8, HID_9, HID_0,

    HID_RETURN, HID_ESCAPE, HID_BACKSPACE, HID_TAB, HID_SPACE, HID_MINUS, HID_PLUS,
    HID_LEFTBRACKET, HID_RIGHTBRACKET, HID_BACKSLASH, HID_EUROPE1_, HID_SEMICOLON,
    HID_QUOTE, HID_BACKQUOTE, HID_COMMA, HID_PERIOD, HID_SLASH, HID_CAPSLOCK,
    HID_F1, HID_F2, HID_F3, HID_F4, HID_F5, HID_F6, HID_F7, HID_F8, HID_F9, HID_F10, HID_F11, HID_F12,
    HID_PRINT, HID_SCROLLOCK, HID_PAUSE, HID_INSERT, HID_HOME, HID_PAGEUP, HID_DELETE, HID_END,
    HID_PAGEDOWN, HID_RIGHT, HID_LEFT, HID_DOWN, HID_UP, HID_NUMLOCK,
    HID_KP_DIVIDE, HID_KP_MULTIPLY, HID_KP_MINUS, HID_KP_PLUS, HID_KP_ENTER,
    HID_KP1, HID_KP2, HID_KP3, HID_KP4, HID_KP5, HID_KP6, HID_KP7, HID_KP8, HID_KP9, HID_KP0,
    HID_KP_PERIOD, HID_EUROPE2_, HID_APP, HID_KEYBOARDPOWER, HID_KP_EQUALS,
    HID_F13, HID_F14, HID_F15, HID_F16_, HID_F17_, HID_F18_, HID_F19_, HID_F20_, HID_F21_, HID_F22_, HID_F23_, HID_F24_,
    HID_EXECUTE_, HID_HELP, HID_MENU, HID_SELECT_, HID_STOP_, HID_AGAIN_, HID_UNDO_, HID_CUT_,
    HID_COPY_, HID_PASTE_, HID_FIND_, HID_MUTE_, HID_VOLUP_, HID_VOLDN_, HID_CAPSLOCK_,
    HID_NUMLOCK_, HID_SCROLLOCK_, HID_BRAZIL_KP_PERIOD_, HID_KBEQUALSIGN_, HID_INTL1_, HID_INTL2_,
    HID_INTL3_, HID_INTL4_, HID_INTL5_,

    //Mouse: Not really hid but who cares?
    HID_LEFTBUTTON = 0x10000, HID_MIDDLEBUTTON, HID_RIGHTBUTTON
};

typedef struct
{
    const char* name;
    SDL_scancode scancode;
    SDLKey symbol;
    Uint16 modifier;
    enum HID_ID HIDID;
} PSL1GHT_Key;

#define PS3_MAX_KEYS    140

const PSL1GHT_Key* PSL1GHT_GetKeyFromHID(enum HID_ID hid);
const PSL1GHT_Key* PSL1GHT_GetKeyFromSDLK(SDLKey key);
void PSL1GHT_DoKeyEvent (enum HID_ID hid, Uint8 state, KbMkey ps3key, KbLed ps3led);
void PSL1GHT_DoKeyEventSDLK(enum HID_ID hid, Uint8 state, uint32_t unicode);
void PSL1GHT_DoModifierEvent(SDLKey skey, Uint8 state);

//void PSL1GHT_ReleaseAllMouseButtons();
//void PSL1GHT_DoMouseEvent(uint32_t aButton, Uint8 state);

#endif

