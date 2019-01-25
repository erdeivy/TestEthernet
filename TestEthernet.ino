#include <Dhcp.h>
#include <EthernetClient.h>
#include <EthernetUdp.h>
#include <Dns.h>
#include <EthernetServer.h>
#include <Ethernet.h>
#include <SPI.h>

#include <PubSubClient.h>
// IP del servidor
IPAddress mqtt_server(10,11,112,45);
// Topic con el que trabajamos
const char* topicName = "test";


byte mac[] = {0x90,0xA2,0xDA,0x00,0x69,0x7C};
EthernetClient client;
PubSubClient mqttClient(client);

void setup() {
   Serial.begin(9600);
   while (!Serial){
  }

      if (Ethernet.begin(mac) == 0) //Si devuelve error
   {       
    Serial.println("No ha sido posible configurar Ethernet por DHCP");
    while (true); // No sigas,....
   }

   Serial.print("Mi direccion IP es: ");
for (byte B = 0; B < 4; B++)   
   {
       Serial.print(Ethernet.localIP()[B], DEC);
       Serial.print(".");
    }
 Serial.println();


   mqttClient.setServer(mqtt_server, 1883);

}

void loop() {
if (!mqttClient.connected()) {
    Serial.print("Connecting ...\n");
    mqttClient.connect("arduinoClient", "user", "prueba01");
  }
  else {
    Serial.print("Sending...");
    // Envio
    int published = mqttClient.publish("amq.topic", "{\"title\":\"the lord of the rings\"}");
    Serial.println(published);
  }
  // Tiempo entre envios (en ms)
  delay(5000);

}
