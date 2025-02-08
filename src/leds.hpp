#pragma once

#include <chrono>
#include <iostream>
#include <thread>

#define NUM_PIXELS (16)

class LEDs {
 public:
  LEDs();
  void Init();
  void SetHeadLights(bool on);
  void SetBrakeLights(bool on);
  void SetReversingLights(bool on);
  void SetSideLights(bool on);
  void SetLeftIndicator(bool on);
  void SetRightIndicator(bool on);
  void Update();

 private:
  // Colours
  enum Colour { OFF, RED, GREEN, BLUE, WHITE, ORANGE };
  const char *ColourToChar(Colour colour);
  void PrintLEDStates();
  void FillRange(size_t start, size_t end, Colour colour);
  // Pixels actually do the lighting up of the LEDs.
  Colour pixels_[NUM_PIXELS];
  // Fake LEDS values for printing state of LEDS.
  bool headlights_on_;
  bool brake_lights_on_;
  bool reversing_lights_on_;
  bool side_lights_on_;
  bool left_indicator_on_;
  bool right_indicator_on_;
};
