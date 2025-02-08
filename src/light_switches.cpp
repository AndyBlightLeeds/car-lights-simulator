#include "light_switches.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "electronics.hpp"

LightSwitches::LightSwitches()
    : left_indicator_on_(false),
      right_indicator_on_(false),
      hazard_lights_on_(false),
      previous_left_indicator_(false),
      previous_right_indicator_(false) {}

void LightSwitches::SetHeadlights(bool on) { electronics_.SetHeadLights(on); }

void LightSwitches::SetBrakeLights(bool on) { electronics_.SetBrakeLights(on); }

void LightSwitches::SetReversingLights(bool on) { electronics_.SetReversingLights(on); }

void LightSwitches::SetSideLights(bool on) { electronics_.SetSideLights(on); }

void LightSwitches::SetLeftIndicator(bool on) {
  if (on) {
    left_indicator_on_ = true;
  } else {
    left_indicator_on_ = false;
  }
  if (!hazard_lights_on_) {
    electronics_.SetLeftIndicator(left_indicator_on_);
  }
}

void LightSwitches::SetRightIndicator(bool on) {
  if (on) {
    right_indicator_on_ = true;
  } else {
    right_indicator_on_ = false;
  }
  if (!hazard_lights_on_) {
    electronics_.SetRightIndicator(right_indicator_on_);
  }
}

void LightSwitches::SetHazardLights(bool on) {
  if (on) {
    // Store current indicator states
    previous_left_indicator_ = left_indicator_on_;
    previous_right_indicator_ = right_indicator_on_;

    // Activate hazard lights
    hazard_lights_on_ = true;
    electronics_.SetLeftIndicator(true);
    electronics_.SetRightIndicator(true);
  } else {
    // Restore previous indicator states
    hazard_lights_on_ = false;
    electronics_.SetLeftIndicator(previous_left_indicator_);
    electronics_.SetRightIndicator(previous_right_indicator_);
  }
}

// Call at least every 100ms to update the blink state.
void LightSwitches::UpdateLights() { electronics_.Update(); }
