#include "electronics.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "leds.hpp"

// Add business logic here

Electronics::Electronics()
    : headlights_on_(false),
      brake_lights_on_(false),
      reversing_lights_on_(false),
      side_lights_on_(false),
      left_indicator_on_(false),
      right_indicator_on_(false),
      new_blink_(true) {}

void Electronics::Init() { leds_.Init(); }

void Electronics::SetHeadLights(bool on) {
  headlights_on_ = on;
  leds_.SetHeadLightCluster(on);
}

void Electronics::SetBrakeLights(bool on) {
  std::cout << __func__ << " " << on << std::endl;
  brake_lights_on_ = on;
  EvaluateTailLights();
}

void Electronics::SetReversingLights(bool on) {
  std::cout << __func__ << " " << on << std::endl;
  reversing_lights_on_ = on;
  EvaluateTailLights();
}

void Electronics::SetSideLights(bool on) {
  std::cout << __func__ << " " << on << std::endl;
  side_lights_on_ = on;
  EvaluateTailLights();
}

void Electronics::SetLeftIndicator(bool on) {
  // May have to protect this variable in a multithreaded environment.
  new_blink_ = true;
  left_indicator_on_ = on;
}

void Electronics::SetRightIndicator(bool on) {
  // May have to protect this variable in a multithreaded environment.
  new_blink_ = true;
  right_indicator_on_ = on;
}

void Electronics::Update() {
  bool blink_state = GetBlinkState();
  std::cout << "Electronics: ";
  std::cout << "H[" << (headlights_on_ ? "ON " : "OFF") << "] ";
  std::cout << "B[" << (brake_lights_on_ ? "ON " : "OFF") << "] ";
  std::cout << "R[" << (reversing_lights_on_ ? "ON " : "OFF") << "] ";
  std::cout << "S[" << (side_lights_on_ ? "ON " : "OFF") << "] ";
  std::cout << "L[" << (left_indicator_on_ && blink_state ? "ON " : "OFF")
            << "] ";
  std::cout << "R[" << (right_indicator_on_ && blink_state ? "ON " : "OFF")
            << "] ";
  std::cout << std::endl;
  // Update the blink state of the LEDs that need to flash.
  leds_.SetLeftIndicatorCluster(left_indicator_on_ && blink_state);
  leds_.SetRightIndicatorCluster(right_indicator_on_ && blink_state);
  leds_.Update();
}

// Private

// Simulates the flasher unit in a car.
bool Electronics::GetBlinkState() {
  static auto last_blink = std::chrono::steady_clock::now();
  static bool blink_state = false;
  // Start with the Electronics on for 500ms.
  if (new_blink_) {
    last_blink = std::chrono::steady_clock::now();
    blink_state = true;
    // May have to protect this variable in a multithreaded environment.
    new_blink_ = false;
  }
  auto now = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - last_blink)
          .count();
  // Toggle blink state every 500ms
  if (elapsed >= 500) {
    blink_state = !blink_state;
    last_blink = now;
  }
  return blink_state;
}

void Electronics::EvaluateTailLights() {
  std::cout << __func__ << std::endl;
  LEDs::Colour colour = LEDs::kOff;
  // Set priority of colours of lights.
  if (reversing_lights_on_) {
    colour = LEDs::kBrightWhite;
  } else {
    if (brake_lights_on_) {
      colour = LEDs::kBrightRed;
    } else {
      if (side_lights_on_) {
        colour = LEDs::kRed;
      }  // Else off
    }
  }
  std::cout << "Elec. Eval. RBS: " << reversing_lights_on_ << brake_lights_on_
            << side_lights_on_ << " Colour: " << leds_.ColourToChar(colour)
            << std::endl;
  leds_.SetTailLightCluster(colour);
}
