#pragma once

#include <chrono>
#include <iostream>
#include <thread>

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
  enum Colour { RED, GREEN, BLUE, WHITE, ORANGE };
  const char *ColourToChar(Colour colour);
  // NeoPixel simulated LEDs
  // There are two strips of 8 LEDs each in series.
  // LEDS 0-7 are at the back of the car, 8 to 15 are at the front.
  Colour leds_[16];
  // Fake LEDS values for printing state of LEDS.
  bool headlights_on_;
  bool brake_lights_on_;
  bool reversing_lights_on_;
  bool side_lights_on_;
  bool left_indicator_on_;
  bool right_indicator_on_;
};
