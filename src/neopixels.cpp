#include "neopixels.hpp"

#include <chrono>
#include <iostream>
#include <thread>

NeoPixels::NeoPixels()
    : headlights_on_(false),
      brake_lights_on_(false),
      reversing_lights_on_(false),
      side_lights_on_(false),
      left_indicator_on_(false),
      right_indicator_on_(false) {
  std::cout << "Constructor called" << std::endl;
  for (size_t i = 0; i < NUM_LEDS; i++) {
    leds_[i] = OFF;
  }
}
void NeoPixels::Init() { std::cout << "Init called" << std::endl; }

// There are two strips of 8 LEDs each in series.
// LEDS 0-7 are at the back of the car, 8 to 15 are at the front.
// Left indicators are LEDs 0, 1, 14, 15
// Right indicators are LEDs 6, 7, 8, 9.
// Headlights are LEDs 8 to 15.
// Tail lights are LEDs 0, 1, 6, 7.
// Reversing lights are LEDs 2, 3, 4, 5.
// Side lights are LEDs 0, 7, 8, 15.

void NeoPixels::SetHeadLights(bool on) {
  headlights_on_ = on;
  FillRange(8, 15, on ? WHITE : OFF);
}

void NeoPixels::SetTailLights(bool on) {
  brake_lights_on_ = on;
  leds_[0] = on ? RED : OFF;
  leds_[1] = on ? RED : OFF;
  leds_[6] = on ? RED : OFF;
  leds_[7] = on ? RED : OFF;
}

void NeoPixels::SetReversingLights(bool on) {
  reversing_lights_on_ = on;
  FillRange(2, 5, on ? WHITE : OFF);
}

void NeoPixels::SetSideLights(bool on) {
  side_lights_on_ = on;
  leds_[0] = on ? RED : OFF;
  leds_[7] = on ? RED : OFF;
  leds_[8] = on ? WHITE : OFF;
  leds_[15] = on ? WHITE : OFF;
}

void NeoPixels::SetLeftIndicator(bool on) {
  left_indicator_on_ = on;
  FillRange(0, 1, on ? ORANGE : OFF);
  FillRange(14, 15, on ? ORANGE : OFF);
}

void NeoPixels::SetRightIndicator(bool on) {
  right_indicator_on_ = on;
  FillRange(6, 7, on ? ORANGE : OFF);
  FillRange(8, 9, on ? ORANGE : OFF);
}

void NeoPixels::Update() {
  std::cout << "NeoPixels: Front 54321098  Rear 01234567" << std::endl;
  std::cout << "                 " << ColourToChar(leds_[15])
            << ColourToChar(leds_[14]) << ColourToChar(leds_[13])
            << ColourToChar(leds_[12]) << ColourToChar(leds_[11])
            << ColourToChar(leds_[10]) << ColourToChar(leds_[9])
            << ColourToChar(leds_[8]) << "       " << ColourToChar(leds_[0])
            << ColourToChar(leds_[1]) << ColourToChar(leds_[2])
            << ColourToChar(leds_[3]) << ColourToChar(leds_[4])
            << ColourToChar(leds_[5]) << ColourToChar(leds_[6])
            << ColourToChar(leds_[7]) << std::endl;
}

/**** Private */

const char *NeoPixels::ColourToChar(Colour colour) {
  switch (colour) {
    case OFF:
      return "-";
    case RED:
      return "R";
    case GREEN:
      return "G";
    case BLUE:
      return "B";
    case WHITE:
      return "W";
    case ORANGE:
      return "O";
    default:
      return "UNKNOWN";
  }
}

void NeoPixels::FillRange(size_t start, size_t end, Colour colour) {
  for (size_t i = start; i <= end; i++) {
    leds_[i] = colour;
  }
}
