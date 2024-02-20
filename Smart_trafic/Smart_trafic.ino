#include <cvzone.h>

SerialData serialData(1, 1); //(numOfValsRec,digitsPerValRec)
int valsRec[1]; // array of int with size numOfValsRec 
void todelay_10s(void);
void todelay_3s(void);
void normal_mode(void);
void get_gas_ldr(void);
void beside_on(void);
void front_on(void);
// Traffic Light 1
const int red1Pin = 2;
const int yellow1Pin = 3;
const int green1Pin = 4;
const int red2Pin = 5;
const int yellow2Pin = 6;
const int green2Pin = 7;

#define gas 8
#define buzz 13
#define ldr  A0
#define relay 11

void setup() {
  pinMode(red1Pin, OUTPUT);
  pinMode(yellow1Pin, OUTPUT);
  pinMode(green1Pin, OUTPUT);
  pinMode(red2Pin, OUTPUT);
  pinMode(yellow2Pin, OUTPUT);
  pinMode(green2Pin, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(gas, INPUT);
  pinMode(ldr, INPUT);
  // Start with the initial state
  //digitalWrite(green1Pin, HIGH);
  //digitalWrite(red2Pin, HIGH);
  digitalWrite(buzz , 0) ;
  //serialData.begin();
  Serial.begin(9600);
}

void loop() {
  //serialData.Get(valsRec);
  get_gas_ldr();
  if(valsRec[0] == 0){   // normal mode
    get_gas_ldr();
    normal_mode();
    get_gas_ldr();
  }else if(valsRec[0] == 1){  // normal car in front with no car beside 
    get_gas_ldr();
    front_on();
    get_gas_ldr();
  }else if(valsRec[0] == 2){  // normal car in beside with no car in front 
    get_gas_ldr();
    beside_on();
    get_gas_ldr();
  }else if(valsRec[0] == 3){  // Ambulance in front 
    get_gas_ldr();
    front_on();
    get_gas_ldr();
  }else if(valsRec[0] == 4){  // Ambulance in beside
    get_gas_ldr();
    beside_on();
    get_gas_ldr();
  }else{
    get_gas_ldr();

    get_gas_ldr();
  }
  
}

void normal_mode(void){
  digitalWrite(red1Pin , HIGH);
  digitalWrite(yellow1Pin , LOW);
  digitalWrite(green1Pin , LOW);
  digitalWrite(red2Pin , LOW);
  digitalWrite(yellow2Pin , LOW);
  digitalWrite(green2Pin , HIGH);
  get_gas_ldr();
  todelay_10s();
  digitalWrite(red1Pin , LOW);
  digitalWrite(yellow1Pin , HIGH);
  digitalWrite(green1Pin , LOW);
  digitalWrite(red2Pin , LOW);
  digitalWrite(yellow2Pin , HIGH);
  digitalWrite(green2Pin , LOW);
  get_gas_ldr();
  todelay_3s();
  digitalWrite(red1Pin , LOW);
  digitalWrite(yellow1Pin , LOW);
  digitalWrite(green1Pin , HIGH);
  digitalWrite(red2Pin , HIGH);
  digitalWrite(yellow2Pin , LOW);
  digitalWrite(green2Pin , LOW);
  get_gas_ldr();
  todelay_10s();
}

void get_gas_ldr(void){
  if(digitalRead(gas) == 0){
      digitalWrite(buzz , 1) ; 
  }else{
      digitalWrite(buzz , 0) ;
  }
  if(analogRead(ldr) < 900 ){
      digitalWrite(relay , 1);
      Serial.println(analogRead(ldr));
  }else{
      digitalWrite(relay , 0);
      Serial.println(analogRead(ldr));
  }
  
}



void front_on(void){
  digitalWrite(red1Pin , HIGH);
  digitalWrite(yellow1Pin , LOW);
  digitalWrite(green1Pin , LOW);
  digitalWrite(red2Pin , LOW);
  digitalWrite(yellow2Pin , LOW);
  digitalWrite(green2Pin , HIGH);
  get_gas_ldr();
}
void beside_on(void){
  digitalWrite(red1Pin , LOW);
  digitalWrite(yellow1Pin , LOW);
  digitalWrite(green1Pin , HIGH);
  digitalWrite(red2Pin , HIGH);
  digitalWrite(yellow2Pin , LOW);
  digitalWrite(green2Pin , LOW);
  get_gas_ldr();
}


void todelay_10s(void){

  for(int i = 0 ; i < 100 ; i++){
    delay(100);
    get_gas_ldr();
  }


}
void todelay_3s(void){

  for(int i = 0 ; i < 30 ; i++){
    delay(100);
    get_gas_ldr();
  }


}