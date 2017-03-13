#include <ESP8266WiFi.h>


//const char *ssid = "SmartGas";
//const char *password = "redsiliconlabs";

char ssid[] = "RES_Research";      // your network SSID (name)
char password[] = "aruba567";          // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

IPAddress ip(172, 16, 16, 106);
IPAddress gateway(172, 16, 16, 16);
IPAddress subnet(255, 255, 0, 0);

WiFiServer server(80);
void printWiFiStatus() ;

//char key[50] = "kgdjgdlGAJJ";
char mes[100];
int j = 0, k = 0, l = 0, i = 0;
char mes1[200];
char ch;
int len1, len2;

void setup() {
  Serial.begin(9600);
    WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  server.begin();
  printWiFiStatus();
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //client.print("<pre>RedSiliconLabs");
          //client.print("GasSensor1=100</pre>");
          client.print("GasValue1:<br><input type=\"/text\"\" name=\"/lastname\"\" value=" + String(len1) + "><br>");
           client.print("GasValue2:<br><input type=\"/text\"\" name=\"/lastname\"\" value=" + String(len1) + "><br>");
          
          client.println("</html>");
          len1++;
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}


void printWiFiStatus() {
  IPAddress ip =  WiFi.softAPIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}


