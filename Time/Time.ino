#include<Time.h>
int sec;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
Serial.println("System ready!!!");
}

void loop() {
  // put your main code here, to run repeatedly:
   // Store the current time in time 
                    //  variable t 
  //setTime(t);
  
  //time_t t = now();
  
  if(Serial.available())
  {
     sec=Serial.parseInt(); 
     setTime(20,59,sec,4,11,2015);
  }
  //setTime(hr,min,sec,day,month,yr); 
 if(timeStatus() == timeNotSet) 
    Serial.println("waiting for sync message");
  else  {
Serial.println("Second now is:");
Serial.println(second()); }
delay(1000);
}
