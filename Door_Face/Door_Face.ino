#include <cvzone.h>

#define relay 13
#define switch1 7

SerialData serialData(1, 1);  //(numOfValsRec,digitsPerValRec)
int valsRec[1];               // array of int with size numOfValsRec

void setup() {
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  pinMode(switch1, INPUT_PULLUP);
  serialData.begin();
}
void loop() {
  static int get_switch = 0;
  get_switch = digitalRead(switch1);

  serialData.Get(valsRec);
  if ( valsRec[0] == 1 ) {
    digitalWrite(relay, HIGH);
  } else if ( valsRec[0] == 0 ) {
    digitalWrite(relay, LOW);
  }
    if ( get_switch == 0) {
    digitalWrite(relay, HIGH);
  } else if ( get_switch == 1) {
  if ( valsRec[0] == 1 ) {
    digitalWrite(relay, HIGH);
  }
  else
  {
    digitalWrite(relay, LOW);
  }
  }
  delay(10);
}