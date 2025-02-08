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
void NeoPixels::SetHeadLights(bool on) { headlights_on_ = on; }
void NeoPixels::SetTailLights(bool on) { brake_lights_on_ = on; }
void NeoPixels::SetReversingLights(bool on) { reversing_lights_on_ = on; }
void NeoPixels::SetSideLights(bool on) { side_lights_on_ = on; }
void NeoPixels::SetLeftIndicator(bool on) { left_indicator_on_ = on; }
void NeoPixels::SetRightIndicator(bool on) { right_indicator_on_ = on; }

void NeoPixels::Update() {
  std::cout << "NeoPixels: Front 54321098  Rear 01234567" << std::endl;
  std::cout << "                 " << ColourToChar(leds_[15])
            << ColourToChar(leds_[14]) << ColourToChar(leds_[13])
            << ColourToChar(leds_[12]) << ColourToChar(leds_[11])
            << ColourToChar(leds_[10]) << ColourToChar(leds_[9])
            << ColourToChar(leds_[8]) << "      " << ColourToChar(leds_[0])
            << ColourToChar(leds_[1]) << ColourToChar(leds_[2])
            << ColourToChar(leds_[3]) << ColourToChar(leds_[4])
            << ColourToChar(leds_[5]) << ColourToChar(leds_[6])
            << ColourToChar(leds_[7]) << std::endl;
}

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
