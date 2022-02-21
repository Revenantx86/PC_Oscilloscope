#include <Arduino.h>
#include <string.h>

bool started = false;
String data;

//Custom Functions
void comCheck();
String serialRead();
void dataAcq();
void configureADC();

// Main & Loop
void setup()
{
  Serial.begin(250000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  dataAcq();
}

String serialRead()
{
  String output;
  if (Serial.available() > 0)
  {
    output = Serial.readString();
    return output;
  }
}

void comCheck()
{
  data = serialRead();
  if (data == "#start\n")
  {
    Serial.println(data);
    started = true;
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (data == "#test")
  {
    Serial.println("#comok");
  }
  delay(50);
}

void dataAcq()
{
  int val = analogRead(A0);
  Serial.println(val);
  Serial.print(",");
}
