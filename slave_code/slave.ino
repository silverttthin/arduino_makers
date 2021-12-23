#include <SoftwareSerial.h>
#include <Servo.h>

Servo myServo;
int servoPin = 11;

void servo_control();
void alert_water();


void setup() {
  Serial.begin(38400); 
  Serial1.begin(38400); 
  myServo.attach(servoPin);
}

void loop() {
  servo_control();
  alert_water(); 

}

void servo_control(){
  int angle;
  if(Serial1.available()){ 
  char buf = Serial1.read();
  
  if(buf == '1')
    {
     Serial.println("1");
   
    angle=180;     
    myServo.write(angle);
    
  }
  
   else if(buf == '0')
{
    Serial.println("0");
    angle=0;     
    myServo.write(angle);
      }
  }
}

void alert_water(){
  analogRead(A0);
  int a = analogRead(A0);
  if (a>620){
    Serial1.write('0');
  }
  else{
    Serial1.write('1');
    }
  delay(1000);
}
