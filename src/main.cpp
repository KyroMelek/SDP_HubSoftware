#include "WiFi.h"
#include "AsyncUDP.h"
#include <WiFiUdp.h>
#include <string>

// const char *ssid = "WhiteSky-Standard";
// const char *password = "9fg6cj5k";

const char *ssid = "iPhone 12 Pro";
const char *password = "SeniorDesignTeam08";

// const char * udpAddress = "10.23.141.78";
// const char *udpAddress = "172.20.10.11";
const int udpPort = 5555;

WiFiUDP udpSend;

AsyncUDP udp;

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
  if (udp.listen(1234))
  {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    udp.onPacket([](AsyncUDPPacket packet)
                 {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();

            char* message = new char[packet.length()+1];
            message = (char *)packet.data(); 
            message[packet.length()] = '\0';   

            std::string messageString(message, packet.length()+1);
            int pin = stoi(messageString);
            pinMode(pin, OUTPUT);
            digitalWrite(pin, HIGH);
            //reply to the client
            udpSend.beginPacket(packet.remoteIP(),udpPort);
            udpSend.printf("Hello from ESP32 ");
            udpSend.endPacket();
            packet.printf("Got %u bytes of data", packet.length()); });
  }
}

void loop()
{
  delay(1000);
  // Send broadcast
  udp.broadcast("Anyone here?");
}
