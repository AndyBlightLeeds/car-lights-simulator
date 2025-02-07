#include "car_lights.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <thread>

class TestableCarLights : public CarLights {
 public:
  // Make this method public for testing
  using CarLights::UpdateLights;

  // Add method to capture console output
  std::string getLightsStatus() {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    UpdateLights();

    std::cout.rdbuf(old);
    return buffer.str();
  }

  // Add getters for testing internal state
  bool IsHeadlightsOn() const { return headlights_on_; }
  bool IsBrakeLightsOn() const { return brake_lights_on_; }
  bool IsLeftIndicatorOn() const { return left_indicator_on_; }
  bool IsRightIndicatorOn() const { return right_indicator_on_; }
  bool IsHazardLightsOn() const { return hazard_lights_on_; }
  bool GetPreviousLeftIndicator() const { return previous_left_indicator_; }
  bool GetPreviousRightIndicator() const { return previous_right_indicator_; }
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
  EXPECT_FALSE(lights.IsHeadlightsOn());
  EXPECT_FALSE(lights.IsBrakeLightsOn());
  EXPECT_FALSE(lights.IsLeftIndicatorOn());
  EXPECT_FALSE(lights.IsRightIndicatorOn());
  EXPECT_FALSE(lights.IsHazardLightsOn());
}

TEST_F(CarLightsTest, HeadlightsToggle) {
  lights.SetHeadlights(true);
  EXPECT_TRUE(lights.IsHeadlightsOn());

  lights.SetHeadlights(false);
  EXPECT_FALSE(lights.IsHeadlightsOn());
}

TEST_F(CarLightsTest, BrakeLights) {
  lights.SetBrakeLights(true);
  EXPECT_TRUE(lights.IsBrakeLightsOn());

  lights.SetBrakeLights(false);
  EXPECT_FALSE(lights.IsBrakeLightsOn());
}

// Indicator Tests
TEST_F(CarLightsTest, LeftIndicator) {
  lights.SetLeftIndicator(true);
  EXPECT_TRUE(lights.IsLeftIndicatorOn());
  EXPECT_FALSE(lights.IsRightIndicatorOn());

  lights.SetLeftIndicator(false);
  EXPECT_FALSE(lights.IsLeftIndicatorOn());
}

TEST_F(CarLightsTest, RightIndicator) {
  lights.SetRightIndicator(true);
  EXPECT_TRUE(lights.IsRightIndicatorOn());
  EXPECT_FALSE(lights.IsLeftIndicatorOn());

  lights.SetRightIndicator(false);
  EXPECT_FALSE(lights.IsRightIndicatorOn());
}

TEST_F(CarLightsTest, MutuallyExclusiveIndicators) {
  lights.SetLeftIndicator(true);
  EXPECT_TRUE(lights.IsLeftIndicatorOn());

  lights.SetRightIndicator(true);
  EXPECT_TRUE(lights.IsRightIndicatorOn());
  EXPECT_FALSE(lights.IsLeftIndicatorOn());
}

// Hazard Light Tests
TEST_F(CarLightsTest, BasicHazardOperation) {
  lights.SetHazardLights(true);
  EXPECT_TRUE(lights.IsHazardLightsOn());
  EXPECT_FALSE(lights.IsLeftIndicatorOn());
  EXPECT_FALSE(lights.IsRightIndicatorOn());

  lights.SetHazardLights(true);
  EXPECT_FALSE(lights.IsHazardLightsOn());
}

TEST_F(CarLightsTest, HazardsPreserveIndicatorState) {
  // Set left indicator
  lights.SetLeftIndicator(true);
  EXPECT_TRUE(lights.IsLeftIndicatorOn());

  // Enable hazards
  lights.SetHazardLights(true);
  EXPECT_TRUE(lights.IsHazardLightsOn());
  EXPECT_FALSE(lights.IsLeftIndicatorOn());
  EXPECT_TRUE(lights.GetPreviousLeftIndicator());

  // Disable hazards
  lights.SetHazardLights(false);
  EXPECT_FALSE(lights.IsHazardLightsOn());
  EXPECT_TRUE(lights.IsLeftIndicatorOn());
}

TEST_F(CarLightsTest, IndicatorsBlockedDuringHazards) {
  lights.SetHazardLights(true);

  lights.SetLeftIndicator(true);
  lights.SetRightIndicator(true);

  EXPECT_TRUE(lights.IsHazardLightsOn());
  EXPECT_FALSE(lights.IsLeftIndicatorOn());
  EXPECT_FALSE(lights.IsRightIndicatorOn());
}

// Blinking Behavior Tests
TEST_F(CarLightsTest, IndicatorBlinking) {
  lights.SetLeftIndicator(true);

  std::string initial_state = lights.getLightsStatus();
  std::this_thread::sleep_for(std::chrono::milliseconds(600));
  std::string next_state = lights.getLightsStatus();

  EXPECT_NE(initial_state, next_state);
}

TEST_F(CarLightsTest, HazardBlinking) {
  lights.SetHazardLights(true);

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
