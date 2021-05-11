/*
 * Big Clock
 * Tydence Davis
 * 2021-03-19
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ResetButtonPin = 15; // Reset Button INPUT pin

int TimeChange = 1;
float BeatTime = 1000;
int BeatNumber = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

int sensorPin = A1;    // Potentiometer wiper (middle terminal) connected to analog pin 3
                       // Outside leads to ground and +5V
                       
int sensorValue = 0;   // variable to store the value coming from the sensor

int OutPin1x = 2;      // 1x Output
int OutPin2x = 3;      // 2x Output
int OutPin4x = 4;      // 4x Output
int OutPin8x = 5;     // 8x Output
int OutPin16x = 6;    // 16x Output
int OutPin32x = 7;    // 32x Output
int OutPin64x = 13;    // 64x Output
int OutPin96x = 46;    // 96x for MIDI Output
int ResetOutPin = 45;  // Reset Signal Output
int OutPin2b = 14;     // 2 beats Output
int OutPin4b = 15;     // 4 beats Output
int OutPin8b = 16;     // 8 beats Output
int OutPin16b = 17;    // 16 beats Output
int OutPin32b = 18;    // 32 beats Output
int OutPin64b = 19;    // 64 beats  Output

int BPM = 0;  // BPM output
float BPS = 0; // Beats Per Second

float Var2b = 0.000000;
float Var4b = 0.000000;
float Var8b = 0.000000;
float Var16b = 0.000000;
float Var32b = 0.000000;
float Var64b = 0.000000;

bool Out2b = false;
bool Out4b = false;
bool Out8b = false;
bool Out16b = false;
bool Out32b = false;
bool Out64b = false;

bool ResetState = LOW;

void setup(){
  Serial.begin(9600);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Setup Reset Button
  pinMode(ResetButtonPin, INPUT);
  ResetState = LOW; // Starts with Reset off
  pinMode(ResetOutPin, OUTPUT);
  
}

void loop(){
sensorValue = analogRead(sensorPin);  // read the value from the sensor:
DoTheMath();
FlashTheLights();
// ShowBPM();    // Prints the BPM on the screen
// Serial.println(TimeChange);          // debug value
}

void DoTheMath(){
BPM = (sensorValue * 0.0978) + 60 ; // Converts the pot (0 to 1024) into 0 to 100 and adds 60
currentMillis = millis();
BeatTime = sensorValue; // Beat time is in Millis. (60 / BPM) * 1000
TimeChange = currentMillis - previousMillis;
}

void ShowBPM(void) {
//  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(25,0);             // Start at top-left corner
  display.println(F("Current BPM"));
  display.setTextSize(3);             // Draw 2X-scale text
  display.setCursor(40,10); 
  display.print(BPM);
  display.display();
}


void FlashTheLights(){

// 1x
if (TimeChange < BeatTime * 0.5){
  digitalWrite(OutPin1x, HIGH); // Turn the light on
  }

if (TimeChange > BeatTime * 0.5){
  digitalWrite(OutPin1x, LOW); // Turn the light off
  }
  
  

// 2x
 if (TimeChange <= (BeatTime *.25)){
      digitalWrite(OutPin2x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.25) && TimeChange < (BeatTime * .5)){
      digitalWrite(OutPin2x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.5) && TimeChange < (BeatTime *.75)){
      digitalWrite(OutPin2x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.75)){
      digitalWrite(OutPin2x, LOW);  // Turn off the LED
    }
     

// 4x
 if (TimeChange <= (BeatTime *.125)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.125) && TimeChange < (BeatTime * .25)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.25) && TimeChange < (BeatTime * .375)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.375) && TimeChange < (BeatTime * .5)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.5) && TimeChange < (BeatTime * .625)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.675) && TimeChange < (BeatTime * .75)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.75) && TimeChange < (BeatTime * .825)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime * .825)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }



  // 8x
 if (TimeChange <= (BeatTime *.0625)){
      digitalWrite(OutPin8x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.0625) && TimeChange < (BeatTime * .125)){
      digitalWrite(OutPin8x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.125) && TimeChange < (BeatTime * .1825)){
      digitalWrite(OutPin8x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.1825) && TimeChange < (BeatTime * .25)){
      digitalWrite(OutPin8x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.25) && TimeChange < (BeatTime * .3125)){
      digitalWrite(OutPin8x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.3125) && TimeChange < (BeatTime * .375)){
      digitalWrite(OutPin8x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.375) && TimeChange < (BeatTime * .4375)){
      digitalWrite(OutPin8x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.4375) && TimeChange < (BeatTime * .5)){
      digitalWrite(OutPin8x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.5) && TimeChange < (BeatTime * .5625)){
      digitalWrite(OutPin8x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.5625) && TimeChange < (BeatTime * .625)){
      digitalWrite(OutPin8x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.625) && TimeChange < (BeatTime * .6875)){
      digitalWrite(OutPin8x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.6875) && TimeChange < (BeatTime * .75)){
      digitalWrite(OutPin8x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.75) && TimeChange < (BeatTime * .8125)){
      digitalWrite(OutPin8x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.8125) && TimeChange < (BeatTime * .875)){
      digitalWrite(OutPin8x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.875) && TimeChange < (BeatTime * .9375)){
      digitalWrite(OutPin8x, HIGH);  // Turn on the LED
    }
 
 if (TimeChange > (BeatTime * .9325)){
      digitalWrite(OutPin8x, LOW);  // Turn off the LED
    }


  

  // 16x

 if (TimeChange <= (BeatTime *.03125)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.03125) && TimeChange < (BeatTime * .0625)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.0625) && TimeChange < (BeatTime * .09375)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.09375) && TimeChange < (BeatTime * .125)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.125) && TimeChange < (BeatTime * .1525)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.15625) && TimeChange < (BeatTime * .1875)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.1875) && TimeChange < (BeatTime * .21875)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.21875) && TimeChange < (BeatTime * .25)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.25) && TimeChange < (BeatTime * .28125)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.28125) && TimeChange < (BeatTime * .3125)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.3125) && TimeChange < (BeatTime * .34375)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.34375) && TimeChange < (BeatTime * .375)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.375) && TimeChange < (BeatTime * .40625)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.40625) && TimeChange < (BeatTime * .4375)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.4375) && TimeChange < (BeatTime * .5)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.5) && TimeChange < (BeatTime * .53125)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.53125) && TimeChange < (BeatTime * .5625)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.59375) && TimeChange < (BeatTime * .625)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.625) && TimeChange < (BeatTime * .65625)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.65625) && TimeChange < (BeatTime * .6875)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.6875) && TimeChange < (BeatTime * .71875)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.71875) && TimeChange < (BeatTime * .75)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.75) && TimeChange < (BeatTime * .78125)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.78125) && TimeChange < (BeatTime * .8125)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.8125) && TimeChange < (BeatTime * .84375)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.84375) && TimeChange < (BeatTime * .875)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.875) && TimeChange < (BeatTime * .90625)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.90625) && TimeChange < (BeatTime * .9375)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.9375) && TimeChange < (BeatTime * .96875)){
      digitalWrite(OutPin16x, HIGH);  // Turn on the LED
    }
  
 if (TimeChange > (BeatTime * .96875)){
      digitalWrite(OutPin16x, LOW);  // Turn off the LED
    }


  
  
  // 32x (only the 1st half is complete)

 if (TimeChange <= (BeatTime *.015625)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.015625) && TimeChange < (BeatTime * .03125)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.03125) && TimeChange < (BeatTime * .046875)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.046875) && TimeChange < (BeatTime * .0625)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.0625) && TimeChange < (BeatTime * .078125)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.078125) && TimeChange < (BeatTime * .09375)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.09375) && TimeChange < (BeatTime * .109375)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.109375) && TimeChange < (BeatTime * .125)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.125) && TimeChange < (BeatTime * .140625)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.140625) && TimeChange < (BeatTime * .15625)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.15625) && TimeChange < (BeatTime * .171875)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.171875) && TimeChange < (BeatTime * .1875)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.1875) && TimeChange < (BeatTime * .203125)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.203125) && TimeChange < (BeatTime * .21875)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.21875) && TimeChange < (BeatTime * .234375)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.234375) && TimeChange < (BeatTime * .25)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.25) && TimeChange < (BeatTime * .265625)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.265625) && TimeChange < (BeatTime * .28125)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.28125) && TimeChange < (BeatTime * .296875)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.296875) && TimeChange < (BeatTime * .3125)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.3125) && TimeChange < (BeatTime * .328125)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.328125) && TimeChange < (BeatTime * .34375)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.34375) && TimeChange < (BeatTime * .359375)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.359375) && TimeChange < (BeatTime * .3755)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.375) && TimeChange < (BeatTime * .390625)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.390625) && TimeChange < (BeatTime * .40625)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.40625) && TimeChange < (BeatTime * .421875)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.421875) && TimeChange < (BeatTime * .4375)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.4375) && TimeChange < (BeatTime * .453125)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.453125) && TimeChange < (BeatTime * .46875)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.46875) && TimeChange < (BeatTime * .484375)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.484375) && TimeChange < (BeatTime * .5)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.5) && TimeChange < (BeatTime * .515625)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.515625) && TimeChange < (BeatTime * .53125)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.53125) && TimeChange < (BeatTime * .546875)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.546875) && TimeChange < (BeatTime * .5625)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.5625) && TimeChange < (BeatTime * .578125)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.578125) && TimeChange < (BeatTime * .59375)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.59375) && TimeChange < (BeatTime * .609375)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.609375) && TimeChange < (BeatTime * .625)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.625) && TimeChange < (BeatTime * .640625)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.640625) && TimeChange < (BeatTime * .65625)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.65625) && TimeChange < (BeatTime * .671875)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.671875) && TimeChange < (BeatTime * .6875)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.6875) && TimeChange < (BeatTime * .703125)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.703125) && TimeChange < (BeatTime * .71875)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.71875) && TimeChange < (BeatTime * .734375)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.734375) && TimeChange < (BeatTime * .75)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.75) && TimeChange < (BeatTime * .765625)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.765625) && TimeChange < (BeatTime * .78125)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.78125) && TimeChange < (BeatTime * .796875)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.796875) && TimeChange < (BeatTime * .8125)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.8125) && TimeChange < (BeatTime * .828125)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.828125) && TimeChange < (BeatTime * .84375)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.84375) && TimeChange < (BeatTime * .859375)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.859375) && TimeChange < (BeatTime * .8755)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.875) && TimeChange < (BeatTime * .890625)){
      digitalWrite(OutPin4x, HIGH);  // Turn on the LED
    }
    
 if (TimeChange > (BeatTime *.890625) && TimeChange < (BeatTime * .90625)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }
 
 if (TimeChange >= (BeatTime *.90625) && TimeChange < (BeatTime * .921875)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.921875) && TimeChange < (BeatTime * .9375)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.9375) && TimeChange < (BeatTime * .953125)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime *.953125) && TimeChange < (BeatTime * .96875)){
      digitalWrite(OutPin4x, LOW);  // Turn off the LED
    }

 if (TimeChange >= (BeatTime *.96875) && TimeChange < (BeatTime * .984375)){
      digitalWrite(OutPin32x, HIGH);  // Turn on the LED
    }

 if (TimeChange > (BeatTime * .984375)){
      digitalWrite(OutPin32x, LOW);  // Turn off the LED
    }




  
  // 64x
 if (TimeChange <= (BeatTime * 0.0078125)){
      digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.0078125) && TimeChange < (BeatTime * 0.015625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.015625) && TimeChange < (BeatTime * 0.0234375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.0234375) && TimeChange < (BeatTime * 0.03125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.03125) && TimeChange < (BeatTime * 0.0390625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.0390625) && TimeChange < (BeatTime * 0.046875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.046875) && TimeChange < (BeatTime * 0.0546875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.0546875) && TimeChange < (BeatTime * 0.0625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.0625) && TimeChange < (BeatTime * 0.0703125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.0703125) && TimeChange < (BeatTime * 0.078125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.078125) && TimeChange < (BeatTime * 0.0859375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.0859375) && TimeChange < (BeatTime * 0.09375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.09375) && TimeChange < (BeatTime * 0.1015625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.1015625) && TimeChange < (BeatTime * 0.109375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.109375) && TimeChange < (BeatTime * 0.1171875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.1171875) && TimeChange < (BeatTime * 0.125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.125) && TimeChange < (BeatTime * 0.1328125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.1328125) && TimeChange < (BeatTime * 0.140625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.140625) && TimeChange < (BeatTime * 0.1484375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.1484375) && TimeChange < (BeatTime * 0.15625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.15625) && TimeChange < (BeatTime * 0.1640625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.1640625) && TimeChange < (BeatTime * 0.171875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.171875) && TimeChange < (BeatTime * 0.1796875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.1796875) && TimeChange < (BeatTime * 0.1875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.1875) && TimeChange < (BeatTime * 0.1953125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.1953125) && TimeChange < (BeatTime * 0.203125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.203125) && TimeChange < (BeatTime * 0.2109375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.2109375) && TimeChange < (BeatTime * 0.21875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.21875) && TimeChange < (BeatTime * 0.2265625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.2265625) && TimeChange < (BeatTime * 0.234375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.234375) && TimeChange < (BeatTime * 0.2421875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.2421875) && TimeChange < (BeatTime * 0.25)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.25) && TimeChange < (BeatTime * 0.2578125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.2578125) && TimeChange < (BeatTime * 0.265625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.265625) && TimeChange < (BeatTime * 0.2734375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.2734375) && TimeChange < (BeatTime * 0.28125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.28125) && TimeChange < (BeatTime * 0.2890625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.2890625) && TimeChange < (BeatTime * 0.296875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.296875) && TimeChange < (BeatTime * 0.3046875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.3046875) && TimeChange < (BeatTime * 0.3125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.3125) && TimeChange < (BeatTime * 0.3203125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.3203125) && TimeChange < (BeatTime * 0.328125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.328125) && TimeChange < (BeatTime * 0.3359375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.3359375) && TimeChange < (BeatTime * 0.34375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.34375) && TimeChange < (BeatTime * 0.3515625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.3515625) && TimeChange < (BeatTime * 0.359375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.359375) && TimeChange < (BeatTime * 0.3671875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.3671875) && TimeChange < (BeatTime * 0.375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.375) && TimeChange < (BeatTime * 0.3828125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.3828125) && TimeChange < (BeatTime * 0.390625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.390625) && TimeChange < (BeatTime * 0.3984375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.3984375) && TimeChange < (BeatTime * 0.40625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.40625) && TimeChange < (BeatTime * 0.4140625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.4140625) && TimeChange < (BeatTime * 0.421875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.421875) && TimeChange < (BeatTime * 0.4296875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.4296875) && TimeChange < (BeatTime * 0.4375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.4375) && TimeChange < (BeatTime * 0.4453125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.4453125) && TimeChange < (BeatTime * 0.453125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.453125) && TimeChange < (BeatTime * 0.4609375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.4609375) && TimeChange < (BeatTime * 0.46875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.46875) && TimeChange < (BeatTime * 0.4765625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.4765625) && TimeChange < (BeatTime * 0.484375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.484375) && TimeChange < (BeatTime * 0.4921875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.4921875) && TimeChange < (BeatTime * 0.5)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.5) && TimeChange < (BeatTime * 0.5078125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.5078125) && TimeChange < (BeatTime * 0.515625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.515625) && TimeChange < (BeatTime * 0.5234375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.5234375) && TimeChange < (BeatTime * 0.53125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.53125) && TimeChange < (BeatTime * 0.5390625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.5390625) && TimeChange < (BeatTime * 0.546875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.546875) && TimeChange < (BeatTime * 0.5546875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.5546875) && TimeChange < (BeatTime * 0.5625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.5625) && TimeChange < (BeatTime * 0.5703125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.5703125) && TimeChange < (BeatTime * 0.578125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.578125) && TimeChange < (BeatTime * 0.5859375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.5859375) && TimeChange < (BeatTime * 0.59375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.59375) && TimeChange < (BeatTime * 0.6015625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.6015625) && TimeChange < (BeatTime * 0.609375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.609375) && TimeChange < (BeatTime * 0.6171875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.6171875) && TimeChange < (BeatTime * 0.625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.625) && TimeChange < (BeatTime * 0.6328125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.6328125) && TimeChange < (BeatTime * 0.640625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.640625) && TimeChange < (BeatTime * 0.6484375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.6484375) && TimeChange < (BeatTime * 0.65625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.65625) && TimeChange < (BeatTime * 0.6640625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.6640625) && TimeChange < (BeatTime * 0.671875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.671875) && TimeChange < (BeatTime * 0.6796875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.6796875) && TimeChange < (BeatTime * 0.6875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.6875) && TimeChange < (BeatTime * 0.6953125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.6953125) && TimeChange < (BeatTime * 0.703125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.703125) && TimeChange < (BeatTime * 0.7109375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.7109375) && TimeChange < (BeatTime * 0.71875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.71875) && TimeChange < (BeatTime * 0.7265625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.7265625) && TimeChange < (BeatTime * 0.734375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.734375) && TimeChange < (BeatTime * 0.7421875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.7421875) && TimeChange < (BeatTime * 0.75)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.75) && TimeChange < (BeatTime * 0.7578125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.7578125) && TimeChange < (BeatTime * 0.765625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.765625) && TimeChange < (BeatTime * 0.7734375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.7734375) && TimeChange < (BeatTime * 0.78125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.78125) && TimeChange < (BeatTime * 0.7890625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.7890625) && TimeChange < (BeatTime * 0.796875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.796875) && TimeChange < (BeatTime * 0.8046875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.8046875) && TimeChange < (BeatTime * 0.8125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.8125) && TimeChange < (BeatTime * 0.8203125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.8203125) && TimeChange < (BeatTime * 0.828125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.828125) && TimeChange < (BeatTime * 0.8359375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.8359375) && TimeChange < (BeatTime * 0.84375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.84375) && TimeChange < (BeatTime * 0.8515625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.8515625) && TimeChange < (BeatTime * 0.859375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.859375) && TimeChange < (BeatTime * 0.8671875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.8671875) && TimeChange < (BeatTime * 0.875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.875) && TimeChange < (BeatTime * 0.8828125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.8828125) && TimeChange < (BeatTime * 0.890625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.890625) && TimeChange < (BeatTime * 0.8984375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.8984375) && TimeChange < (BeatTime * 0.90625)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.90625) && TimeChange < (BeatTime * 0.9140625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.9140625) && TimeChange < (BeatTime * 0.921875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.921875) && TimeChange < (BeatTime * 0.9296875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.9296875) && TimeChange < (BeatTime * 0.9375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.9375) && TimeChange < (BeatTime * 0.9453125)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.9453125) && TimeChange < (BeatTime * 0.953125)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.953125) && TimeChange < (BeatTime * 0.9609375)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.9609375) && TimeChange < (BeatTime * 0.96875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.96875) && TimeChange < (BeatTime * 0.9765625)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
if (TimeChange > (BeatTime *0.9765625) && TimeChange < (BeatTime * 0.984375)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }
if (TimeChange > (BeatTime *0.984375) && TimeChange < (BeatTime * 0.9921875)){
     digitalWrite(OutPin64x, HIGH);  // Turn on the LED
    }
 if (TimeChange > (BeatTime *.9921875)){
      digitalWrite(OutPin64x, LOW);  // Turn off the LED
    }

   
  
  // Every 2 beats
if (BeatNumber - Var2b == 2){
  digitalWrite(OutPin2b, HIGH); // Turn the light on
  Var2b = Var2b + 2;      // Increase the Variable  
  digitalWrite(OutPin2b, LOW); // Turn the light off
  }

  // Every 4 beats
if (BeatNumber - Var2b == 4) {
  digitalWrite(OutPin4b, HIGH); // Turn the light on
  Var2b = Var2b + 4;      // Increase the Variable  
  digitalWrite(OutPin4b, LOW); // Turn the light off
  }

  // Every 8 beats
if (BeatNumber - Var2b == 8) {
  digitalWrite(OutPin8b, HIGH); // Turn the light on
  Var2b = Var2b + 8;      // Increase the Variable  
  digitalWrite(OutPin8b, LOW); // Turn the light off
  }

  // Every 16 beats
if (BeatNumber - Var16b == 16) {
  digitalWrite(OutPin16b, HIGH); // Turn the light on
  Var2b = Var2b + 16;      // Increase the Variable  
  digitalWrite(OutPin16b, LOW); // Turn the light off
  }

  // Every 32 beats
if (BeatNumber - Var2b == 32) {
  digitalWrite(OutPin32b, HIGH); // Turn the light on
  Var2b = Var2b + 32;      // Increase the Variable  
  digitalWrite(OutPin32b, LOW); // Turn the light off
  }

  // Every 64 beats
if (BeatNumber - Var64b == 64) {
  digitalWrite(OutPin64b, HIGH); // Turn the light on
  Var2b = Var2b + 64;      // Increase the Variable  
  digitalWrite(OutPin64b, LOW); // Turn the light off
  }


// Reset Everybody!  
if (BeatTime >= 1.00000){
  digitalWrite(OutPin1x, LOW); // Turn the light off
  digitalWrite(OutPin2x, LOW); // Turn the light off
  digitalWrite(OutPin4x, LOW); // Turn the light off
  digitalWrite(OutPin8x, LOW); // Turn the light off
  digitalWrite(OutPin16x, LOW); // Turn the light off
  digitalWrite(OutPin32x, LOW); // Turn the light off
  digitalWrite(OutPin64x, LOW); // Turn the light off

  BeatNumber = ++BeatNumber; // Increase the Beat Number
    }

 if (currentMillis > (previousMillis + BeatTime)){
  previousMillis = currentMillis; // Mark The BeatTime    
    }
 
}
