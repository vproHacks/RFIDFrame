#include <ESP8266WiFi.h>
#include <SPI.h>
#include "MFRC522.h"
/* wiring the MFRC522 to ESP8266 (ESP-12)
RST     = GPIO5
SDA(SS) = GPIO4 
MOSI    = GPIO13
MISO    = GPIO12
SCK     = GPIO14
GND     = GND
3.3V    = 3.3V
*/
#define RST_PIN  5 
#define SS_PIN  4  

const char *ssid =  "ssid-name";     // change according to your Network, no longer than 32 chars
const char *pass =  "password-value"; // change according to your Network
String msg;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
String header;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);    // Initialize serial communications
  delay(250);
  Serial.println(F("Booting...."));
  
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522
  
  WiFi.begin(ssid, pass);
  
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected"));
  }

 Serial.println("");
 Serial.println("WiFi connected.");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 server.begin();
  
 Serial.println(F("Ready!"));
  Serial.println(F("==============================================")); 
Serial.println(F("Scan for Card and print UID:"));
}

unsigned long getID(){
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return -1;
  }
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }

void loop() {

if(mfrc522.PICC_IsNewCardPresent()) {
  unsigned long uid = getID();
  if(uid != -1){
    Serial.print("Card detected, UID: "); Serial.println(uid);
  }
  WiFiClient client = server.available();
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
           
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
            client.println("<h4>Card UIDs</h4>");
            client.print("<h5 id=\"uidValue\">");
            client.print(uid);
            client.print("</h5>");
            client.println();
            client.println("</body>");
  client.println("</html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } 
          else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
          
        }
      }
    }
  } 
 }
}
