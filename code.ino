#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
SoftwareSerial rfid(2, 3);

#define SS_PIN 10
#define RST_PIN 9

const int granted = 12, denied = 13;
String route1 = "UTTARPRADESH-DELHI", route2 = "UTTARPRADESH-DEHRADUN", route3 = "DELHI-UTTARPRADESH";
String route4 = "DELHI-DEHRADUN", route5 = "DEHRADUN-DELHI", route6 = "DEHRADUN-UTTARPRADESH";
String current_route,temp;
int route,route1_ticket = 15, route2_ticket = 30, route3_ticket = 15, route4_ticket = 20, route5_ticket = 20, route6_ticket = 30;
int total_amount = 5000, used_amount,remaining_amount;


MFRC522 mfrc522(SS_PIN , RST_PIN);

void setup()
  {
  Serial.begin(9600);
  SPI.begin();
    rfid.begin(9600);
    pinMode(granted, OUTPUT);
    pinMode(denied, OUTPUT);
    while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);       
    if(digitalRead(10) ==  LOW){
      EEPROM.put(0, total_amount);
      Serial.println("Amount Recharged");
      Serial.print("Remaining Amount : ");Serial.println(total_amount);
      while(1);
    }else{
      EEPROM.get(0, remaining_amount);  
    }

}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  String content = "";
  byte letter;
  Serial.print("UID : ");
  for(byte i = 0 ; i < mfrc522.uid.size ; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " ");
    Serial.print(mfrc522.uid.uidByte[i] , HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i] , HEX));
  }
      Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "A1 31 6E 1B") {
     while (Serial.available()) {
     delay(10);
     char c = Serial.read();
     if (c == '#') {
        current_route = temp;
        current_route.toUpperCase();
        temp = "";
        Serial.print("Journey Details : ");
        if (current_route.indexOf(route1) != -1) {
        Serial.println(route1);
        route = 1;
        }
       else if (current_route.indexOf(route2) != -1) {
        Serial.println(route2);
        route =2;
       }
       else if (current_route.indexOf(route3) != -1) {
        Serial.println(route3);
        route = 3;
       }
       else if (current_route.indexOf(route4) != -1) {
        Serial.println(route4);
        route =4;
       }
       else if (current_route.indexOf(route5) != -1) {
        Serial.println(route5);
        route = 5;
       }
       else if (current_route.indexOf(route6) != -1) {
        Serial.println(route6);
        route = 6;
       }
       else{
        Serial.print(current_route);
        Serial.println(" is not Valid");
        current_route = "";
        route = 0;
       }
      break;
    }
    temp += c;
  }
      if(route == 0){
                Serial.println("Journey Route not selected");
      }
      else if(route == 1){
        remaining_amount = remaining_amount - route1_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route1_ticket);
        current_route = "";route = 0;
      }
      else if(route == 2){
        remaining_amount = remaining_amount - route2_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route2_ticket);
        current_route = "";route = 0;
      }
      else if(route == 3){
        remaining_amount = remaining_amount - route3_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route3_ticket);
        current_route = "";route = 0;
      }
      else if(route == 4){
        remaining_amount = remaining_amount - route4_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route4_ticket);
        current_route = "";route = 0;
      }
      else if(route == 5){
        remaining_amount = remaining_amount - route5_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route5_ticket);
        current_route = "";route = 0;
      }
      else if(route == 6){
        remaining_amount = remaining_amount - route6_ticket;
        Serial.print("Ticket Rate : ");Serial.println(route6_ticket);
        current_route = "";route = 0;
      }
      EEPROM.put(0, remaining_amount);
      Serial.print("Remaining Amount : ");Serial.println(remaining_amount);
      
  }
    else {
       Serial.println("Access Denied");
    }
}
