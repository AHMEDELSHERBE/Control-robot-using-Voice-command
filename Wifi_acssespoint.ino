#include <ESP8266WiFi.h>
 
const char* ssid = "we21";//type your ssid
const char* password = "95603081";//type your password
 
int ledPin_1 = D2; // GPIO2 of ESP8266
int ledPin_2 = D3; // GPIO2 of ESP8266
int ledPin_3 = D4; // GPIO2 of ESP8266
int ledPin_4 = D5; // GPIO2 of ESP8266
WiFiServer server(80);//Service Port
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin_1, OUTPUT);
  pinMode(ledPin_2, OUTPUT);
  pinMode(ledPin_3, OUTPUT);
  pinMode(ledPin_4, OUTPUT);
    //digitalWrite(ledPin, LOW);
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/right") != -1) {
    digitalWrite(ledPin_1, HIGH);
    digitalWrite(ledPin_2, HIGH);
    digitalWrite(ledPin_3, HIGH);
    digitalWrite(ledPin_4, HIGH);
        
    value = LOW;
  } 
  if (request.indexOf("http://192.168.1.5/off") != -1){
    digitalWrite(ledPin_2, HIGH);
    digitalWrite(ledPin_1, LOW);
     digitalWrite(ledPin_3, LOW);
    
    value = HIGH;
  }
     if (request.indexOf("/stop") != -1)
  {
    
    value = LOW;
  }

  //Set ledPin according to the request
  //digitalWrite(ledPin, value);
   
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   
  client.print("Led pin is now: ");
   
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here turn the LED on pin 2 OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
