#pragma once

#include "leds.hpp"

class Electronics {
 public:
  Electronics();
  void Init();
  void SetHeadLights(bool on);
  void SetBrakeLights(bool on);
  void SetReversingLights(bool on);
  void SetSideLights(bool on);
  void SetLeftIndicator(bool on);
  void SetRightIndicator(bool on);
  void Update();

 private:
  bool GetBlinkState();
  // High level state variables (like physical switches on a car).
  bool headlights_on_;
  bool brake_lights_on_;
  bool reversing_lights_on_;
  bool side_lights_on_;
  bool left_indicator_on_;
  bool right_indicator_on_;
  // Internal states.
  // May need to protect this variable in a multithreaded environment.
  bool new_blink_;

  // Low level implementation.
  LEDs leds_;
};
