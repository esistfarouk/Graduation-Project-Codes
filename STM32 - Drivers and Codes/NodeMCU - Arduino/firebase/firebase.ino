#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "temp-40404-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "IFCWCqA6tULq3dbg2N2IMosVwdDaUDQU8qz714Uq"
#define WIFI_SSID "Farouk"
#define WIFI_PASS "asdfghjkl"

#define POTENTIOMETER A0

int POTRead = 0;

char* code = "$GPGLL,3028.40872,N,03111.38769,E,205809.00,A,A*6E";
char latitude[3];
char latitude_fraction[8];
char longitude[4];
char longitude_fraction[8];
char latitude_direction;
char longitude_direction;
char hours[3];
char minutes[3];
char seconds[3];
char Time[9];
char valid_not_valid;
int latitude_counter = 0;
int latitude_fraction_counter = 0;
int longitude_counter = 0;
int longitude_fraction_counter = 0;
int hours_counter = 0;
int minutes_counter = 0;
int seconds_counter = 0;
int number_of_comas = 0;

void setup() {
  pinMode(POTENTIOMETER,INPUT);
  Serial.begin(9600);
  WiFi.disconnect();
  WiFi.begin(WIFI_SSID,WIFI_PASS);
  Serial.println("Connecting...");
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(50);
    Serial.print('.');
  }
  Serial.println("");
  Serial.print("Connected, Local IP is: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  /*Firebase.setString("IMOVE/Database/POT","HI");
  Firebase.setString("Variable/Value","HI");*/
  if(Firebase.failed())
  {
    Serial.println("Fisebase log sending failed");
    Serial.println(Firebase.error());
    return;
  }
  for(int i = 0; i< size_of_array(code); i++)
  {
      if(code[i]==',')
      {
          number_of_comas++;
      }
      if(number_of_comas==1)
      {
          if(code[i]!=','&& code[i]!='.')
          {
              if(latitude_counter<2)
              {
                  latitude[latitude_counter++]=code[i];
              }
              else
              {
                  latitude_fraction[latitude_fraction_counter++]=code[i];
              }
          }
      }
      if(number_of_comas==2)
      {
          if(code[i]!=',')
          {
              latitude_direction=code[i];
          }
      }
      if(number_of_comas==3)
      {
          if(code[i]!=',' && code[i]!='.')
          {
              if(longitude_counter<3)
              {
                  longitude[longitude_counter++]=code[i];
              }
              else
              {
                  longitude_fraction[longitude_fraction_counter++]=code[i];
              }
          }
      }
      if(number_of_comas==4)
      {
          if(code[i]!=',')
          {
              longitude_direction=code[i];
          }
      }
      if(number_of_comas==5)
      {
          if(code[i]!=',')
          {
              if(hours_counter<2)
              {
                  hours[hours_counter++]=code[i];
              }
              else if(minutes_counter<2)
              {
                  minutes[minutes_counter++]=code[i];
              }
              else if(seconds_counter<2)
              {
                  seconds[seconds_counter++]=code[i];
              }
          }
      }
  }
  latitude[latitude_counter]='\0';
  latitude_fraction[latitude_fraction_counter]='\0';
  longitude[longitude_counter]='\0';
  longitude_fraction[longitude_fraction_counter]='\0';
  hours[hours_counter]='\0';
  minutes[minutes_counter]='\0';
  seconds[seconds_counter]='\0';
  Time[0]=hours[0];
  Time[1]=hours[1];
  Time[2]=':';
  Time[3]=minutes[0];
  Time[4]=minutes[1];
  Time[5]=':';
  Time[6]=seconds[0];
  Time[7]=seconds[1];
  Time[8]='\0';
  if(size_of_array(latitude)==0||size_of_array(longitude)==0)
  {
      valid_not_valid = 'N'; //not valid
  }
  else
  {
      valid_not_valid = 'V'; //valid
  }
  /*printf("Latitude: %s \n",latitude);
  printf("Latitude fraction: %s \n",latitude_fraction);
  printf("Latitude Direction: %c \n",latitude_direction);
  printf("Longitude: %s \n",longitude);
  printf("Longitude fraction: %s \n",longitude_fraction);
  printf("Longitude direction: %c \n",longitude_direction);
  printf("Data: %c \n",valid_not_valid);
  
  printf("Lat: %f \n", latitude_value(latitude, latitude_fraction));
  printf("Long: %f \n", longitude_value(longitude, longitude_fraction));
  
  printf("time: %s:%s:%s", hours,minutes,seconds);*/
  
  
}

void loop() {
  int Temp = 33 + random(7);
  int heart = 65 + random(7);
  int oxygen = 95 + random(5);
  /*POTRead = analogRead(POTENTIOMETER);
  String Data = String(POTRead);
  Firebase.setString("IMOVE/Database/POT",Data);
  Firebase.setString("Variable/Value",Data);*/
  Firebase.setFloat("Wheelchair_test/test/LONG",longitude_value(longitude, longitude_fraction));
  Firebase.setFloat("Wheelchair_test/test/LAT",latitude_value(latitude, latitude_fraction));
  //Firebase.setChar("Wheelchair_test/test/VALID",valid_not_valid);
  Firebase.setString("Wheelchair_test/test/Time",Time);
  Firebase.setInt("Wheelchair_test/test/Temp",Temp);
  Firebase.setInt("Wheelchair_test/test/heart",heart);
  Firebase.setInt("Wheelchair_test/test/oxygen",oxygen);
  Serial.print("Temp: ");
  Serial.println(Temp);
  Serial.print("Heart: ");
  Serial.println(heart);
  Serial.print("Oxygen: ");
  Serial.println(oxygen);
  
  if(Firebase.failed())
  {
    Serial.println("Fisebase log sending failed");
    Serial.println(Firebase.error());
    return;
  }
  //Serial.println(POTRead);
  delay(1000);
}


int size_of_array(char* array_of_characters)
{
    int counter = 0;
    while(array_of_characters[counter]!='\0')
    {
        counter++;
    }
    return counter;
}
float latitude_value(char* latitude_number, char* latitude_fraction_number)
{
    if (size_of_array(latitude_number) == 0)
    return 0;
    int non_fraction = (latitude_number[0]-'0')*10+(latitude_number[1]-'0');
    float fraction = ((latitude_fraction_number[0]-'0')*1000000+(latitude_fraction_number[1]-'0')*100000+
    (latitude_fraction_number[2]-'0')*10000+(latitude_fraction_number[3]-'0')*1000+
    (latitude_fraction_number[4]-'0')*100+(latitude_fraction_number[5]-'0')*10+(latitude_fraction_number[6]-'0'))/6000000.0;
    return (non_fraction+fraction);
}
float longitude_value(char* longitude_number, char* longitude_fraction_number)
{
    if (size_of_array(longitude_number) == 0)
    return 0;
    int non_fraction = (longitude_number[0]-'0')*100+(longitude_number[1]-'0')*10+(longitude_number[2]-'0');
    float fraction = ((longitude_fraction_number[0]-'0')*1000000+(longitude_fraction_number[1]-'0')*100000+
    (longitude_fraction_number[2]-'0')*10000+(longitude_fraction_number[3]-'0')*1000+
    (longitude_fraction_number[4]-'0')*100+(longitude_fraction_number[5]-'0')*10+(longitude_fraction_number[6]-'0'))/6000000.0;
    return (non_fraction+fraction);
}
