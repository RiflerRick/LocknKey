String ID;
String msg;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial Ready");
  
}
char c;

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0)
  {
    c=Serial.read();
    msg+=c;
    Serial.println("Message is\n");
    Serial.println(msg);
    Serial.println("The length of the message is:\n");
    Serial.println(msg.length());
    
  }
}
