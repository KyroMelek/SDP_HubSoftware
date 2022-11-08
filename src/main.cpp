#include <WiFi.h>
#include <WiFiUdp.h>
#include <string>

// const char * ssid = "WhiteSky-Standard";
// const char * password = "9fg6cj5k";

const char *ssid = "iPhone 12 Pro";
const char *password = "SeniorDesignTeam08";

// const char * udpAddress = "10.23.141.78";
const char *udpAddress = "172.20.10.11";
const int udpPort = 5555;

unsigned int localPort = 1234; // local port to listen on

char packetBuffer[255];              // buffer to hold incoming packet
char ReplyBuffer[] = "acknowledged"; // a string to send back

WiFiUDP Udp;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi Failed");
    while (1)
    {
      delay(1000);
    }
  }
  Serial.print("UDP Listening on IP: ");
  Serial.println(WiFi.localIP());
  Udp.begin(localPort);
}

void loop()
{
  int packetSize = Udp.parsePacket();

  if (packetSize)
  {

    Serial.println();
    Serial.print("Received packet of size: ");
    Serial.print(packetSize);
    Serial.println();
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.print(Udp.remotePort());
    Serial.println();

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    // if (len > 0) {

    //   packetBuffer[len] = 0;

    // }

    Serial.println("Contents:");
    Serial.println(packetBuffer);
    char *message = new char[packetSize + 1];
    message = packetBuffer;
    message[packetSize] = '\0';

    std::string messageString(message, packetSize + 1);
    int pin = stoi(messageString);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), 5555);
    Udp.printf("acknowledged");
    Udp.endPacket();
  }
}
