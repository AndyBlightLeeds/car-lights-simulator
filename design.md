# Design

## Abstraction layers

There are 4 layers of abstraction in this project.

1. The top level control as the driver of the car might see it.  This layer is responsible for operating the switches on the car to control the lights. See `car_light_sim.cpp`.
2. The car lights layer stores the states of the physical switches on the car.  For instance, if the tail lights have two purposes, e.g. indicator and side light, when the indicator finishes with flashing the light, the tail light should be lit. See `light_switches.cpp`.
3. This layer emulates the electronics in the car.  It changes the states of the lights under the control of the layer above.  It also implements the flashing of the indicator lights when required. See `electronics.cpp`.
4. This layer implements the physical layer.  Each light in the layer above is implemented using a number of multicolour LEDs.  In this example, we are simulating two strips of 8 RGBW LEDs. See `leds.cpp`.

## Multi-use LEDs

The most difficult part of this project has been working out the logic for re-using some of the LEDs.  For instance, on the rear light strip, LEDs 0, 1, 6 and 7 are used as brake lights, side lights, reversing lights and indicators.  The electronics layer is the place where this extra logic lives.  Lets look at the tail light example and draw up a table for the expected results.

|   | Side light | Brake light | Indicator | Reversing |
|----------------|:-:|:-:|:-:|:-:|
| Off            | 0 | 0 | 0 | 0 |
| Red (dim)      | 1 | 0 | 0 | 0 |
| Red (bright)   | x | 1 | x | x |
| Orange         | x | x | 1 | 0 |
| White (bright) | x | x | 0 | 1 |

From this table, we can see that there is a situation where the indicator over-rides the brake light.  This is not desirable from a safety point of view, so it becomes clear that we need separate brake light and indicator lights.  Removing the indicator from this table make it much simpler.

| | Side light | Brake light | Reversing |
|--------------|:-:|:-:|:-:|
| Off          | 0 | 0 | 0 |
| Red (dim)    | 1 | 0 | 0 |
| Red (bright) | x | 1 | 0 |
| White (bright) | x | x | 1 |

Therefore, we need to change the allocation of LEDs on the rear lighting strip as shown below:

| LED number | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|------------|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| Before     |BSIR|BSIR| D | D | D | D |BSIR|BSIR|
| After      | I |BSR|BSR| D | D |BSR|BSR| I |

Where: B = Brake, S = Side, I = Indicator, R = Reversing, D = Diagnostic.

From the above, it makes sense for the `LEDs` class to provide methods to set the colours of clusters of lights, not turn on or off lights.  A cluster is a group of LEDs, e.g. 0 and 15 for the left indicator cluster.

### How to implement the logic for the 3 function LEDs

The state of all three switches: brake light, side light and reversing lights are held in the `LightSwitches` class.  When any switch changes state, the `Electronics` class is told about it. When a change occurs, a function can be called to re-evaluate the output from the current input states.  For example, when the brake light is turned on, the electronics layer records the new state and then calls the evaluate function to update the cluster of multi-function LEDs as required. This was implemented and tested.
