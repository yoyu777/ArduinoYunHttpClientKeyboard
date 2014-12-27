/*
  Yún HTTP Client

 This example for the Arduino Yún shows how create a basic
 HTTP client that connects to the internet and downloads
 content. In this case, you'll connect to the Arduino
 website and download a version of the logo as ASCII text.

 created by Tom igoe
 May 2013

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/HttpClient

 */

#include <Bridge.h>
#include <HttpClient.h>
Process shell;
int pushButton = 2;
int pushButton2 = 3;
int speed=100;
int toner = 8;
void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  pinMode(pushButton, INPUT);
  pinMode(toner, OUTPUT);
  Serial.begin(9600);

  //while (!Serial); // wait for a serial connection
}

void loop() {
  // Initialize the client library
  HttpClient client;

  // Make a HTTP request:
  //  client.get("http://arduino.cc/asciilogo.txt");
  client.get("http://192.168.1.70:3000/getSignal");
  // if there are incoming bytes available
  // from the server, read the stream and print them:
  float sensorValue = analogRead(A0);
  while (client.available()) {
    String command = client.readStringUntil('/');
    Serial.println( command.toFloat()*(sensorValue/1000));
    tone(toner, command.toInt()*(sensorValue/1000), speed);
  }
  Serial.flush();
  int buttonState = digitalRead(pushButton);
  int buttonState2 = digitalRead(pushButton2);
  if ( buttonState == 1 ) {
    postFunction(300);
  }
  if ( buttonState2 == 1 ) {
    postFunction(500);
  }
  //Serial.println(buttonState);
  delay(100);

}

 void postFunction(float pitch) {
    shell.runShellCommand("curl --data \"number="+String(pitch*100)+"\" http://192.168.1.70:3000/postSignal");
  }


