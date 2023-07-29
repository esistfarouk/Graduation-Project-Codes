#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(2, 3); // RX, TX pins for the GPS module

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  if (gpsSerial.available()) {
    String line = gpsSerial.readStringUntil('\r'); // read a line from the GPS module
    Serial.print(line);
    if (line.startsWith("$GPRMC")) { // check if the line contains the recommended minimum data for GPS
      int commaIndex = 0;
      for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
          commaIndex++;
          if (commaIndex == 2) {
            String valid = line.substring(i+1, i+2); // extract valid flag (A for valid, V for invalid)
            if (valid == "A") { // check if the GPS receiver has a fix
              float lat = line.substring(i+3, i+12).toFloat(); // extract latitude in degrees
              String latDir = line.substring(i+13, i+14); // extract latitude direction (N or S)
              float lon = line.substring(i+15, i+25).toFloat(); // extract longitude in degrees
              String lonDir = line.substring(i+26, i+27); // extract longitude direction (E or W)
              String time = line.substring(i-9, i-1); // extract time (UTC)
              Serial.print("Latitude: ");
              Serial.print(lat, 6);
              Serial.print(" ");
              Serial.print(latDir);
              Serial.print(", Longitude: ");
              Serial.print(lon, 6);
              Serial.print(" ");
              Serial.print(lonDir);
              Serial.print(", Time: ");
              Serial.println(time);
            }
            break;
          }
        }
      }
    }
  }
}
