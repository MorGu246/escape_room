#include <DHT.h>
#include <ASCIIDic.h>
#define pinMuxA D5
#define pinMuxB D6
#define pinMuxC D7
#define pinMuxInOut A0
int val;
int case=1;
//חידה 1
const int LDRPin = ReadMuxChannel(1);
//חידה 2
#define MotorPinA D7
float firstTemp;
#define DHTTYPE DHT22
#define DHT_PIN D5
DHT dht(DHT_PIN, DHTTYPE);
//חידה 3
#define RedLed D5
#define GreenLed D6
#define YellowLed D7
#define BlueLed D8
#define RedBtn D1
#define GreenBtn D2
#define YellowBtn D3
#define BlueBtn D4
#define NUM_OF_LEDS 4
int Leds[NUM_OF_LEDS]={RedLed,GreenLed,YellowLed,BlueLed};
int Btns[NUM_OF_LEDS]={RedBtn,GreenBtn,YellowBtn,BlueBtn};
int OrderOfLights[8];
int rnd;
int points=-1;
int num;
//חידה 4
int VrX;
int VrY;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
//חידה 2
  pinMode(MotorPinA, OUTPUT);
  dht.begin();
  firstTemp = dht.readTemperature();
//חידה 3
  for(int i=0;i<NUM_OF_LEDS;i++){
    pinMode(Leds[i],OUTPUT);
  }
  for(int i=0;i<NUM_OF_LEDS;i++){
    pinMode(Btns[i],INPUT_PULLUP);
  }
  for(int i=0;i<NUM_OF_LEDS;i++){
    digitalWrite(Leds[i],LOW);
  }
  pinMode(pinMuxA, OUTPUT);
  pinMode(pinMuxB, OUTPUT);
	pinMode(pinMuxC, OUTPUT);
	pinMode(pinMuxInOut, INPUT);
  randomSeed(analogRead(ReadMuxChannel(5)));
  for(int i=0;i<8;i++){
    rnd=random(0,NUM_OF_LEDS);
    OrderOfLights[i]=rnd;
  }
//חידה 4
  Serial.begin(9600);
  pinMode(pinMuxA, OUTPUT);
  pinMode(pinMuxB, OUTPUT);
	pinMode(pinMuxC, OUTPUT);
	pinMode(pinMuxInOut, INPUT);
  VrX = ReadMuxChannel(4);
	VrY = ReadMuxChannel(5);
}

void loop() {
  // put your main code here, to run repeatedly:
if(case=1){
  int LDRValue = analogRead(LDRPin);
  int pwmValue = map(LDRValue, 0, 1023, 0, 255);
  Serial.println(pwmValue);
  if(pwmValue<=(0.8*255)){
    val=7;
    SendData(val);
    case=2;
  }
}
if(case=2){
  float temp = dht.readTemperature();
  if((firstTemp-temp)>2){
    digitalWrite(MotorPinA,LOW);
    val=97;
    SendData(val);
    case=3;
  } else{
    digitalWrite(MotorPinA,HIGH);
  }
  delay(2000);
}
if(case=3){
  if(points==-1){
  showColors(OrderOfLights);
  num=0;
  points++;
}
  if(points>-1){
    for(int i=0;i<NUM_OF_LEDS;i++){
      if(digitalRead(Btns[i])==LOW){
        if(i==OrderOfLights[num]){
          points++;
          Serial.println(points);
          num++;
          while(digitalRead(Btns[i])==LOW){delay(50);}
        }
        else{
          points=-1;
        }
      }
    }
  }
  if(points==8){
    val=697;
    SendData(val);
    case=4;
    }
    if(digitalRead(Btns[0])==LOW){
      points=-1;
    }
  }
}

int ReadMuxChannel(int chnl) {

	int a = (bitRead(chnl, 0) > 0) ? HIGH : LOW;
	int b = (bitRead(chnl, 1) > 0) ? HIGH : LOW;
	int c = (bitRead(chnl, 2) > 0) ? HIGH : LOW;
	digitalWrite(pinMuxA, a);
	digitalWrite(pinMuxB, b);
	digitalWrite(pinMuxC, c);
	int ret = analogRead(pinMuxInOut);
	return ret;
}
void showColors(int OrderOfLights[]){
  for(int i=0;i<NUM_OF_LEDS;i++){
    digitalWrite(Leds[i],LOW);
  }
  for(int i=0;i<8;i++){
    Serial.println(OrderOfLights[i]);
    digitalWrite(Leds[OrderOfLights[i]],HIGH);
    delay(1000);
    digitalWrite(Leds[OrderOfLights[i]],LOW);
  }
}
if(case=4){
  VrX = ReadMuxChannel(4);
	VrY = ReadMuxChannel(5);
  if(VrX>1020 && VrY>1020 ||
     VrX>1020 && VrY<25   ||
     VrX<25 && VrY>1020   ||
     VrX<25 && VrY<25){
      val=2697;
      SendData(val);
  }
}