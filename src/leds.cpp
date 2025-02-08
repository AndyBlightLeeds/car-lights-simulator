#include "leds.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "neopixels.hpp"

// Add business logic here

Leds::Leds()
    : headlights_on_(false),
      brake_lights_on_(false),
      reversing_lights_on_(false),
      side_lights_on_(false),
      left_indicator_on_(false),
      right_indicator_on_(false),
      new_blink_(true) {}

void Leds::Init() { neopixels_.Init(); }
void Leds::SetHeadLights(bool on) {
  headlights_on_ = on;
  neopixels_.SetHeadLights(on);
}
void Leds::SetTailLights(bool on) {
  brake_lights_on_ = on;
  neopixels_.SetTailLights(on);
}
void Leds::SetReversingLights(bool on) {
  reversing_lights_on_ = on;
  neopixels_.SetReversingLights(on);
}

void Leds::SetSideLights(bool on) {
  side_lights_on_ = on;
  neopixels_.SetSideLights(on);
}

void Leds::SetLeftIndicator(bool on) {
  // May have to protect this variable in a multithreaded environment.
  new_blink_ = true;
  left_indicator_on_ = on;
  if (!hazard_lights_on_) {
    neopixels_.SetLeftIndicator(left_indicator_on_);
  }
}

void Leds::SetRightIndicator(bool on) {
  // May have to protect this variable in a multithreaded environment.
  new_blink_ = true;
  right_indicator_on_ = on;
  if (!hazard_lights_on_) {
    neopixels_.SetRightIndicator(right_indicator_on_);
  }
}

void Leds::SetHazardLights(bool on) {
  if (on) {
    // Store current indicator states
    previous_left_indicator_ = left_indicator_on_;
    previous_right_indicator_ = right_indicator_on_;
    // Activate hazard lights
    hazard_lights_on_ = true;
    neopixels_.SetLeftIndicator(true);
    neopixels_.SetRightIndicator(true);
  } else {
    // Restore previous indicator states
    hazard_lights_on_ = false;
    neopixels_.SetLeftIndicator(previous_left_indicator_);
    neopixels_.SetRightIndicator(previous_right_indicator_);
  }
}

void Leds::Update() {
  bool blink_state = GetBlinkState();
  std::cout << "Lights Status: ";
  std::cout << "H[" << (headlights_on_ ? "ON " : "OFF") << "] ";
  std::cout << "B[" << (brake_lights_on_ ? "ON " : "OFF") << "] ";
  std::cout << "R[" << (reversing_lights_on_ ? "ON " : "OFF") << "] ";
  std::cout << "S[" << (side_lights_on_ ? "ON " : "OFF") << "] ";
  std::cout << "L[" << (left_indicator_on_ && blink_state ? "ON " : "OFF")
            << "] ";
  std::cout << "R[" << (right_indicator_on_ && blink_state ? "ON " : "OFF")
            << "] ";
  std::cout << std::endl;
  neopixels_.Update();
}

// Private

bool Leds::GetBlinkState() {
  static auto last_blink = std::chrono::steady_clock::now();
  static bool blink_state = false;
  // Start with the LEDs on for 500ms.
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
