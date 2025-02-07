#include "car_lights.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <thread>

class TestableCarLights : public CarLights {
 public:
  // Make this method public for testing
  using CarLights::updateLights;

  // Add method to capture console output
  std::string getLightsStatus() {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    updateLights();

    std::cout.rdbuf(old);
    return buffer.str();
  }

  // Add getters for testing internal state
  bool isHeadlightsOn() const { return headlights_on_; }
  bool isBrakeLightsOn() const { return brake_lights_on_; }
  bool isLeftIndicatorOn() const { return left_indicator_on_; }
  bool isRightIndicatorOn() const { return right_indicator_on_; }
  bool isHazardLightsOn() const { return hazard_lights_on_; }
  bool getPreviousLeftIndicator() const { return previous_left_indicator_; }
  bool getPreviousRightIndicator() const { return previous_right_indicator_; }
};

// Test fixture for CarLights
class CarLightsTest : public ::testing::Test {
 protected:
  TestableCarLights lights;

  void SetUp() override {
    // Any setup code would go here
  }

  void TearDown() override {
    // Any cleanup code would go here
  }
};

// Basic Functionality Tests
TEST_F(CarLightsTest, InitialState) {
  EXPECT_FALSE(lights.isHeadlightsOn());
  EXPECT_FALSE(lights.isBrakeLightsOn());
  EXPECT_FALSE(lights.isLeftIndicatorOn());
  EXPECT_FALSE(lights.isRightIndicatorOn());
  EXPECT_FALSE(lights.isHazardLightsOn());
}

TEST_F(CarLightsTest, HeadlightsToggle) {
  lights.setHeadlights(true);
  EXPECT_TRUE(lights.isHeadlightsOn());

  lights.setHeadlights(false);
  EXPECT_FALSE(lights.isHeadlightsOn());
}

TEST_F(CarLightsTest, BrakeLights) {
  lights.setBrakeLights(true);
  EXPECT_TRUE(lights.isBrakeLightsOn());

  lights.setBrakeLights(false);
  EXPECT_FALSE(lights.isBrakeLightsOn());
}

// Indicator Tests
TEST_F(CarLightsTest, LeftIndicator) {
  lights.setLeftIndicator(true);
  EXPECT_TRUE(lights.isLeftIndicatorOn());
  EXPECT_FALSE(lights.isRightIndicatorOn());

  lights.setLeftIndicator(false);
  EXPECT_FALSE(lights.isLeftIndicatorOn());
}

TEST_F(CarLightsTest, RightIndicator) {
  lights.setRightIndicator(true);
  EXPECT_TRUE(lights.isRightIndicatorOn());
  EXPECT_FALSE(lights.isLeftIndicatorOn());

  lights.setRightIndicator(false);
  EXPECT_FALSE(lights.isRightIndicatorOn());
}

TEST_F(CarLightsTest, MutuallyExclusiveIndicators) {
  lights.setLeftIndicator(true);
  EXPECT_TRUE(lights.isLeftIndicatorOn());

  lights.setRightIndicator(true);
  EXPECT_TRUE(lights.isRightIndicatorOn());
  EXPECT_FALSE(lights.isLeftIndicatorOn());
}

// Hazard Light Tests
TEST_F(CarLightsTest, BasicHazardOperation) {
  lights.setHazardLights(true);
  EXPECT_TRUE(lights.isHazardLightsOn());
  EXPECT_FALSE(lights.isLeftIndicatorOn());
  EXPECT_FALSE(lights.isRightIndicatorOn());

  lights.setHazardLights(true);
  EXPECT_FALSE(lights.isHazardLightsOn());
}

TEST_F(CarLightsTest, HazardsPreserveIndicatorState) {
  // Set left indicator
  lights.setLeftIndicator(true);
  EXPECT_TRUE(lights.isLeftIndicatorOn());

  // Enable hazards
  lights.setHazardLights(true);
  EXPECT_TRUE(lights.isHazardLightsOn());
  EXPECT_FALSE(lights.isLeftIndicatorOn());
  EXPECT_TRUE(lights.getPreviousLeftIndicator());

  // Disable hazards
  lights.setHazardLights(false);
  EXPECT_FALSE(lights.isHazardLightsOn());
  EXPECT_TRUE(lights.isLeftIndicatorOn());
}

TEST_F(CarLightsTest, IndicatorsBlockedDuringHazards) {
  lights.setHazardLights(true);

  lights.setLeftIndicator(true);
  lights.setRightIndicator(true);

  EXPECT_TRUE(lights.isHazardLightsOn());
  EXPECT_FALSE(lights.isLeftIndicatorOn());
  EXPECT_FALSE(lights.isRightIndicatorOn());
}

// Blinking Behavior Tests
TEST_F(CarLightsTest, IndicatorBlinking) {
  lights.setLeftIndicator(true);

  std::string initial_state = lights.getLightsStatus();
  std::this_thread::sleep_for(std::chrono::milliseconds(600));
  std::string next_state = lights.getLightsStatus();

  EXPECT_NE(initial_state, next_state);
}

TEST_F(CarLightsTest, HazardBlinking) {
  lights.setHazardLights(true);

  std::string initial_state = lights.getLightsStatus();
  std::this_thread::sleep_for(std::chrono::milliseconds(600));
  std::string next_state = lights.getLightsStatus();

  EXPECT_NE(initial_state, next_state);
}

// Main function to run the tests
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
