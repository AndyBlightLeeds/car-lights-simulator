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
  void PrintLEDStates(const char *func_name = nullptr);
  void FillRange(size_t start, size_t end, Colour colour);
  // Pixels actually do the lighting up of the LEDs.
  Colour pixels_[NUM_PIXELS];
};
