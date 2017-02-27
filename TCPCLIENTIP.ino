

#include <ESP8266WiFi.h>

char ssid[] = "RES_Research"; //  your network SSID (name)
char pass[] = "aruba567";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

void printWiFiStatus();
// use the numeric IP instead of the name for the server:
IPAddress server(172, 16, 16, 150); // numeric IP for Google (no DNS)

char mes2[200];
char key2[100];
char key[] = "kgdjgdlGAJJ";
int j = 0, k = 0, len1 = 0,n=0;
char mes1[200];
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }




  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, pass);

  // wait 10 seconds for connection:
  delay(10000);

  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
     client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
     client.println("Connection: close");
    client.println();
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    mes1[n]=c;
    n++;
  }
  n=0;
  // if the server's disconnected, stop the client:
 
  if (!client.connected()) {
     decodeMsg();
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}
void decodeMsg()
{
  k=0;j=0;
  len1 = strlen(key);
    Serial.println(mes1);
  for (int i = 0; i <= 300; i++)
  {
    if (i % 2 == 0)
    {
      mes2[j] = mes1[i];
      j++;
    }

    else
    {
      key2[k] = mes1[i];
      k++;
    }

  }
  Serial.println("after decoded");
  Serial.println("mes2");
  Serial.println(mes2);
  Serial.println("key2");
  Serial.println(key2);
  if (!strncmp(key2, key, len1))
  {
    Serial.println("in if condtion");
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
