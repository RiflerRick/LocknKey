String str;
void setup()
{
  Serial.begin(9600);
  Serial.println("System ready!!!");
}
void loop()
{
  CardRead();
  
}
void CardRead()
{
  if(Serial.available())
  {
    str=Serial.readString();
    Serial.print("Card 10 digit code:");
    Serial.println(str);
  }
}

