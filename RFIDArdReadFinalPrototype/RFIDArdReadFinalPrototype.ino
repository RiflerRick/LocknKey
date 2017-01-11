String str;
String master="08009A23BC";
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
    str=Serial.readString();//so understand that the readString function is used mainly for the purpose of reading the 10 digit code that we are trying to access.
    Serial.print("Card 10 digit code:\n");
    int len=str.length();
    Serial.println(str);
    Serial.println("length of the string is:");
    Serial.println(len);
    String s=str.substring(7,11);
    Serial.println(s);
    Serial.println(master.substring(6,10));
    if(s.equals(master.substring(6,10)))
    Serial.println("true");
    else
    Serial.println("false");
  }
}

