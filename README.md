# Variable-Speed-Bench-Grinder
A grinding wheel is spun by a DC motor, which is set to a particular speed by the user via a potentiometer.

![](https://github.com/BenHenderson09/Variable-Speed-Bench-Grinder/blob/master/grinder.jpg)

## Details
- 24VDC motor from an old scooter drives the grinding wheel.
- A laptop power supply converts 240VAC to 19VDC before then boosting to 24VDC with a buck boost converter.
- A 2N3055 power transistor with heatsink acts as a switching mechanism to pulse-width modulate the motor for speed control.
- An Arduino Nano reads the potentiometer setting and correspondingly calculates a duty cycle to PWM the motor. The Arduino will then saturate
the transistor at intervals to achieve the desired duty cycle, controlling the speed of the motor.
- Includes a flyback diode to protect against voltage spikes.
- The circuitry is enclosed in a steel box, with the motor bolted to a steel holder. Both of these are mounted to an aluminium stand which was reinforced
with 10mm steel bars welded together for support.