#include "constants/MotorConstants.hpp"
#include "constants/PinConstants.hpp"

void setMotorDutyCycle(double dutyCycle);
double getPotentiometerSettingAsPercentage();
double mapPercentageAboveLowerLimit(double percentage, double lowerLimit);

void setup(){
    pinMode(PinConstants::motorControlPin, OUTPUT);
}

void loop(){
    double dutyCycle{
        mapPercentageAboveLowerLimit(
            getPotentiometerSettingAsPercentage(),
            MotorConstants::minimumDutyCycle
        )
    };

    setMotorDutyCycle(dutyCycle);
}

double getPotentiometerSettingAsPercentage(){
    // Range is from 0 to 1023
    int potentiometerSettingFromRange{analogRead(PinConstants::potentiometerPin)};
    
    // Return percentage as a decimal, range 0 to 1
    return potentiometerSettingFromRange / 1023.f;
}

double mapPercentageAboveLowerLimit(double percentage, double lowerLimit){
    return percentage * (1 - lowerLimit) + lowerLimit;
}

void setMotorDutyCycle(double dutyCycle){
    double periodInSeconds{1.f / MotorConstants::pwmFrequencyInHertz};
    double periodInMicroseconds{10E6 * periodInSeconds};
    double highTimeInMicroseconds{dutyCycle * periodInMicroseconds};
    double lowTimeInMicroseconds{periodInMicroseconds - highTimeInMicroseconds};

    digitalWrite(PinConstants::motorControlPin, HIGH);
    delayMicroseconds(highTimeInMicroseconds);

    // Delaying by a small number of microseconds can take longer than intended,
    // so this check will run the motor without any delay if the potentiometer
    // is very close to fully turned.
    if (lowTimeInMicroseconds > 1){
      digitalWrite(PinConstants::motorControlPin, LOW);
      delayMicroseconds(lowTimeInMicroseconds);
    }
}
