#include <chrono>
#include <iostream>
#include <thread>

#include "electronics.hpp"

void demo_features(Electronics *electronics) {
  static int call_count = 0;
  call_count++;
  static int state = 0;
  if (call_count % 20 == 0) {
    switch (state) {
      case 0:
        std::cout << "\n\nDEMO: Headlights" << std::endl;
        electronics->SetHeadLights(true);
        state++;
        break;
      case 1:
        std::cout << "\n\nDEMO: Headlights and brake lights" << std::endl;
        electronics->SetBrakeLights(true);
        state++;
        break;
      case 2:
        std::cout << "\n\nDEMO: Headlights, left indicators" << std::endl;
        electronics->SetBrakeLights(false);
        electronics->SetLeftIndicator(true);
        state++;
        break;
      case 3:
        std::cout << "\n\nDEMO: Headlights, right indicators" << std::endl;
        electronics->SetLeftIndicator(false);
        electronics->SetRightIndicator(true);
        state++;
        break;
      case 4:
        std::cout << "\n\nDEMO: Headlights, hazard" << std::endl;
        electronics->SetHazardLights(true);
        state++;
        break;
      case 5:
        std::cout << "\n\nDEMO: Right indicators" << std::endl;
        electronics->SetHazardLights(false);
        electronics->SetHeadLights(false);
        state++;
        break;
      case 6:
        std::cout << "\n\nDEMO: reversing" << std::endl;
        electronics->SetRightIndicator(false);
        electronics->SetReversingLights(true);
        state++;
        break;
      case 7:
        std::cout << "\n\nDEMO: sides on" << std::endl;
        electronics->SetReversingLights(false);
        electronics->SetSideLights(true);
        state++;
        break;
      case 8:
        std::cout << "\n\nDEMO: All off" << std::endl;
        electronics->SetSideLights(false);
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
  Electronics electronics;

  // Main loop
  while (true) {
    demo_features(&electronics);
    electronics.Update();
    sleep_for(100ms);
  }
}
