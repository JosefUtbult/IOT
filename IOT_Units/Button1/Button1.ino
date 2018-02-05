#include "Wifi.h"

const String id = "01_001_01";

const int SWITCH = D1;
const int RELAY = D2;

bool lastVariable = false;

void setup() {

  Serial.begin(115200);
  Serial.println("Begin!");

  Wifi().begin();
  
  pinMode(SWITCH, INPUT);
  pinMode(RELAY, OUTPUT);

  lastVariable = digitalRead(SWITCH);

}

void loop() {
  // put your main code here, to run repeatedly:

    if(!lastVariable && !digitalRead(SWITCH)){
      Serial.println("LOW");
      
      lastVariable = true;

      Wifi().setUrl(id, "1");
      
      digitalWrite(RELAY, HIGH);
      Wifi().resetLastUpdate();

      
    }
    else if(lastVariable && digitalRead(SWITCH)){
      Serial.println("HIGH");
      
      lastVariable = false;

      Wifi().setUrl(id, "0");

      digitalWrite(RELAY, LOW);
      Wifi().resetLastUpdate();
      
    }
    else if(Wifi().checkLastUpdate()){
      Wifi().resetLastUpdate();
 
        String value = Wifi().runURL("http://" + Wifi().getIp() + "/variable/id=" + id + "&o=read");

        if(value == "1"){
          digitalWrite(RELAY, HIGH);
        }
        else if(value == "0"){
          digitalWrite(RELAY, LOW);
        }

    }

    Wifi().iteration();
    
    delay(100);

}







