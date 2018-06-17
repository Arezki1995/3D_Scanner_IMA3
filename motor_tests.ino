/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */

// defines pins numbers
const int stepPin = 5; 
const int dirPin = 3;
const int prec05mm = 0.5;
const int prec1mm = 1;
const int prec2mm = 2;
const int prec5mm = 5;
const int prec = prec1mm;
 
void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  // we used 100ohm resistors
  //digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // HIGH = down; LOW = up
  digitalWrite(dirPin,HIGH); 
  delay(2000);
  // Makes 200 pulses for making one full cycle rotation 
  // one full cycle rotation = 1mm 
  for(int x = 0; x < prec*200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(4000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(4000); 
  }
  delay(2000); // One second delay
  
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < prec*200; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(4000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(4000);
  }
  delay(2000);
}
