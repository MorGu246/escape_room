#include <DIYables_4Digit7Segment_74HC595.h>
#define DATA_PIN D7
#define LATCH_PIN D6
#define CLK_PIN D5

DIYables_4Digit7Segment_74HC595 display(CLK_PIN, LATCH_PIN, DATA_PIN);

#define LockPin D4
String btn;
String myPassword;
int number;
unsigned long timer;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LockPin,OUTPUT);
  btn="";
  myPassword="";
  Wifi_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  wifi_loop();
  display.loop();
  showNumber();
    digitalWrite(LockPin,HIGH);
    if(btn=="unlock"){
      if(myPassword=="2697"){
        digitalWrite(LockPin,LOW);
      }
    }
}

void showNumber(){
  if(millis()-timer>1000){
    number=val;
    display.printInt(number,false);
    timer=millis();
  }
}