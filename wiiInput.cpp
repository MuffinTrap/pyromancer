#include "wiiInput.hpp"
#include "wiiuse/wpad.h"
#include <mgdl-wii.h>


bool WiiInput::ButtonPress(int buttonEnum) {
  return (WPAD_ButtonsDown(0) & buttonEnum);
}

bool WiiInput::ButtonRelease(int buttonEnum) {
  return (WPAD_ButtonsUp(0) & buttonEnum);
}

bool WiiInput::ButtonHeld(int buttonEnum) {
  return (WPAD_ButtonsHeld(0) & buttonEnum);
}

void WiiInput::Init() {
  WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

  cursor_x = gdl::ScreenXres / 2;
  cursor_y = gdl::ScreenYres / 2;

  // Tested and found these values to be good
  correction_x = -125.0f;
  correction_y = -10.0f;
}

glm::vec2 WiiInput::GetCursorPosition() {
  return glm::vec2(cursor_x, cursor_y);
}

glm::vec2 WiiInput::GetNunchukJoystickDirection(float deadzone)
{
    nunchukJoystickDeadzone = deadzone;
    return nunchukJoystickDir;
}

glm::vec2 WiiInput::ReadNunchukJoystickDirection(expansion_t &ex, float deadzone)
{
    if (ex.type == WPAD_EXP_NUNCHUK)
    {
        joystick_t n = ex.nunchuk.js;
        if (n.mag > deadzone)
        {
            // Angle of 0 means up.
            // 90 right, 180 down, 270 left

            float rad = n.ang * PI / 180.0f;
            float x = 0;
            float y = -1.0f;
            float dirx = glm::cos(rad) * x - glm::sin(rad) * y;
            float diry = glm::sin(rad) * x + glm::cos(rad) * y;
            return glm::vec2(dirx, diry) * n.mag;
        }
    }
    return glm::vec2(0.0f, 0.0f);
}

void WiiInput::StartFrame() {
  WPAD_ScanPads();  // Scan the Wiimotes

  // Nunchuck
  expansion_t ex;
  WPAD_Expansion(WPAD_CHAN_0, &ex);
  nunchukJoystickDir = ReadNunchukJoystickDirection(ex, 0.1f);

  // Pointer
  ir_t ir;
  WPAD_IR(WPAD_CHAN_0, &ir);
  cursor_x = ir.x;
  cursor_y = ir.y;

  /* Found these values by testing:

     IR X goes from 0 to 1200, so 0.5 gives correct result
     IR Y does not cover the whole screen, so multiply with 1.3 before halving


     IR also has:
     ax ay for raw position
     sx sy are for smoothed position
     x  y  are bounded coordinates

     int offset[2] IR XY correction offset
   */

   /*
  const double sensitivity_x = 0.5;
  const double sensitivity_y = 1.3 * 0.5;
  ir_x = ir.sx;
  ir_y = ir.sy;

  cursor_x = (ir.sx - correction_x) * sensitivity_x;
  cursor_y = (ir.sy - correction_y) * sensitivity_y;

  int mult = 1;
  */

/*/
  if (ButtonHeld(WPAD_BUTTON_A)) {
    mult = 10;
  }


  // Adjust with - and +
  if (ButtonPress(WPAD_BUTTON_PLUS)) {
    if (ButtonHeld(WPAD_BUTTON_B)) {
      correction_y += 1 * mult;
    }
    else {
      correction_x += 1 * mult;
    }
  }
  if (ButtonPress(WPAD_BUTTON_MINUS)) {
    if (ButtonHeld(WPAD_BUTTON_B)) {
      correction_y -= 1 * mult;
    }
    else {
      correction_x -= 1 * mult;
    }
  }
  */
}