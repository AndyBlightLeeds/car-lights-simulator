#include <iostream>
#include <chrono>
#include <thread>

class CarLights {
private:
    bool headlights_on;
    bool brake_lights_on;
    bool left_indicator_on;
    bool right_indicator_on;
    bool hazard_lights_on;

    // Store previous indicator states when hazards are activated
    bool previous_left_indicator;
    bool previous_right_indicator;

    // Helper function to ensure mutually exclusive indicator states
    void clearIndicators() {
        left_indicator_on = false;
        right_indicator_on = false;
    }

public:
    CarLights() :
        headlights_on(false),
        brake_lights_on(false),
        left_indicator_on(false),
        right_indicator_on(false),
        hazard_lights_on(false),
        previous_left_indicator(false),
        previous_right_indicator(false) {}

    void toggleHeadlights() {
        headlights_on = !headlights_on;
    }

    void setBrakeLights(bool on) {
        brake_lights_on = on;
    }

    void setLeftIndicator(bool on) {
        if (!hazard_lights_on) {
            if (on) {
                clearIndicators();
                left_indicator_on = true;
            } else {
                left_indicator_on = false;
            }
        }
    }

    void setRightIndicator(bool on) {
        if (!hazard_lights_on) {
            if (on) {
                clearIndicators();
                right_indicator_on = true;
            } else {
                right_indicator_on = false;
            }
        }
    }

    void toggleHazardLights() {
        if (!hazard_lights_on) {
            // Store current indicator states
            previous_left_indicator = left_indicator_on;
            previous_right_indicator = right_indicator_on;

            // Activate hazard lights
            clearIndicators();
            hazard_lights_on = true;
        } else {
            // Restore previous indicator states
            hazard_lights_on = false;
            left_indicator_on = previous_left_indicator;
            right_indicator_on = previous_right_indicator;
        }
    }

    // Method to simulate the current state of lights
    // This would typically be called in your main loop
    void updateLights() {
        static auto last_blink = std::chrono::steady_clock::now();
        static bool blink_state = false;

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>
            (now - last_blink).count();

        // Toggle blink state every 500ms
        if (elapsed >= 500) {
            blink_state = !blink_state;
            last_blink = now;
        }

        // Debug output - you would replace this with actual hardware control
        std::cout << "\rLights Status: ";
        std::cout << "Headlights[" << (headlights_on ? "ON" : "OFF") << "] ";
        std::cout << "Brake[" << (brake_lights_on ? "ON" : "OFF") << "] ";

        if (hazard_lights_on) {
            std::cout << "HAZARD[" << (blink_state ? "ON" : "OFF") << "] ";
        } else {
            std::cout << "Left[" << (left_indicator_on && blink_state ? "ON" : "OFF") << "] ";
            std::cout << "Right[" << (right_indicator_on && blink_state ? "ON" : "OFF") << "] ";
        }
    }
};


int main() {
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    CarLights car;

    // Turn on left indicator
    car.setLeftIndicator(true);

    // Main loop
    while (true) {
        car.updateLights();
        sleep_for(100ms);
    }
}
