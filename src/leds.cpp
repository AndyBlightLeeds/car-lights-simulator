#include "leds.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

LEDs::LEDs() {
  std::cout << "Constructor called" << std::endl;
  for (size_t i = 0; i < NUM_PIXELS; i++) {
    pixels_[i] = kOff;
  }
}
void LEDs::Init() { std::cout << "Init called" << std::endl; }

// There are two strips of 8 LEDs each in series.
// LEDS 0-7 are at the back of the car, 8 to 15 are at the front.
// Left indicators are LEDs 0, 15
// Right indicators are LEDs 6, 9.
// Headlights are LEDs 8 to 15.
// Tail lights are LEDs 1, 2, 5, 6.
// Reversing lights are LEDs 2, 3, 4, 5.
// Side lights are LEDs 0, 7, 8, 15.

void LEDs::SetHeadLightCluster(bool on) {
  Colour colour = on ? kBrightWhite : kOff;
  FillRange(9, 14, colour);
}

void LEDs::SetTailLightCluster(Colour colour) {
  FillRange(1, 2, colour);
  FillRange(5, 6, colour);
  PrintLEDStates(__func__);
}

void LEDs::SetLeftIndicatorCluster(bool on) {
  Colour colour = on ? kOrange : kOff;
  pixels_[0] = colour;
  pixels_[15] = colour;
  PrintLEDStates(__func__);
}

void LEDs::SetRightIndicatorCluster(bool on) {
  Colour colour = on ? kOrange : kOff;
  pixels_[7] = colour;
  pixels_[8] = colour;
  PrintLEDStates(__func__);
}

void LEDs::Update() {
  std::cout << "LEDs: Front 54321098  Rear 01234567" << std::endl;
  PrintLEDStates("Update    ");
}

/**** Private */

const char* LEDs::ColourToChar(Colour colour) {
  switch (colour) {
    case kOff:
      return "-";
    case kRed:
    case kBrightRed:
      return "R";
    case kWhite:
    case kBrightWhite:
      return "W";
    case kOrange:
      return "O";
    default:
      return "UNKNOWN";
  }
}

void LEDs::PrintLEDStates(const char* func_name) {
  std::string func_str("???????????");
  if (func_name != nullptr) {
    func_str = func_name;
  }
  std::cout << func_str.substr(0, 10) << ": " << ColourToChar(pixels_[15])
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
