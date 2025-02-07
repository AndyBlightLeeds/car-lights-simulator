#include "car_lights.hpp"

#include <chrono>
#include <iostream>
#include <thread>

CarLights::CarLights()
    : headlights_on_(false),
      brake_lights_on_(false),
      left_indicator_on_(false),
      right_indicator_on_(false),
      hazard_lights_on_(false),
      previous_left_indicator_(false),
      previous_right_indicator_(false) {}

void CarLights::setHeadlights(bool on) { headlights_on_ = on; }

void CarLights::setBrakeLights(bool on) { brake_lights_on_ = on; }

void CarLights::clearIndicators() {
  left_indicator_on_ = false;
  right_indicator_on_ = false;
}

void CarLights::setLeftIndicator(bool on) {
  if (!hazard_lights_on_) {
    if (on) {
      clearIndicators();
      left_indicator_on_ = true;
    } else {
      left_indicator_on_ = false;
    }
  }
}

void CarLights::setRightIndicator(bool on) {
  if (!hazard_lights_on_) {
    if (on) {
      clearIndicators();
      right_indicator_on_ = true;
    } else {
      right_indicator_on_ = false;
    }
  }
}

void CarLights::setHazardLights(bool on) {
  if (on) {
    // Store current indicator states
    previous_left_indicator_ = left_indicator_on_;
    previous_right_indicator_ = right_indicator_on_;

    // Activate hazard lights
    clearIndicators();
    hazard_lights_on_ = true;
  } else {
    // Restore previous indicator states
    hazard_lights_on_ = false;
    left_indicator_on_ = previous_left_indicator_;
    right_indicator_on_ = previous_right_indicator_;
  }
}

// Method to simulate the current state of lights
// This would typically be called in your main loop
void CarLights::updateLights() {
  static auto last_blink = std::chrono::steady_clock::now();
  static bool blink_state = false;

  auto now = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - last_blink)
          .count();

  // Toggle blink state every 500ms
  if (elapsed >= 500) {
    blink_state = !blink_state;
    last_blink = now;
  }

  // Debug output - you would replace this with actual hardware control
  std::cout << "\nLights Status: ";
  std::cout << "Headlights[" << (headlights_on_ ? "ON" : "OFF") << "] ";
  std::cout << "Brake[" << (brake_lights_on_ ? "ON" : "OFF") << "] ";
  std::cout << "Left[" << (left_indicator_on_ && blink_state ? "ON" : "OFF")
            << "] ";
  std::cout << "Right[" << (right_indicator_on_ && blink_state ? "ON" : "OFF")
            << "] ";
  std::cout << "Hazards[" << (hazard_lights_on_ ? "ON" : "OFF") << "] ";
}
