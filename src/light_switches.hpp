#pragma once

#include "electronics.hpp"

class LightSwitches {
 public:
  LightSwitches();
  void SetHeadlights(bool on);
  void SetBrakeLights(bool on);
  void SetReversingLights(bool on);
  void SetSideLights(bool on);
  void SetLeftIndicator(bool on);
  void SetRightIndicator(bool on);
  void SetHazardLights(bool on);
  // This would typically be called in your main loop
  void UpdateLights();

 private:
  // All of the leds on the car.
  Electronics electronics_;
  // High level logic for the indicators and hazard lights.
  bool left_indicator_on_;
  bool right_indicator_on_;
  bool hazard_lights_on_;
  // Store previous indicator states when hazards are activated
  bool previous_left_indicator_;
  bool previous_right_indicator_;
};
