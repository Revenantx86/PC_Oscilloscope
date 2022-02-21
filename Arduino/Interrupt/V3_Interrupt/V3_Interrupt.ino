const byte adcPin = 0;
volatile int adcReading;
volatile boolean adcDone;
boolean adcStarted;

void setup ()
{
  Serial.begin (250000);
  ADCSRA =  bit (ADEN);                      // turn ADC on
   ADCSRA |= bit (ADPS1);                    //   4 = 300 kHz
ADMUX  =  bit (REFS0) | (adcPin & 0x07);    // AVcc and select input port

}  


ISR (ADC_vect)
  {
  adcReading = ADC;
  adcDone = true;  
  }  
  
void loop ()
{
  
  if (adcDone)
    {
    adcStarted = false;
  
    Serial.print (adcReading);
    Serial.write(',');
    adcDone = false;
    }   
  
  if (!adcStarted)
    {
    adcStarted = true;
    
    ADCSRA |= bit (ADSC) | bit (ADIE);
    }      

}  
