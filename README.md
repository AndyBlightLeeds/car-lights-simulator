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
./car_lights_test
./car_lights_sim
```

## Bugs

* Indicators don't work properly in the sim code.

## Copyright

© 2025, Andy Blight.
