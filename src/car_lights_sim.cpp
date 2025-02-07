#include <chrono>
#include <iostream>
#include <thread>

#include "car_lights.hpp"

void demo_features(CarLights *car) {
  static int call_count = 0;
  call_count++;
  static int state = 0;
  if (call_count % 5 == 0) {
    switch (state) {
      case 0:
        car->setHeadlights(true);
        std::cout << "\n\nDEMO: Headlights" << std::endl;
        state++;
        break;
      case 1:
        car->setBrakeLights(true);
        std::cout << "\n\nDEMO: Headlights and brake lights" << std::endl;
        state++;
        break;
      case 2:
        car->setBrakeLights(false);
        std::cout << "\n\nDEMO: Headlights, left indicators" << std::endl;
        car->setLeftIndicator(true);
        state++;
        break;
      case 3:
        car->setLeftIndicator(false);
        car->setRightIndicator(true);
        std::cout << "\n\nDEMO: Headlights, right indicators" << std::endl;
        state++;
        break;
      case 4:
        car->setHazardLights(true);
        std::cout << "\n\nDEMO: Headlights, hazard" << std::endl;
        state++;
        break;
      case 5:
        car->setHazardLights(false);
        car->setHeadlights(false);
        std::cout << "\n\nDEMO: Right indicators" << std::endl;
        state++;
        break;
      case 6:
        car->setRightIndicator(false);
        std::cout << "\n\nDEMO: All off" << std::endl;
        state = 0;
        break;

      default:
        break;
    }
  }
}

int main() {
  using namespace std::this_thread;      // sleep_for, sleep_until
  using namespace std::chrono_literals;  // ns, us, ms, s, h, etc.
  CarLights car;

  // Main loop
  while (true) {
    demo_features(&car);
    car.updateLights();
    sleep_for(100ms);
  }
}
