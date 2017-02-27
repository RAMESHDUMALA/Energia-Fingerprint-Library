#include <ESP8266WiFi.h>


char ssid[] = "RES_Research";      // your network SSID (name)
char pass[] = "aruba567";          // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

IPAddress ip(172, 16, 16, 150);
IPAddress gateway(172, 16, 16, 16);
IPAddress subnet(255, 255, 0, 0);


WiFiServer server(80);
void printWiFiStatus() ;

char key[50] = "kgdjgdlGAJJ";
char mes[100];
int j = 0, k = 0, l = 0, i = 0;
char mes1[200];
char ch;
int len1, len2;

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);

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
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("<br>");
          msgSend();
          client.print(mes1);
          client.println("<br />");
          client.println("</html>");
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
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void msgSend()
{
  Serial.println("please enter the data");
  memset(mes1, 0, 200);
  memset(mes, 0, 100);
  ch = '0';
  i = 0, l = 0, j = 0, k = 0;
  while (ch != '\n')
  {
    if (Serial.available() > 0) {

      ch = Serial.read(); // read the incoming byte:
      mes[l] = ch;
      l++;
    }

  }
  len1 = strlen(mes);
  len2 = strlen(key);
  len1 = 2 * len1 - 4;
  Serial.println(mes);
  while (1)
  {

    if (i % 2 == 0)
    {
      mes1[i] = mes[j];
      j++;
      if (i == len1)
        break;
    }

    else
    {
      if (i == len1)
        break;
      else if (k == len2)
      {
        k = 0;
      }
      mes1[i] = key[k];
      k++;

    }
    i++;

  }

}
