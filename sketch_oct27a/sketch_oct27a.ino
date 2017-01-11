// #include <SoftwareSerial.h>
//int arr[2];
//SoftwareSerial mySerial(9, 10);
int code;
int flag=1;
int i=0;
void setup()
{
  Serial.begin(9600); // Setting the baud rate of Software Serial Library
    //Setting the baud rate of Serial Monitor
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.println("System ready!!!");
  Serial.println("System starts with the door unlocked\n");
  Serial.println("Accessing Master card!!!");
   /*Serial.write("Accessing Master Card......");
  if(Serial.available()>0)
  {
    Serial.write("Master card accessed...This card will now be used");
    code=Serial.read();
  }*/
  
}

void Locking()
{
  digitalWrite(7,HIGH);
  delay(250);
  digitalWrite(7,LOW);
  delay(250);
}
void Unlocking()
{
  digitalWrite(8,HIGH);
  delay(250);
  digitalWrite(8,LOW);
  delay(250);
  
}
void loop()
{
  if(i==0)
  {
    if(Serial.available()>0)
    {
      code=Serial.read();
      
      Serial.write("Master card read...Memory refreshed\n");
      i=1;
    }
  }
  
 if(Serial.available()>0&&Serial.read()==code)
 {
  if(flag==0)
    {
      Unlocking();
      
      Serial.write("Access Granted...The door has been unlocked\n");
      flag=1;
    }
    else
    {
      Locking();
      
      Serial.write("The door has been locked!\n");
      flag=0;
    }
    
    
 }
}
