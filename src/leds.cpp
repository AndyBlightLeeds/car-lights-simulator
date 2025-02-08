#include "leds.hpp"

#include <chrono>
#include <iostream>
#include <thread>

LEDs::LEDs()
    : headlights_on_(false),
      brake_lights_on_(false),
      reversing_lights_on_(false),
      side_lights_on_(false),
      left_indicator_on_(false),
      right_indicator_on_(false) {
  std::cout << "Constructor called" << std::endl;
  for (size_t i = 0; i < NUM_PIXELS; i++) {
    pixels_[i] = OFF;
  }
}
void LEDs::Init() { std::cout << "Init called" << std::endl; }

// There are two strips of 8 LEDs each in series.
// LEDS 0-7 are at the back of the car, 8 to 15 are at the front.
// Left indicators are LEDs 0, 1, 14, 15
// Right indicators are LEDs 6, 7, 8, 9.
// Headlights are LEDs 8 to 15.
// Tail lights are LEDs 0, 1, 6, 7.
// Reversing lights are LEDs 2, 3, 4, 5.
// Side lights are LEDs 0, 7, 8, 15.

void LEDs::SetHeadLights(bool on) {
  headlights_on_ = on;
  FillRange(8, 15, on ? WHITE : OFF);
}

void LEDs::SetBrakeLights(bool on) {
  brake_lights_on_ = on;
  Colour colour = on ? RED : OFF;
  FillRange(0, 1, colour);
  FillRange(6, 7, colour);
  PrintLEDStates();
}

void LEDs::SetReversingLights(bool on) {
  reversing_lights_on_ = on;
  FillRange(2, 5, on ? WHITE : OFF);
}

void LEDs::SetSideLights(bool on) {
  side_lights_on_ = on;
  Colour colour_rear = on ? RED : OFF;
  Colour colour_front = on ? WHITE : OFF;
  pixels_[0] = colour_rear;
  pixels_[7] = colour_rear;
  pixels_[8] = colour_front;
  pixels_[15] = colour_front;
}

void LEDs::SetLeftIndicator(bool on) {
  left_indicator_on_ = on;
  FillRange(0, 1, on ? ORANGE : OFF);
  FillRange(14, 15, on ? ORANGE : OFF);
  PrintLEDStates();
}

void LEDs::SetRightIndicator(bool on) {
  right_indicator_on_ = on;
  FillRange(6, 7, on ? ORANGE : OFF);
  FillRange(8, 9, on ? ORANGE : OFF);
  PrintLEDStates();
}

void LEDs::Update() {
  std::cout << "LEDs: Front 54321098  Rear 01234567" << std::endl;
  PrintLEDStates();
}

/**** Private */

const char *LEDs::ColourToChar(Colour colour) {
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

void LEDs::PrintLEDStates() {
  std::cout << "            " << ColourToChar(pixels_[15])
            << ColourToChar(pixels_[14]) << ColourToChar(pixels_[13])
            << ColourToChar(pixels_[12]) << ColourToChar(pixels_[11])
            << ColourToChar(pixels_[10]) << ColourToChar(pixels_[9])
            << ColourToChar(pixels_[8]) << "       " << ColourToChar(pixels_[0])
            << ColourToChar(pixels_[1]) << ColourToChar(pixels_[2])
            << ColourToChar(pixels_[3]) << ColourToChar(pixels_[4])
            << ColourToChar(pixels_[5]) << ColourToChar(pixels_[6])
            << ColourToChar(pixels_[7]) << std::endl;
}

void LEDs::FillRange(size_t start, size_t end, Colour colour) {
  for (size_t i = start; i <= end; i++) {
    pixels_[i] = colour;
  }
}
