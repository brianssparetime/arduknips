
#include "SoftwareServo.h" // works with Arduino IDE 1.8.9 and tinycore 1.2.4 by Spence Konde
  // see also https://github.com/electricsheeplabs/attinyServo/blob/master/servoControlWorking.ino
  // couldn't get this one to work: http://www.cunningturtle.com/attiny4585-servo-library/
  



/*
 * ARDUKNIPS!
 * 

 * Use ISP programmer board to program attiny85
 * - burn bootloader if not previous done
 * - 
 * 
 * 
 * 
*/



/*                            ATTINY85
                              _______
         PB5 ADC0   RST <-  1 | o     | 8  -> VCC 5v                    
LED1  <= PB3 ADC3           2 |       | 7  ->              I2C / SCL   PB2 ADC1  ==> BUT
SRV   <= PB4 ADC2           3 |       | 6  -> SPI / MISO               PB1       ==> LED2
                    GND <-  4 |       | 5  -> SPI / MOSI   I2C / SDA   PB0       ==> 
                              -------
*/



// turn on and off serial output for debugging
#define DEBUG 0

SoftwareServo grabber;    

const int SERVO = PB4;
const int R_LED = PB1; // not really needed
const int G_LED = PB3; // turns green on boot, then activates with servo
const int BUT = PB2;
const int SERVO_MAX = 180;
const int SERVO_MIN = 1;
const int REACT_DELAY = 200; // ms
const int LOOP_DELAY = 500; // ms
const int DEBOUNCE_DELAY = 100; //ms

long unsigned last_change = 0;
bool last_but_state = false;

bool r_led_state = 0;
bool g_led_state = 0;



void setup() {
  pinMode(G_LED, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(BUT,INPUT_PULLUP);
  grabber.attach(SERVO);
  grabber.write(SERVO_MIN); // set to initial position

  // blink ready
  for (int i = 0; i < 30; i++) {
    digitalWrite(R_LED, r_led_state);
    digitalWrite(G_LED, r_led_state);
    r_led_state = !r_led_state;
    g_led_state = !g_led_state;
    delay(100);
  }
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, LOW);

}




void loop() {


  bool grab_state = false;  // avoid spamming the servo?
  long unsigned int now = millis();
  bool bval = digitalRead(BUT);

  if (!bval ) {
    // on press, close servo
      digitalWrite(G_LED, HIGH);
      digitalWrite(R_LED, LOW);
      grabber.write(SERVO_MIN);
      SoftwareServo::refresh(); 
    } else  {
        digitalWrite(G_LED, LOW);
        digitalWrite(R_LED, HIGH);
        grabber.write(SERVO_MAX/2);
        SoftwareServo::refresh();
    }
  
 
}
