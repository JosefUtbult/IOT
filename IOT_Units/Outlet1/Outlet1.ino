#include "Wifi.h"

const String id = "01_001_01";

const int RELAY[4] = { D1, D2, D7, D6 };

void setup() {

  delay(2000);

  Serial.begin(115200);
  Serial.println("Begin!");

  Wifi().begin();
  
  for(int i = 0; i < 4; i++ ){
    pinMode(RELAY[i], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

    if(Wifi().checkLastUpdate()){
      Wifi().resetLastUpdate();
 
        String value = Wifi().runURL("http://" + Wifi().getIp() + "/variable/id=" + id + "&o=read");

        if(value == "1"){
          digitalWrite(RELAY[1], HIGH);
          digitalWrite(RELAY[3], HIGH);

        }
        else if(value == "0"){
          digitalWrite(RELAY[1], LOW);
          digitalWrite(RELAY[3], LOW);
        }

    }

    Wifi().iteration();
    
    delay(100);

}







