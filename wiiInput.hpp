#pragma once
#include "glm/glm.hpp"

struct expansion_t;
class WiiInput
{
    public:
        void Init();
        void StartFrame();

        bool ButtonPress(int buttonEnum);
        bool ButtonRelease(int buttonEnum);
        bool ButtonHeld(int buttonEnum);

        glm::vec2 GetCursorPosition();
        glm::vec2 GetNunchukJoystickDirection(float deadzone);

    private:
        glm::vec2 ReadNunchukJoystickDirection(expansion_t &ex, float deadzone);

        char ir_message[60];
        char position_message[60];
        char correction_message[60];


        float ir_x;
        float ir_y;

        int cursor_x;
        int cursor_y;

        float correction_x;
        float correction_y;

        glm::vec2 nunchukJoystickDir;
        float nunchukJoystickDeadzone;
};