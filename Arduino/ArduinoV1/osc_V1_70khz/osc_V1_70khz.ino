int numSamples = 0 ; 
long t, t0;


void setuo()
{

  //-------------  Serial Settings  ----------//

  Serial.begin(115200); //baud rate, rated for the 75kHz operation might change for other

  //-------------  Register Settings  ----------//
  ADCSRA = 0;
  ADCSRB = 0;
  ADMUX |= ( 0 & 0x07); //selecting the analog 0 pin as the input pin of multiplexer
  ADMUX |= ( 1 << REFS0); //Setting up the reference votlage 
  ADMUX |= ( 1 << ADLAR); //left align ADC value to 8 bits from ADCH register

  //-------------   ADC Prescaler Settings  ----------//
  // ADCSRA |= ( 1 << ADPS2 ) | ( 1 << ADPS0); //32 prescale for around 38kHz -> 1_0_1
  ADCSRA |= ( 1 << ADPS2); //16 prescale for around 75kHz -> 1_0_0

  //-------------  Default Operation Register Settings  ----------//
  ADCSRA |= (1 << ADATE); //Enable Auto Trigger <-> manual trigger
  ADCSRA |= (1 << ADIE); //..Enable Intertupts 
  ADCSRA |= ( 1 << ADEN); //Enable ADC
  ADCSRA |= ( 1 << ADSC); //Starting ADC Measure
}

ISR(ADC_vect)
{
  byte x = ADCH;  //8 bit val from ADC
  numSamples++;
}

void loop()
{
  if (numSamples>=1000)
  {
    t = micros()-t0;  // calculate elapsed time

    Serial.print("Sampling frequency: ");
    Serial.print((float)1000000/t);
    Serial.println(" KHz");
    delay(2000);
    
    // restart
    t0 = micros();
    numSamples=0;
  }
}
