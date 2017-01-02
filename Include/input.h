#ifndef INPUT_H
#define INPUT_H

#include "shared.h"
#include "ttmath.h"

#define KEYCODE_Q               1
#define KEYCODE_W               2
#define KEYCODE_E               3
#define KEYCODE_R               4
#define KEYCODE_T               5
#define KEYCODE_Y               6
#define KEYCODE_U               7
#define KEYCODE_I               8
#define KEYCODE_O               9
#define KEYCODE_P               10
#define KEYCODE_A               11
#define KEYCODE_S               12
#define KEYCODE_D               13
#define KEYCODE_F               14
#define KEYCODE_G               15
#define KEYCODE_H               16
#define KEYCODE_J               17
#define KEYCODE_K               18
#define KEYCODE_L               19
#define KEYCODE_Z               20
#define KEYCODE_X               21
#define KEYCODE_C               22
#define KEYCODE_V               23
#define KEYCODE_B               24
#define KEYCODE_N               25
#define KEYCODE_M               26
#define KEYCODE_TAB             27
#define KEYCODE_CAPSLOCK        28
#define KEYCODE_LSHIFT          29
#define KEYCODE_LCTRL           30

#define KEY_COUNT   32
typedef struct InputState
{
    u8 keyStates[KEY_COUNT];
    u8 keyStatesLastFrame[KEY_COUNT];
    Vec2 mousePosition;
    Vec2 mouseCoord;
} InputState;

int charToKeycode(char ch);

class Input
{
    // TODO: friendship to platform not implementation
    friend class LinuxPlatform;
    friend class WindowsPlatform;
public:
    Input();
    bool GetKeyDown(u32 keyCode);
    bool GetKeyUp(u32 keyCode);
    bool GetKey(u32 keyCode);
protected:
    InputState _input;
};

#endif // INPUT_H
