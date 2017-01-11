/* 
Modified code to work with Arduino 1.0.1
Credits to Petushka, http://www.instructables.com/member/Petushka/ 
*/

/*
The Arduino Software has a built in support for serial communication on pins 0 and 1
The native support on pins 0 and 1 happens via a universal hardware called UART(Universal Asynchronus Receiver TRansmitter)
This hardware enables the Arduino device to receive serial data even while performing other tasks
The SoftwareSerial library has been developed to allow serial communication on other digital pins of the Arduino...

*/

#include <SoftwareSerial.h>

#define ADD_TAG_CODE "210014DFE309"  //change this ID with your own card TAG
#define DEL_TAG_CODE "210014E2BD6A"  //change this ID with your own card TAG

SoftwareSerial rfid = SoftwareSerial(5, 6);//object rfid of type SoftwareSerial is created.
/*
SoftwareSerial.h is the library that comes with arduino used for transimitting and receiving serial communication signals. 
SoftwareSerial(rxPin, txPin, inverse_Logic)
rxPin - receiver pin number.(pin number to receive serial data)
txPin- transmitter pin number(pin number ti transmit serial data)
inverseLogic- as the name suggests, if used the logic on which the ckt functions becomes negative logic.
*/

String msg;
String ID ;  //string to store allowed cards

void setup()  
{
  Serial.begin(9600);//9600 is the baud rate or 9600 bits per second is the data rate of the communication.
  Serial.println("Serial Ready");
  
  /*
  Digital pins 0 and 1 are used for reception and transmission of serial signals in digital form.
  Now the idea is that Serial is used for the serial ports already available for serial data comm.
  SoftwareSerial on the other hand is used for using other pins for serial communication.
  Serial.begin
  */
  rfid.begin(9600);
  Serial.println("RFID Ready");
}

char c;

void loop(){
  /*
  SoftwareSerial: available()-Gets the number of bytes(character ) available for reading from a software serial port.
  This data has already arrived and is stored in the serial receive buffer.
  */
  while(rfid.available()>0){
    Serial.println ("reading");
    c=rfid.read(); 
    /*
     * SoftwareSerial: read()- return a character that was recieved on the RX pin of the software serial  port- (the digital port that is configured to be used for
     * serial data reception using ther SoftwareSerial class.)
    */
    msg += c;
    
    Serial.println(msg);  
    Serial.println(msg.length());
  }
  msg=msg.substring(1,13);
  if(msg.indexOf(ADD_TAG_CODE)>=0) add(); 
  else if(msg.indexOf(DEL_TAG_CODE)>=0) del();  
  else if(msg.length()>10) verifica();
  msg="";
  
}

void add(){
  Serial.print("What TAG do you wanna grant access?: ");
  msg="";
  while(msg.length()<13){
    while(rfid.available()>0){
      c=rfid.read(); 
      msg += c;
    }
  }
  if(ID.indexOf(msg)>=0) {
    /*
     * So if the index of the new message is not 0 or greater it means they are not the same.
     * Remember we are already granting access for allowed cards.
     * 
    */
    Serial.println("\nAccess already granted for this card.");
    msg="";
  }
  else{
    Serial.print("Card: ");
    Serial.println(msg); 
    ID += msg;
    ID += ",";
    //Serial.print("ID: ");
   // Serial.println(ID);
    msg="";
    Serial.println("Access granted for this card.");
  }

}

void del(){
  msg="";
  Serial.print("What TAG do you wanna deny access?: ");
  while(msg.length()<13){
    while(rfid.available()>0){
      c=rfid.read(); 
      msg += c;
    }
  }
  msg=msg.substring(1,13);
  if(ID.indexOf(msg)>=0){
    Serial.println(msg);
    Serial.println("TAG found. Access for this card denied.");
    //ID.replace(card,"");
    int pos=ID.indexOf(msg);
    msg="";
    msg += ID.substring(0,pos);
    msg += ID.substring(pos+15,ID.length());
    ID="";
    ID += msg;
    //Serial.print("ID: ");
    //Serial.println(ID);
  } else Serial.println("\nTAG not found or already denied");
  msg="";
}

void verifica(){
    msg=msg.substring(1,13);
    if(ID.indexOf(msg)>=0) Serial.println("Access granted.");
    
    else Serial.println("Access denied.");
}

