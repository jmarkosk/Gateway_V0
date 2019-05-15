#include "application.h"
#line 1 "c:/Users/jasonma.Vecima/Documents/particle/boron/GATEWAY_V0/Gateway_V0/src/Gateway_V0.ino"
/*
 * Project Gateway_V0
 * Description:
 * Author:
 * Date:
 */
#include "elapsedMillis.h"

void ProcessNodes(const char *event, const char *data);
void setup();
void loop();
#line 9 "c:/Users/jasonma.Vecima/Documents/particle/boron/GATEWAY_V0/Gateway_V0/src/Gateway_V0.ino"
SYSTEM_THREAD(ENABLED);
//SYSTEM_MODE(SEMI_AUTOMATIC);
//SYSTEM_MODE(MANUAL);



#define TIME_INTERVAL 1000
#define HB_LED D7 //heartbeat LED
u64_t lastTime = 0;
bool heartbeat = 0;
bool heartbeat_blocking = 1;
bool gLedstate = LOW;

const char version[] = "MESH_YARD_MONITOR_v0.0.1";
elapsedMillis timeElapsed;
elapsedMillis timeElapsed2;
// setup() runs once, when the device is first turned on.

void ProcessNodes(const char *event, const char *data)
{
  Serial.printlnf("event=%s data=%s", event, data ? data : "NULL");
}




void setup() {
  // Put initialization like pinMode and begin functions here.
    Serial.begin(9600);
    waitFor(Serial.isConnected, 30000);
    Serial.printlnf("Version: %s", version);
    Serial.println("Yard Monitor initialized....");
    pinMode(HB_LED, OUTPUT);
    
    Mesh.subscribe("Recieved_Nodes", ProcessNodes);

    Mesh.publish("GET_Nodes");
    



}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
/*
  if(millis() - lastTime >= TIME_INTERVAL){
    lastTime = millis();
    heartbeat = 1;
  }
*/
  if(timeElapsed > TIME_INTERVAL)
  {
     heartbeat = 1;
     timeElapsed = 0;
  }


  if(heartbeat && heartbeat_blocking){
    heartbeat_blocking = 0;
    gLedstate = !gLedstate;
    digitalWrite(HB_LED,gLedstate);
    heartbeat_blocking = 1;
    heartbeat = 0;
  }

}