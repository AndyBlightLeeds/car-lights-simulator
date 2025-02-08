#include <chrono>
#include <iostream>
#include <thread>

#include "light_switches.hpp"

void demo_features(LightSwitches *switches) {
  static int call_count = 0;
  call_count++;
  static int state = 0;
  if (call_count % 20 == 0) {
    switch (state) {
      case 0:
        switches->SetHeadlights(true);
        std::cout << "\n\nDEMO: Headlights" << std::endl;
        state++;
        break;
      case 1:
        switches->SetBrakeLights(true);
        std::cout << "\n\nDEMO: Headlights and brake lights" << std::endl;
        state++;
        break;
      case 2:
        switches->SetBrakeLights(false);
        std::cout << "\n\nDEMO: Headlights, left indicators" << std::endl;
        switches->SetLeftIndicator(true);
        state++;
        break;
      case 3:
        switches->SetLeftIndicator(false);
        switches->SetRightIndicator(true);
        std::cout << "\n\nDEMO: Headlights, right indicators" << std::endl;
        state++;
        break;
      case 4:
        switches->SetHazardLights(true);
        std::cout << "\n\nDEMO: Headlights, hazard" << std::endl;
        state++;
        break;
      case 5:
        switches->SetHazardLights(false);
        switches->SetHeadlights(false);
        std::cout << "\n\nDEMO: Right indicators" << std::endl;
        state++;
        break;
      case 6:
        switches->SetRightIndicator(false);
        switches->SetReversingLights(true);
        std::cout << "\n\nDEMO: reversing" << std::endl;
        state++;
        break;
      case 7:
        switches->SetReversingLights(false);
        switches->SetSideLights(true);
        std::cout << "\n\nDEMO: sides on" << std::endl;
        state++;
        break;
      case 8:
        switches->SetSideLights(false);
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
  LightSwitches switches;

  // Main loop
  while (true) {
    demo_features(&switches);
    switches.UpdateLights();
    sleep_for(100ms);
  }
}
