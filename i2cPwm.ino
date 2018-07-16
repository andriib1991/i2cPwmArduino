#include <Servo.h>
#include <Wire.h>

#define MOTORS_NUMBER 6
#define SLAVE_ADDRESS 0x05
#define I2C_BUFFER_SIZE

Servo servoMotors[MOTORS_NUMBER];
int servoMotorsAngels[MOTORS_NUMBER];

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);

    servoMotors[0].attach(3);
    servoMotors[1].attach(5);
    servoMotors[2].attach(6);
    servoMotors[3].attach(9);
    servoMotors[4].attach(10);
    servoMotors[5].attach(11);

    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(i2cReceiveData);
}

// the loop function runs over and over again forever
void loop()
{
    delay(100);
}

//callback for received data via I2C
void i2cReceiveData(int byteCount)
{
    uint8_t receivedMessage[I2C_BUFFER_SIZE];
    int i = 0;
    while (Wire.available())
    {
        receivedMessage[i] = (uint8_t)Wire.read();
        // Serial.printf("receivedMessage[i]=%d\n", receivedMessage[i]);
        i++;
    }

    if (i < 4)
    {
        return;
    }
    // Serial.printf("receivedMessage=[%d, %d, %d, %d]\n", receivedMessage[0], receivedMessage[1], receivedMessage[2], receivedMessage[3]);

    int servoMotorIndex = receivedMessage[0];
    int turningAngle =  receivedMessage[2] * 256 + receivedMessage[3];
    // Serial.printf("servo motor index: %d\nturning angle:%d\n", servoMotorIndex, turningAngle);
    servoMotors[servoMotorIndex] = turningAngle;
}

// callback for sending data via I2C
void i2cSendData()
{
    Wire.write(42);
}
