SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
BINS=$(SOURCES:.cpp=)

CFLAGS+=-MMD
CXXFLAGS+=-MMD -Wall -std=c++17
LDLIBS+=-lgtest -lgtest_main -pthread

all:
	g++ $(CXXFLAGS) car_lights_test.cpp car_lights.cpp -o car_lights_test $(LDLIBS)

# $(BINS): $(OBJECTS)
#     $(CXX) $(LDFLAGS) $@.o -o $@ $(LDLIBS)

.PHONY: clean

clean:
	$(RM) $(OBJECTS) $(DEPS) $(BINS)

-include $(DEPS)


# g++ -std=c++11 car_lights_test.cpp -o car_lights_test -lgtest -lgtest_main -pthread
