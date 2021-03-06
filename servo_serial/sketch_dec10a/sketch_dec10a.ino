#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
int inByte;


char buffer[20];           
char bufferIndex = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
      inByte = Serial.parseInt();
      Serial.print(inByte);
   
    if (inByte == 1){
      pos += 3;
      Serial.print("inByte == 1");
    }else if(inByte == 2){
      pos -= 3;
      Serial.print("inByte == 2");
    }
    myservo.write(pos);

    Serial.flush();
    
  }

}
