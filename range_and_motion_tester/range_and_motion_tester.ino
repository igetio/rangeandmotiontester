// Input
int sonarPin = 0;
int irPin = 8;
int motion = 0;
int last = 0;
char motionOut[10];
unsigned long start, finished, elapsed;
// Output

// etc.
int inchesAway;
// include the library code:
#include "Wire.h"
#include "LiquidCrystal.h"
// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);
char output_buffer[10];
void setup()
{
    Serial.begin(9600);  // ...set up the serial ouput
    pinMode(irPin, INPUT);
     // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Range: ");
  lcd.setCursor(0, 1);
lcd.print("Mot:");
  
}

// Main program: list the order of crossfades
void loop()
{
 inchesAway = analogRead(sonarPin) /2;
 motion = digitalRead(irPin);
 
 if (motion == HIGH && last == 0){
 start=millis();
 snprintf_P(motionOut, 10, PSTR("Active    "), elapsed);
 last = 1;
 }
 
 
 if (motion == LOW && last == 1){
  finished=millis();
  Serial.println("Finished");
  elapsed=(finished-start)/1000;
  snprintf_P(motionOut, 10, PSTR("%d sec.     "), elapsed);
  last = 0;
 }
 
 Serial.print("Inches Away:");
 Serial.println(inchesAway);
 delay(100);
  lcd.setCursor(8,  0);
 snprintf_P(output_buffer, 10, PSTR("%d           "), inchesAway);
 lcd.print(output_buffer); 
 lcd.setCursor(5,  1);
 lcd.print(motionOut);
}
