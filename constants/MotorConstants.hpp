#ifndef MOTOR_CONSTANTS_HPP
#define MOTOR_CONSTANTS_HPP

namespace MotorConstants {
    const int startupTimeInMilliseconds{2000};
    const double minimumDutyCycleOnStartup{0.4};
    const double minimumDutyCyclePostStartup{0.18};
    const int pwmFrequencyInHertz{1000};
}

#endif