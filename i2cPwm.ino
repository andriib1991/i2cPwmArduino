#include <Servo.h>
#include <Wire.h>

#define MOTORS_NUMBER 6
#define SLAVE_ADDRESS 0x05

Servo myservo[MOTORS_NUMBER];
int pos = 0;
int angle = 0;
int del = 50;

uint8_t receivedNumbers[10];
int state = 0;

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);

    myservo[0].attach(3);
    myservo[1].attach(5);
    myservo[2].attach(6);
    myservo[3].attach(9);
    myservo[4].attach(10);
    myservo[5].attach(11);

    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
}

// the loop function runs over and over again forever
void loop()
{
    // for(pos = 0; pos < 180; pos += 5) {
    //     for(int current_motor = 0; current_motor < 1; current_motor++) {
    //     // for(int current_motor = 0; current_motor < MOTORS_NUMBER; current_motor++) {
    //         myservo[current_motor].write(pos + (current_motor * 10));
    //         delay(del);
    //     }
    // }
    // for(pos = 180; pos>=1; pos-=5) {
    //     for(int current_motor = 0; current_motor < 1; current_motor++) {
    //     // for(int current_motor = 0; current_motor < MOTORS_NUMBER; current_motor++) {
    //         myservo[current_motor].write(pos + current_motor * 10);
    //         delay(del);
    //     }
    // }
    myservo[0].write(angle);
    myservo[1].write(angle);
    delay(100);
}

//callback for received data via I2C
void receiveData(int byteCount)
{
    int i = 0;
    while (Wire.available())
    {
        Serial.print("i=");
        Serial.println(i);

        receivedNumbers[i] = (uint8_t)Wire.read();
        Serial.print("receivedNumbers[i]=");
        Serial.println(receivedNumbers[i]);
        i++;
    }

    angle =  (long)receivedNumbers[2] * 256 + (long)receivedNumbers[3];
    del = angle;
    //myservo[0].write(angle);
    Serial.print(angle);
    //Serial.print(angle.toInt());
    //Serial.print(number);
}

// callback for sending data via I2C
void sendData()
{
    Wire.write(42);
}
