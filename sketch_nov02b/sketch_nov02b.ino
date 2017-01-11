void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.print("Hey there");
}

int x;
String str;

void loop() 
{
    if(Serial.available() > 0)
    {
        str = Serial.readStringUntil('\n');
        x = Serial.parseInt();
    }
    Serial.print(str);
}
