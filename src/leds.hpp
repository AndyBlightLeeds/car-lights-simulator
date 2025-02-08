#pragma once

#include <chrono>
#include <iostream>
#include <thread>

#define NUM_LEDS (16)

class NeoPixels {
 public:
  NeoPixels();
  void Init();
  void SetHeadLights(bool on);
  void SetTailLights(bool on);
  void SetReversingLights(bool on);
  void SetSideLights(bool on);
  void SetLeftIndicator(bool on);
  void SetRightIndicator(bool on);
  void Update();

 private:
  // Colours
  enum Colour { OFF, RED, GREEN, BLUE, WHITE, ORANGE };
  const char *ColourToChar(Colour colour);
  void FillRange(size_t start, size_t end, Colour colour);
  // NeoPixel simulated LEDs
  Colour leds_[NUM_LEDS];
  // Fake LEDS values for printing state of LEDS.
  bool headlights_on_;
  bool brake_lights_on_;
  bool reversing_lights_on_;
  bool side_lights_on_;
  bool left_indicator_on_;
  bool right_indicator_on_;
};
