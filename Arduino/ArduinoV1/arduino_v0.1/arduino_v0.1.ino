#include <Arduino.h>
#include <string.h>

bool started = false;
String data;

//Custom Functions
void comCheck();
String serialRead();
void dataAcq();
void dataAcqTest();

//Communication Parameters
String sender;
int val;

// Main & Loop
void setup()
{
  Serial.begin(250000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  //--------ADC Register Changing----------//
  //  ADCSRA |= bit (ADPS0);                               //   2
  //  ADCSRA |= bit (ADPS1);                               //   4
  //  ADCSRA |= bit (ADPS0) | bit (ADPS1);                 //   8
  ADCSRA |= bit(ADPS2); //  16
  //  ADCSRA |= bit (ADPS0) | bit (ADPS2);                 //  32
  // ADCSRA |= bit (ADPS1) | bit (ADPS2);                 //  64
  // ADCSRA |= bit (ADPS0) | bit (ADPS1) | bit (ADPS2);   // 128
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

void dataAcqTest()
{
  int val = analogRead(A0);
  Serial.println(val);
}

void dataAcq() //QT version
{
  val = analogRead(A0);
  sender = String(val);
  Serial.print(sender);
  Serial.write(",");
}
