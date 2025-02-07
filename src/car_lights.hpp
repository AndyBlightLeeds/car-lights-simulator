#pragma once

class CarLights {
 public:
  CarLights();
  void setHeadlights(bool on);
  void setBrakeLights(bool on);
  void setLeftIndicator(bool on);
  void setRightIndicator(bool on);
  void setHazardLights(bool on);
  // This would typically be called in your main loop
  void updateLights();

 protected:
  // Protected so test harness can access them.
  bool headlights_on_;
  bool brake_lights_on_;
  bool left_indicator_on_;
  bool right_indicator_on_;
  bool hazard_lights_on_;
  // Store previous indicator states when hazards are activated
  bool previous_left_indicator_;
  bool previous_right_indicator_;
  // Helper function to ensure mutually exclusive indicator states
  void clearIndicators();
};
