
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library

#define FIREBASE_HOST "kryptonites-home-automation-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "oXY9CvgrqiuwDYPGcPFgeFMAarncbqaAFk8r6Lwk"
#define WIFI_SSID "praveen"
#define WIFI_PASSWORD "984805621"                                  

String fireStatus = "";
String fireStatus1 = "";// led status received from firebase
int led = D7;// for external led
int fanpin1=D1;
int fanpin2=D2;
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(D0,OUTPUT);     
  pinMode(led, OUTPUT);
  pinMode(fanpin1, OUTPUT);
  pinMode(fanpin2, OUTPUT);                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
                                           //send initial string of led status
}

void loop() {
  fireStatus = Firebase.getString("LED_STATUS");
  fireStatus1=  Firebase.getString("FAN_STATUS");
  Serial.println(fireStatus);                                                                                               // get ld status input from firebase
  if (fireStatus == "ON") {                                                          // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW);                                                  // make bultin led ON
    digitalWrite(led, HIGH);                                                         // make external led ON
  } 
  else if (fireStatus == "OFF") {                                                  // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);                                               // make bultin led OFF
    digitalWrite(led, LOW);                                                         // make external led OFF
  }
  else {
    Serial.println(fireStatus);
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
  if (fireStatus1 == "ON") {                                                          // compare the input of led status received from firebase
    Serial.println("FAN Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW);                                                  // make bultin led ON
    analogWrite(D0,800);
    digitalWrite(fanpin1, HIGH);                                                         // make external led ON
    digitalWrite(fanpin2, LOW);
  } 
  else if (fireStatus1 == "OFF") {                                                  // compare the input of led status received from firebase
    Serial.println("FAN Turned OFF");
    analogWrite(D0,100);
    digitalWrite(fanpin1, LOW);                                               // make bultin led OFF
    digitalWrite(fanpin2, LOW);                                                         // make external led OFF
  }
  else {
    Serial.println(fireStatus1);
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
  
}
