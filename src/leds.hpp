#pragma once

#include <chrono>
#include <iostream>
#include <thread>

#define NUM_PIXELS (16)

class LEDs {
 public:
  // Colours
  enum Colour { kOff, kRed, kBrightRed, kWhite, kBrightWhite, kOrange };
  LEDs();
  void Init();
  void SetHeadLightCluster(bool on);
  void SetTailLightCluster(Colour colour);
  void SetLeftIndicatorCluster(bool on);
  void SetRightIndicatorCluster(bool on);
  void Update();
  const char *ColourToChar(Colour colour);

 private:
  void PrintLEDStates(const char *func_name = nullptr);
  void FillRange(size_t start, size_t end, Colour colour);
  // Pixels actually do the lighting up of the LEDs.
  Colour pixels_[NUM_PIXELS];
};
