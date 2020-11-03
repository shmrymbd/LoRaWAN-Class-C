/****************************************************************************************************
*  Revision History
*  30 October 2020     Zaki      Initial Creation for sending bytes
*                                
*
*****************************************************************************************************/
#include <loraid.h>

long interval = 10000;    // 10s interval to send message
long previousMillis = 0;  // will store last time message sent

void setup() {
  
  Serial.begin(115200);
  
  pinMode(5,OUTPUT); //pin 5 at the Relay Shield V3.0 is meant for Relay3 on the board
  
  // Setup loraid access
  lora.init();

  // Set LoRaWAN Class
  lora.setDeviceClass(CLASS_C);

  // Set Data Rate for Tx. As for Rx, it is set in Library for SF10, 923.2MHz
  lora.setDataRate(5);  //SF7
  
  // Put Key and DevAddress here
  lora.setNwkAccessKey("F56B4BBA9BA6F3F7497376FD889D6B0C");
  lora.setAppAccessKey("A57DC52E1DA163D5F9C4AD6B048E9610");
  lora.setDeviceId("260119E7");
}

void loop() {
  
  static uint8_t message[3]; //this is for sending hex value
  
  char outBuf[50];
  
  int recvStatus = 0;
  String StringOut = "";
  unsigned char i;
  unsigned char UpperNibble[50];
  unsigned char LowerNibble[50];
  
  unsigned long currentMillis = millis();

  // Transmission of data is done here, example here is just to send 
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis; 

    //this can be your sensor value in hex
    message[0] = 0x12;
    message[1] = 0x23;
    message[2] = 0x25;
    Serial.println("Transmitting data.....");
    lora.sendToGateway(message, sizeof(message), 0);

    Serial.println();
  }

  // Check Lora RX
  lora.update();

  recvStatus = lora.readData(outBuf);
  
  if(recvStatus) 
  {          
    StringOut = String(outBuf);  //convert to String for easy manipulation
    
    for(i = 0; i < StringOut.length(); i++)  //read every nibbles
    {
        UpperNibble[i] = (outBuf[i] >> 4) & 0x0F;
        LowerNibble[i] = outBuf[i] & 0x0F;   
    }

    //Data from Node-Red is actually sent out 31303145, so i want to pick the 3rd byte for action
    if(UpperNibble[3] == 4 && LowerNibble[3] == 5)  //If the 3rd byte is 0x45
    {
        Serial.println("Data Received : Relay3 ON");
        digitalWrite(5,HIGH);
        delay(2000);
        digitalWrite(5,LOW);
        delay(2000);
        Serial.println("Relay3 is hardcoded to OFF after 2 seconds");
        Serial.println();
    }    
  }
}


