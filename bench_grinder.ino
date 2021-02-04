#if FALSE
#include "constants/MotorConstants.hpp"

const int motorControlPin{5};
const int potentiometerPin{A0};

void setMotorDutyCycle(double dutyCycle, int frequencyInHertz);
void startMotor();

void setup(){
    pinMode(motorControlPin, OUTPUT);
    startMotor();

    Serial.begin(9600);
}

void loop(){
    double dutyCycle{((1023-analogRead(potentiometerPin)) / 1023.f) * (1 - MotorConstants::minimumDutyCyclePostStartup) + MotorConstants::minimumDutyCyclePostStartup};

    Serial.println(analogRead(potentiometerPin)); delay(1000);
    //setMotorDutyCycle(dutyCycle, 1000);
}

void startMotor(){
    unsigned long startTime{millis()};

    while (millis() - startTime  <= MotorConstants::startupTimeInMilliseconds){
        setMotorDutyCycle(MotorConstants::minimumDutyCycleOnStartup, 1000);
    }
}

void setMotorDutyCycle(double dutyCycle, int frequencyInHertz){
    double periodInMicroseconds{10E6 * (1.f / frequencyInHertz)};
    double highTimeInMicroseconds{dutyCycle * periodInMicroseconds};
    double lowTimeInMicroseconds{periodInMicroseconds - highTimeInMicroseconds};

    digitalWrite(motorControlPin, HIGH);
    delayMicroseconds(highTimeInMicroseconds);

    if (lowTimeInMicroseconds != 0){
      digitalWrite(motorControlPin, LOW);
      delayMicroseconds(lowTimeInMicroseconds);
    }
}
#else

#include "constants/MotorConstants.hpp"
#include "constants/PinConstants.hpp"

void startMotor();
void setMotorDutyCycle(double dutyCycle);
double getClockwisePotentiometerSettingAsPercentage();
double mapPercentageAboveLowerLimit(double percentage, double lowerLimit);

void setup(){
    delay(400); // Wait for other components to get ready
    pinMode(PinConstants::motorControlPin, OUTPUT);
    startMotor();
}

void loop(){
    double dutyCycle{
        mapPercentageAboveLowerLimit(
            getClockwisePotentiometerSettingAsPercentage(),
            MotorConstants::minimumDutyCyclePostStartup
        )
    };
    
    setMotorDutyCycle(dutyCycle);
}

void startMotor(){
    unsigned long startTime{millis()};

    while (millis() - startTime  <= MotorConstants::startupTimeInMilliseconds){
        setMotorDutyCycle(MotorConstants::minimumDutyCycleOnStartup);
    }
}


double getClockwisePotentiometerSettingAsPercentage(){
    int anticlockwisePotentiometerSetting{analogRead(PinConstants::potentiometerPin)};
    int clockwisePotentiometerSetting{1023 - analogRead(PinConstants::potentiometerPin)};
    return clockwisePotentiometerSetting / 1023.f;
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
    // so this will run the motor at max speed when the pot is very close to fully turned 
    if (lowTimeInMicroseconds > 1){
      digitalWrite(PinConstants::motorControlPin, LOW);
      delayMicroseconds(lowTimeInMicroseconds);
    }
}

#endif
