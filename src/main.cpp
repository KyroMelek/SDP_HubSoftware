#include <Arduino.h>

const byte led_gpio = 32;
void setup()
{
  // put your setup code here, to run once:
  pinMode(led_gpio, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(led_gpio, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                  // wait for a second
  digitalWrite(led_gpio, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);                  // wait for a second
}