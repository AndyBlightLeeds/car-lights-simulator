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
        std::cout << "\n\nDEMO: Headlights" << std::endl;
        switches->SetHeadlights(true);
        state++;
        break;
      case 1:
        std::cout << "\n\nDEMO: Headlights and brake lights" << std::endl;
        switches->SetBrakeLights(true);
        state++;
        break;
      case 2:
        std::cout << "\n\nDEMO: Headlights, left indicators" << std::endl;
        switches->SetBrakeLights(false);
        switches->SetLeftIndicator(true);
        state++;
        break;
      case 3:
        std::cout << "\n\nDEMO: Headlights, right indicators" << std::endl;
        switches->SetLeftIndicator(false);
        switches->SetRightIndicator(true);
        state++;
        break;
      case 4:
        std::cout << "\n\nDEMO: Headlights, hazard" << std::endl;
        switches->SetHazardLights(true);
        state++;
        break;
      case 5:
        std::cout << "\n\nDEMO: Right indicators" << std::endl;
        switches->SetHazardLights(false);
        switches->SetHeadlights(false);
        state++;
        break;
      case 6:
        std::cout << "\n\nDEMO: reversing" << std::endl;
        switches->SetRightIndicator(false);
        switches->SetReversingLights(true);
        state++;
        break;
      case 7:
        std::cout << "\n\nDEMO: sides on" << std::endl;
        switches->SetReversingLights(false);
        switches->SetSideLights(true);
        state++;
        break;
      case 8:
        std::cout << "\n\nDEMO: All off" << std::endl;
        switches->SetSideLights(false);
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
