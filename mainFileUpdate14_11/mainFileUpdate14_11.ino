/*
 * The features that we will include in the project are:
 * 1. There will be 3 cards that we will be dealing with in the first place
 * the Master Card.(mas)(fixed in the ccode itself)
 * MultipurposeCard1(mc1)
 * MultipurposeCard2(mc2)
 * (cards are tags)
 * The initialization of the system has to be done using the master card:
 * Once the master card is recognized, all we have to do is go for either of 2 options:
 * 1. Single user system
 * 2. Multi user System.
 * In case of a single user system, one of the 2 cards will be used to select the system.
 * In case of a multi user System, the other card will be used to select the system.
 * 
 * Single User System
 * Once the single user system is selected, the system will prompt the user to enter the card that will be used for access...
 * After the card selection, the system is now ready...
 * 
 * Multi User System:
 * For Multiple users, the system will prompt for available cards that will be necessary for access to the system.
 * Once the cards are registered in the system, the system is now ready...
 * 
 * Feature:e-Registration will be used to register the date and time of the cards that will be allowed access in the system.
 * 
 * e-Registration is the only thing that remains to be done...
 * 
 * Feature:SleepGuard-SleepGuard is a system where we can set a time(sleeptime) when the user wants absolutely no access to the system,
 * If somebody tries to gain access using either of the cards mc1 or mc2, the cards will be registered(no access will be granted)
 * and when the sleeptime is over and the first card is read, an alarm will ring prompting the user to check the system... 
 * Although other cards will not be allowed during sleeptime, master card will have full control...
 * 
 * Future aspirations:
 * 1. Instead of an alarm for SleepGuard, whenever a card is registered during sleeptime a phonecall in the form of an alarm will be made to the user
 * of that card that it is right now in unauthorised hands...
 */
 #include<Time.h>
 String master="08009A23BC";//this string remains unchanged throughout the code...
 String mas=master.substring(6,10);
 String Card1="08009A2903";
 String mc1=Card1.substring(6,10);
 String Card2="08009A24FA";
 String mc2=Card2.substring(6,10);
 String singleUser,str;
 int flag=1;
 int check,key=1,hr,minutes,sleepflag=0,sleepactivate=0;
void setup() {
  
  Serial.begin(9600);//the baud rate is set to 9600 bps.
  Serial.println("Loading UI...Done!!!");
  Serial.println("Waiting for Initialization...");
  Serial.println("Please use your master card to initialize bootloader...");
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);

}
int SystemInitialization()
{
  key=1;
  sleepactivate=0;
  while(true){
  if(Serial.available())
  {
    //Serial.println("SystemInitialization function");
    //Serial.println("");
    str=Serial.readString();
    
    str=str.substring(7,11);
    /*Serial.println("str string:"+str);
    Serial.println("master string:"+mas);*/
    if(str.equals(mas))
    {
      Serial.println("For single user system, use card 1:");
      Serial.println("For multi user system use card 2:");
      while(true)
      {
      if(Serial.available())
      {
        str=Serial.readString();
        str=str.substring(7,11);
        if(str.equals(mc1))
        {
          Serial.println("Single user System activated...");
          Serial.println("Please enter the card that will be used for access!!!");
          while(true){
          if(Serial.available())
          {
            str=Serial.readString();
            str=str.substring(7,11);
            if((str).equals(mas)){
            Serial.println("Master card cannot be used for access explicitly...");continue;}
            else
            {singleUser=str;break;}
            
          }}
          Serial.println("System ready...");
          
          check =1;
          break;
          
        }
        else if(str.equals(mc2))
        {
          Serial.println("Multiple user System activated...");
          Serial.println("2 cards registered by default...System ready!!!");
          check = 2;
          break;
        }
        else
        {
          Serial.println("Unrecognized card!!!");
          break;
        }
      }
      }
    }
    Serial.println("Do you want to use SleepGuard Y: Card1, N:Card2");
    while(true){
    if(Serial.available()){
      str=Serial.readString();
      str=str.substring(7,11);
      if(str.equals(mc1))
      {SleepGuard();
      break;}
      else{
        Serial.println("Yeah you got that right, you are cautious about ur belongings right!!!");
        Serial.println("System ready!!!");
      break;}
    }}
    break;
  }}
}
void SleepGuard()
{
  Serial.println("This technology allows you to deny access to anybody between 12 midnight to 6 am in the morning...");
  /*Serial.println("Please enter the current time in hours ");
  hr=Serial.parseInt();
  Serial.println("Please enter the current time in minutes");
  minutes=Serial.parseInt();*/
  setTime(23,59,0,1,1,2016);
 //This function will merely be used for initializatio of the time set in the arduino...
 sleepactivate=1;
 Serial.println("System Ready!!!");
}
void e_Registration()
{
  
}
void Single()
{
  while(true){
  if(Serial.available())
  {
    str=Serial.readString();
    str=str.substring(7,11);
    if(str.equals(singleUser))
    {
      if(hour()>=0&&hour()<=6&&sleepactivate==1)
      {sleepflag=1;break;}
      Serial.println("Access Granted");
      /*Serial.print("Time :");
      Serial.print(hour());
      Serial.print(":");
      Serial.println(minute());*/
      Toggle();
      break;
    }
    else
    {
      if(str.equals(mas))
      ReInitialization();
      Serial.println("Acess denied...Use the correct tag!!!");
      continue;
    }
  }}
  if(sleepflag==1)
  {
    hr=hour();
    minutes=minute();
    Serial.println("Cannot allow access at this hour");
    sleepflag=0;
    
  }
}
void Multiple()
{
  while(true){
  if(Serial.available())
  {
    str=Serial.readString();
    str=str.substring(7,11);
    
    if(str.equals(mc1)||str.equals(mc2))
    {
      if(hour()>=0&&hour()<=6&&sleepactivate==1)
      {sleepflag=1;break;}
      Serial.println("Access Granted");
      /*Serial.print("Time :");
      Serial.print(hour());
      Serial.print(":");
      Serial.println(minute());*/
      Toggle();
      break;
    }
    else
    {
      if(str.equals(mas))
      ReInitialization();
      Serial.println("Acess denied...Use the correct tag!!!");
      continue;
    }
  }}
  if(sleepflag==1)
  {
    hr=hour();
    minutes=minute();
    sleepflag=0;
    Serial.println("Cannot acccess at this hour");
  }
}
void Toggle()
{
  if(key==1)
  {
    digitalWrite(7,HIGH);
    delay(1500);//first unlocking...
    digitalWrite(7,LOW);
    key=0;
  }
  else
  {
    digitalWrite(8,HIGH);
    delay(1500);
    digitalWrite(8,LOW);
    key=1;
  }
  
  
  
}
void ReInitialization()
{
  Serial.println("Reinitializing system....Done");
  SystemInitialization();
}
void loop() {
  // put your main code here, to run repeatedly:
  if(flag==1)
  {
    SystemInitialization();
    flag=0;
  }
  else
  {
    if(check==1)
    {
      Single();
    }
    else if(check==2)
    {
      Multiple();
    }
  
  }

}
