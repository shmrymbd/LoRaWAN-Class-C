# LoRaWAN-Class-C
Library and codes for nodes implementing LoRaWAN Class C

The library Arduino-MyLoRaID.zip in this repository is based on work from : https://github.com/antaresdocumentation/lorawan-loraid \
I modified bits and pieces in the library to suit Malaysia AS1 frequencies as well as some minor changes at some of the places.

I ran the code on Arduino UNO + Dragino LoRa Shield + Relay Shield V3.0. 

Dragino LoRa Shield : https://wzper.my/index.php?id_product=90&controller=product \
Relay Shield V3.0 : https://my.cytron.io/p-relay-shield-v3.0?r=1

As i am interested to work on Class C in order to control actuator or Relay using LoRaWAN, we will focus only on Class C here. \
For normal Class A, you can refer to my other repository meant for lmic-as923.

This library is not based on lmic by the way.  It was originally written by Ideetron BV. It works pretty good. \  
The only feature is missing is ADR functionality.  But it is just fine to make your node works.

As TTN is currently does not support Class C yet, i am using Gotthardp LoRaWAN Server for my work - https://github.com/gotthardp/lorawan-server \
I installed the lorawan server on my Raspberry Pi 3B+.  It works pretty good.

In my setup, i am using Dragino LG308 Multi-Channel Gateway which talks to the lorawan server to get the data processed.

LoRaWAN Gateway : https://wzper.my/index.php?id_product=105&controller=product

In the same Raspberry Pi, i also installed Mosquitto MQTT broker. \  
Then, i connect the lorawan server with the MQTT broker at the "connector" section of the lorawan server.

To receive and send data from/to the node, i am using Node-Red on my personal computer. \
Incoming data from node can be seen on Node-Red. \
We can also control the Relay from within the Node-Red flow.

Some settings on the Lorawan server must be done in order to make things work perfectly. \
Here, you can find the screenshot of my setting. \
Also, the flow for my Node-Red for your convenience.


