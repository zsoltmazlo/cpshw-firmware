/* -----------------------------------------------------------
This example shows a lot of different features. As configured here
it will check for a good GPS fix every 10 minutes and publish that data
if there is one. If not, it will save you data by staying quiet. It also
registers 3 Particle.functions for changing whether it publishes,
reading the battery level, and manually requesting a GPS reading.
---------------------------------------------------------------*/

// Getting the library
#include <application.h>
#include <TinyGPS++.h>

long last = 0;
int delays = 1;

TinyGPSPlus gps;

int min2mill(int min);

void setup() {
   Serial.begin(9600);
}

void loop() {
   if(Serial.available())
      for(auto c = Serial.readString().c_str(); c; ++c)
         gps.encode(*c);

   if(millis() - last > min2mill(delays)) {
      auto location = gps.location;
      if(location.isValid() && location.isUpdated()) {
         auto str = String::format("%d:%d", location.lat(), location.lng());
         Particle.publish("pos", str, 60, PRIVATE);
      }

      last = millis();
   }
}

int min2mill(int min) {
   return 1000 * 60 * min;
}
