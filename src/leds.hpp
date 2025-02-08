#pragma once

#include "neopixels.hpp"

class Leds {
 public:
  Leds();
  void Init();
  void SetHeadLights(bool on);
  void SetTailLights(bool on);
  void SetReversingLights(bool on);
  void SetSideLights(bool on);
  void SetLeftIndicator(bool on);
  void SetRightIndicator(bool on);
  void SetHazardLights(bool on);
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
  bool hazard_lights_on_;
  // Internal states.
  // May need to protect this variable in a multithreaded environment.
  bool new_blink_;
  // Store previous indicator states when hazards are activated
  bool previous_left_indicator_;
  bool previous_right_indicator_;

  // Low level implementation based on the Neopixels class.
  NeoPixels neopixels_;
};
