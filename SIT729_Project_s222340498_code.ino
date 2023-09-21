#include <ThingSpeak.h>
#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include "secrets.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>




LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient  client;

const char* ssid     = "******";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "******";     // The password of the Wi-Fi network
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;



const int ledPin = 12;
const int ldrPin = A0;
const int pir = 13;
//const int pir2 = 15;
const int button = 14;
int temp = 0;



void setup() {
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");


Wire.begin(D2, D1);   //Use predefined PINS consts
lcd.begin(20,4);      // The begin call takes the width and height. This
lcd.init();
lcd.backlight();      // Turn on the backlight.
lcd.home();
  

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer



pinMode(ldrPin, INPUT);
pinMode(pir, INPUT);
pinMode(ledPin, OUTPUT);
pinMode(button, INPUT);

//Scale 2
//pinMode(pir2, INPUT);


//Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password, "blynk.cloud", 80);
}



void loop() {

  float ldrStatus = analogRead(ldrPin);
  int motion = digitalRead(pir);
  //int motion2 = digitalRead(pir2);
  float light = digitalRead(ledPin);
  temp = digitalRead(button);
  
  ThingSpeak.setField(2, ldrStatus);
  ThingSpeak.setField(1, motion);
  ThingSpeak.setField(3,light);

if (temp == LOW) {

  int buttonValue = 0;
  ThingSpeak.setField(4, buttonValue);

if (ldrStatus > 300 && motion == LOW) {

digitalWrite(ledPin, LOW);
float ledValue = 0;
//digitalWrite(ledPin2, LOW);


Serial.print("Room has light, No motion detected, Bulb is off. Light in room: ");
Serial.println(ldrStatus);


lcd.setCursor(0, 0);  // Move the cursor at origin
lcd.print("Room still has light");
lcd.setCursor(0, 1);
lcd.print(" No motion detected");
lcd.setCursor(2, 2);
lcd.print("Bulbs are off");
//lcd.setCursor(0, 3);
//lcd.print("Light in room:");

ThingSpeak.setField(2, ldrStatus);
ThingSpeak.setField(1, motion);
ThingSpeak.setField(3, ledValue);

//delay(1000);



// if (temp == HIGH) {
//        digitalWrite(ledPin, HIGH);
//        Serial.println("LED Turned ON");
////        lcd.setCursor(3,2);
////        lcd.print("Bulbs are ON!");
//        delay(1000);
//       }
//     else {
//        digitalWrite(ledPin, LOW);
//        Serial.println("LED Turned OFF");
////        lcd.setCursor(3,2);
////        lcd.print("Bulbs are OFF!");
//        delay(1000);
//       }

       //delay(1000);

}

else if (ldrStatus > 300 && motion == HIGH) {

digitalWrite(ledPin, LOW);
float ledValue = 0;
//digitalWrite(ledPin2, LOW);


Serial.print("Room has light, Motion detected, Bulb is still off. Light in room: ");
Serial.println(ldrStatus);

lcd.setCursor(0, 0);  // Move the cursor at origin
lcd.print("Room still has light");
lcd.setCursor(0, 1);
lcd.print("Motion is  detected");
lcd.setCursor(2, 2);
lcd.print("Bulbs are off");
//lcd.setCursor(0, 3);
//lcd.print("Light in room:");

ThingSpeak.setField(2, ldrStatus);
ThingSpeak.setField(1, motion);
ThingSpeak.setField(3, ledValue);


// if (temp == HIGH) {
//        digitalWrite(ledPin, HIGH);
//        Serial.println("LED Turned ON");
////        lcd.setCursor(3,2);
////        lcd.print("Bulbs are ON!");
//        delay(1000);
//       }
//     else {
//        digitalWrite(ledPin, LOW);
//        Serial.println("LED Turned OFF");
////        lcd.setCursor(3,2);
////        lcd.print("Bulbs are OFF!");
//        delay(1000);
//       }

      // delay(1000);

}

else if (ldrStatus <= 300 && motion == LOW) {

digitalWrite(ledPin, HIGH);
float ledValue = 1;
//digitalWrite(ledPin2, HIGH);

Serial.print("Room has no light, No motion detected, Bulb is ON. Light in room: ");
Serial.println(ldrStatus);

lcd.setCursor(0, 0);  // Move the cursor at origin
lcd.print("Room has no    light");
lcd.setCursor(0, 1);
lcd.print(" No motion detected");
lcd.setCursor(2, 2);
lcd.print("Bulbs are  ON");
//lcd.setCursor(0, 3);
//lcd.print("Light in room:");

ThingSpeak.setField(2, ldrStatus);
ThingSpeak.setField(1, motion);
ThingSpeak.setField(3, ledValue);
delay(1000);

}

else if (ldrStatus <= 300 && motion == HIGH) {

digitalWrite(ledPin, HIGH);
float ledValue = 1;
//digitalWrite(ledPin2, HIGH);

Serial.print("Room has no light, but motion detected, Bulb is ON. Light in room: ");
Serial.println(ldrStatus);



lcd.setCursor(0, 0);  // Move the cursor at origin
lcd.print("Room has no    light");
lcd.setCursor(0, 1);
lcd.print(" But motion detected");
lcd.setCursor(2, 2);
lcd.print("Bulbs are  ON");
//lcd.setCursor(0, 3);
//lcd.print("Light in room:");

ThingSpeak.setField(2, ldrStatus);
ThingSpeak.setField(1, motion);
ThingSpeak.setField(3, ledValue);
delay(1000);
  
  }

} else {
  
     
   digitalWrite(ledPin, HIGH);
   int buttonValue = 1;
        Serial.println("Bulbs are turned ON by Switch");
        lcd.setCursor(0,0);
        lcd.print(" ------------- ");
        lcd.setCursor(0,1);
        lcd.print(" ------------- ");
        lcd.setCursor(0,2);
        lcd.print(" ------------- ");
        lcd.setCursor(0,3);
        lcd.print("Bulbs ON by Switch!");
        delay(1000);

ThingSpeak.setField(4, buttonValue);
        
        }

 
//  Blynk.run();
  
 int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){
    Serial.println("Channel update successful.");
//    Serial.print(F("LDRSTATUS: "));
//    Serial.println(ldrStatus);
//    Serial.print(F("Motion: "));
//    Serial.println(motion);
//    Serial.print(F("LED: "));
//    Serial.println(ledPin);
    
    
  }
  else{
    Serial.println("Connection buffer; system still connceted to cloud ");
  }
  
  }
