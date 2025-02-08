#include <chrono>
#include <iostream>
#include <thread>

#include "car_lights.hpp"

void demo_features(CarLights *car) {
  static int call_count = 0;
  call_count++;
  static int state = 0;
  if (call_count % 20 == 0) {
    switch (state) {
      case 0:
        car->SetHeadlights(true);
        std::cout << "\n\nDEMO: Headlights" << std::endl;
        state++;
        break;
      case 1:
        car->SetBrakeLights(true);
        std::cout << "\n\nDEMO: Headlights and brake lights" << std::endl;
        state++;
        break;
      case 2:
        car->SetBrakeLights(false);
        std::cout << "\n\nDEMO: Headlights, left indicators" << std::endl;
        car->SetLeftIndicator(true);
        state++;
        break;
      case 3:
        car->SetLeftIndicator(false);
        car->SetRightIndicator(true);
        std::cout << "\n\nDEMO: Headlights, right indicators" << std::endl;
        state++;
        break;
      case 4:
        car->SetHazardLights(true);
        std::cout << "\n\nDEMO: Headlights, hazard" << std::endl;
        state++;
        break;
      case 5:
        car->SetHazardLights(false);
        car->SetHeadlights(false);
        std::cout << "\n\nDEMO: Right indicators" << std::endl;
        state++;
        break;
      case 6:
        car->SetRightIndicator(false);
        car->SetReversingLights(true);
        std::cout << "\n\nDEMO: reversing" << std::endl;
        state++;
        break;
      case 7:
        car->SetReversingLights(false);
        car->SetSideLights(true);
        std::cout << "\n\nDEMO: sides on" << std::endl;
        state++;
        break;
      case 8:
        car->SetSideLights(false);
        std::cout << "\n\nDEMO: All off" << std::endl;
        state++;
        break;

      default:
        std::cout << "\nDEMO: Done\n" << std::endl;
        exit(1);
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
    car.UpdateLights();
    sleep_for(100ms);
  }
}
