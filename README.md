# Car Lights Simulator

Simulate controlling the lights on a car.

[Claude.ai](https://claude.ai/) gave me the original code including the test harness code.  Since that stage, the code has been almost completely rewritten, test code excepted.

The lights that can be controlled are:

* Headlights: dipped (dim white), full beam (bright white).
* Side Lights: (rear: left and right dim red, front: left and right dim white)
* Brake Lights: (rear: left and right bright red)
* Indicators: (all orange/amber), left, right , hazard.
* Reverse: (bright white on rear lamp clusters)
* Fog light: (bright red on rear lamp clusters)

The [design notes](design.md) go into more detail.

## Build and run

```bash
cd src
make
./car_lights_sim
```

NOTE: The test code built a while ago but after all the refactoring, it is now broken.  The `car_light_sim` tests most of the functions that matter although it is not automatic.

NOTE: The output of the program is not a nice as it could be, but the code works as I need it, so I'm leaving it as is for now. If I get really bored, I might make it look better.

## Copyright

© 2025, Andy Blight.
