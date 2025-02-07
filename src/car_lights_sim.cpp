#include "car_lights.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main() {
  using namespace std::this_thread;      // sleep_for, sleep_until
  using namespace std::chrono_literals;  // ns, us, ms, s, h, etc.
  CarLights car;

  // Turn on left indicator
  car.setLeftIndicator(true);

  // Main loop
  while (true) {
    car.updateLights();
    sleep_for(100ms);
  }
}
