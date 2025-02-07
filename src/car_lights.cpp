#include "car_lights.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "leds.hpp"

CarLights::CarLights()
    : left_indicator_on_(false),
      right_indicator_on_(false),
      hazard_lights_on_(false),
      previous_left_indicator_(false),
      previous_right_indicator_(false) {}

void CarLights::SetHeadlights(bool on) { leds_.SetHeadLights(on); }

void CarLights::SetBrakeLights(bool on) { leds_.SetTailLights(on); }

void CarLights::SetReversingLights(bool on) { leds_.SetReversingLights(on); }

void CarLights::SetSideLights(bool on) { leds_.SetSideLights(on); }

void CarLights::SetLeftIndicator(bool on) {
  if (on) {
    left_indicator_on_ = true;
  } else {
    left_indicator_on_ = false;
  }
  if (!hazard_lights_on_) {
    leds_.SetLeftIndicator(left_indicator_on_);
  }
}

void CarLights::SetRightIndicator(bool on) {
  if (on) {
    right_indicator_on_ = true;
  } else {
    right_indicator_on_ = false;
  }
  if (!hazard_lights_on_) {
    leds_.SetRightIndicator(right_indicator_on_);
  }
}

void CarLights::SetHazardLights(bool on) {
  if (on) {
    // Store current indicator states
    previous_left_indicator_ = left_indicator_on_;
    previous_right_indicator_ = right_indicator_on_;

    // Activate hazard lights
    hazard_lights_on_ = true;
    leds_.SetLeftIndicator(true);
    leds_.SetRightIndicator(true);
  } else {
    // Restore previous indicator states
    hazard_lights_on_ = false;
    leds_.SetLeftIndicator(previous_left_indicator_);
    leds_.SetRightIndicator(previous_right_indicator_);
  }
}

// Call at least every 100ms to update the blink state.
void CarLights::UpdateLights() { leds_.Update(); }
