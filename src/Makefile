SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
BINS=$(SOURCES:.cpp=)

SIM_SRCS = car_lights_sim.cpp car_lights.cpp leds.cpp neopixels.cpp

CXXFLAGS+=-MMD -Wall -std=c++17
LDLIBS+=-lgtest -lgtest_main -pthread

all:
#	g++ $(CXXFLAGS) car_lights_test.cpp car_lights.cpp leds.cpp -o car_lights_test $(LDLIBS)
	g++ $(CXXFLAGS) $(SIM_SRCS) -o car_lights_sim -pthread

# $(BINS): $(OBJECTS)
#     $(CXX) $(LDFLAGS) $@.o -o $@ $(LDLIBS)

.PHONY: clean

clean:
	$(RM) $(OBJECTS) $(DEPS) $(BINS)

-include $(DEPS)
