/*
 * NodeMCU/ESP8266 act as AP (Access Point) and simplest Web Server
 * to control GPIO (on-board LED)
 * Connect to AP "arduino-er", password = "password"
 * Open browser, visit 192.168.4.1
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include "Wire.h"
#define DS1307_I2C_ADDRESS 0x68 // the I2C address of Tiny RTC
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
return ( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
return ( (val/16*10) + (val%16) );
}

const char *ssid = "PompeGradina";
const char *password = "p0mp3!";
int stateLED = LOW;
int stateLED1 = LOW;
int stateLED2 = LOW;
int stateLED3 = LOW;
int ledPin = D5; 
int ledPin1 = D6; 
int ledPin2 = D7; 
int ledPin3 = D8; 

ESP8266WebServer server(80);

// Function to set the currnt time, change the second&minute&hour to the right time
void setDateDs1307()
{
second =40;
minute = 2;
hour = 16;
dayOfWeek = 7;
dayOfMonth =9;
month =4;
year= 17;
Wire.beginTransmission(DS1307_I2C_ADDRESS);
Wire.write(decToBcd(0));
Wire.write(decToBcd(second)); // 0 to bit 7 starts the clock
Wire.write(decToBcd(minute));
Wire.write(decToBcd(hour)); // If you want 12 hour am/pm you need to set
// bit 6 (also need to change readDateDs1307)
Wire.write(decToBcd(dayOfWeek));
Wire.write(decToBcd(dayOfMonth));
Wire.write(decToBcd(month));
Wire.write(decToBcd(year));
Wire.endTransmission();
}
// Function to gets the date and time from the ds1307 and prints result
void getDateDs1307()
{
// Reset the register pointer
Wire.beginTransmission(DS1307_I2C_ADDRESS);
Wire.write(decToBcd(0));
Wire.endTransmission();
Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
second = bcdToDec(Wire.read() & 0x7f);
minute = bcdToDec(Wire.read());
hour = bcdToDec(Wire.read() & 0x3f); // Need to change this if 12 hour am/pm
dayOfWeek = bcdToDec(Wire.read());
dayOfMonth = bcdToDec(Wire.read());
month = bcdToDec(Wire.read());
year = bcdToDec(Wire.read());
Serial.print(hour, DEC);
Serial.print(":");
Serial.print(minute, DEC);
Serial.print(":");
Serial.print(second, DEC);
Serial.print(" ");
Serial.print(month, DEC);
Serial.print("/");
Serial.print(dayOfMonth, DEC);
Serial.print("/");
Serial.print(year,DEC);
Serial.print(" ");
Serial.println();
//Serial.print("Day of week:");

}

void handleRoot() {
    response();
}

void handleLedOn() {
  stateLED = LOW;
  digitalWrite(LED_BUILTIN, stateLED);
  response();
}

void handleLedOff() {
  stateLED = HIGH;
  digitalWrite(LED_BUILTIN, stateLED);
  response();
}

void pornireFurtun() {
  stateLED = LOW;
  digitalWrite(ledPin, stateLED);
  response();
}

void oprireFurtun() {
  stateLED = HIGH;
  digitalWrite(ledPin, stateLED);
  response();
}

void pornireFurtun1() {
  stateLED = LOW;
  digitalWrite(ledPin1, stateLED1);
  response();
}

void oprireFurtun1() {
  stateLED = HIGH;
  digitalWrite(ledPin1, stateLED1);
  response();
}

void pornireFurtun2() {
  stateLED = LOW;
  digitalWrite(ledPin2, stateLED2);
  response();
}

void oprireFurtun2() {
  stateLED = HIGH;
  digitalWrite(ledPin2, stateLED2);
  response();
}

void pornireFurtun3() {
  stateLED = LOW;
  digitalWrite(ledPin3, stateLED3);
  response();
}

void oprireFurtun3() {
  stateLED = HIGH;
  digitalWrite(ledPin3, stateLED3);
  response();
}


const String HtmlHtml = "<html><head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>Pompe Gradina</h1><br/>\n";
const String HtmlTime = "<h1>" + String(hour, DEC)+":"+String(minute, DEC)+":"+String(second, DEC)+"</h1><br/>\n";
const String HtmlLedStateLow = "<big>LED is now <b>ON</b></big><br/>\n";
const String HtmlLedStateHigh = "<big>LED is now <b>OFF</b></big><br/>\n";
const String HtmlR1StateLow = "<big>Furtun: <b>ON</b></big><br/>\n";
const String HtmlR1StateHigh = "<big>Furtun: <b>OFF</b></big><br/>\n";
const String HtmlButtons = 
    "<a href=\"LEDOn\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
    "<a href=\"LEDOff\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>"
    
    "<a href=\"R1On\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
    "<a href=\"R1Off\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>"

    "<a href=\"R2On\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
    "<a href=\"R2Off\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>";


void response(){
  getDateDs1307();
  const String HtmlTime = "<h1>" + String(hour, DEC)+":"+String(minute, DEC)+":"+String(second, DEC)+"</h1><br/>\n";
  String htmlRes = HtmlHtml + HtmlTitle + HtmlTime;
  if(stateLED == LOW){
    htmlRes += HtmlLedStateLow;
  }else{
    htmlRes += HtmlLedStateHigh;
  }
  
  if(stateLED1 == LOW){
    htmlRes += HtmlR1StateLow;
  }else{
    htmlRes += HtmlR1StateHigh;
  }
  
  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void setup() {
    delay(1000);
  Wire.begin();
    Serial.begin(9600);
    Serial.println();
   // setDateDs1307(); //Set current time;
    getDateDs1307();//get the time data from tiny RTC
    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/LEDOn", handleLedOn);
    server.on("/LEDOff", handleLedOff);
    server.on("/R1On", pornireFurtun);
    server.on("/R1Off", oprireFurtun);
    server.on("/R2On", pornireFurtun1);
    server.on("/R2Off", oprireFurtun1);
    server.begin();
    Serial.println("HTTP server beginned");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, stateLED);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, stateLED);
    pinMode(ledPin1, OUTPUT);
    digitalWrite(ledPin1, stateLED1);
}

void loop() {
    server.handleClient();
    getDateDs1307();//get the time data from tiny RTC
}