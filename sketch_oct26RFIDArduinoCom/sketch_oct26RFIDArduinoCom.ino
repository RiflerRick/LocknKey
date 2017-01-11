String msg;
char c;
//String ID;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial Ready");

}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0)
  {
     Serial.println("reading");
     c=Serial.read();
     msg+=c;  
  }
  Serial.println(msg);


}
