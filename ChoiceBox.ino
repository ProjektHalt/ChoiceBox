// written by Rene Seidlitz
// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+

#include <avr/sleep.h>    // Sleep Modes
#include <avr/power.h>    // Power management

const int GREEN_LED = 0;
const int BLUE_LED = 1;
const int RED_LED = 2;
const int SWITCH = 3; 
int i = 0;

ISR (PCINT0_vect) 
 { 
 // do something interesting here
 }
 
void setup ()
  {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode (SWITCH, INPUT);
  digitalWrite (SWITCH, HIGH);  // internal pull-up
  randomSeed(analogRead(5));
  // pin change interrupt (example for D4)
  PCMSK  |= bit (PCINT3);  // want pin D4 / pin 3
  GIFR   |= bit (PCIF);    // clear any outstanding interrupts
  GIMSK  |= bit (PCIE);    // enable pin change interrupts 
  
  }  // end of setup

void loop ()
  {
    i = random(1,4);
    cascadeerzeugen();
    cascadeerzeugen();
    blinken();
    blinken();
    blinken();
    switch(i){
        case 1:
          digitalWrite(GREEN_LED,LOW);
          break;
        case 2:
          digitalWrite(BLUE_LED,LOW);
          break;
        case 3:
          digitalWrite(RED_LED,LOW);
          break;
      }
      delay(2500);
    i=0;
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
  goToSleep ();
  }  // end of loop

  void cascadeerzeugen()
  {
    digitalWrite(GREEN_LED, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(400);                       // wait for a second
    digitalWrite(GREEN_LED, HIGH);    // turn the LED off by making the voltage LOW
    digitalWrite(BLUE_LED, LOW);
    delay(400);                       // wait for a second
    digitalWrite(BLUE_LED, HIGH);    // turn the LED off by making the voltage LOW
    digitalWrite(RED_LED, LOW);
    delay(400);
    digitalWrite(RED_LED, HIGH);    // turn the LED off by making the voltage LOW
    delay(400);
  }

void blinken()
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(250);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(250);
  }
  
void goToSleep ()
  {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ADCSRA = 0;            // turn off ADC
  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
  sleep_enable();
  sleep_cpu();                             
  sleep_disable();   
  power_all_enable();    // power everything back on
  }  // end of goToSleep 
