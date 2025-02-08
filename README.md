# Car Lights Simulator

Simulate controlling the lights on a car.

Written with help from [Claude.ai](https://claude.ai/).

The lights that can be controlled are:

* Headlights: dipped (dim white), full beam (bright white).
* Side Lights: (rear: left and right dim red, front: left and right dim white)
* Brake Lights: (rear: left and right bright red)
* Indicators: (all orange/amber), left, right , hazard.
* Reverse: (bright white on rear lamp clusters)
* Fog light: (bright red on rear lamp clusters)

## Build and run

```bash
cd src
make
./car_lights_sim
```

NOTE: The test code built a while ago but after all the refactoring, it is now broken.  The `car_light_sim` tests most of the functions that matter although it is not automatic.

## Design

There are 4 layers of abstraction in this project.

1. The top level control as the driver of the car might see it.  This layer is responsible for operating the switches on the car to control the lights. See `car_light_sim.cpp`.
2. The car lights layer stores the states of the physical switches on the car.  For instance, if the tail lights have two purposes, e.g. indicator and side light, when the indicator finishes with flashing the light, the tail light should be lit. See `light_switches.cpp`.
3. This layer emulates the electronics in the car.  It changes the states of the lights under the control of the layer above.  It also implements the flashing of the indicator lights when required. See `electronics.cpp`.
4. This layer implements the physical layer.  Each light in the layer above is implemented using a number of multicolour LEDs (NeoPixels are commonly used). See `leds.cpp`.

## Bugs

* None that I'm aware of.

## Copyright

© 2025, Andy Blight.
