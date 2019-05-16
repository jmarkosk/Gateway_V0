/*
 * Project Gateway_V0
 * Description:
 * Author:
 * Date:
 */
#include "elapsedMillis.h"

SYSTEM_THREAD(ENABLED);
//SYSTEM_MODE(SEMI_AUTOMATIC);
//SYSTEM_MODE(MANUAL);



#define TIME_INTERVAL 1000
#define TIME_INTERVAL2 2000
#define HB_LED D7 //heartbeat LED

const char version[] = "MESH_YARD_MONITOR_v0.0.1";

//MESH DATA
//Structure?
#define MESH_STATS_LED D6
#define  MAX_MESH_NODES 2
#define  MAX_MESH_DATA 32
uint8_t gNumberofNodes = 2;
char    gNodeID[MAX_MESH_NODES][4];
char gNodesDATA[MAX_MESH_NODES][MAX_MESH_DATA];



u64_t lastTime = 0;
bool heartbeat = 0;
bool heartbeat_blocking = 1;
bool gLedstate = LOW;

u64_t lastTime2 = 0;
bool heartbeat2 = 0;
bool heartbeat_blocking2 = 1;
bool gLedstate2 = LOW;







elapsedMillis timeElapsed;
elapsedMillis timeElapsed2;
// setup() runs once, when the device is first turned on.






void setup() {
  // Put initialization like pinMode and begin functions here.
    Serial.begin(9600);
    waitFor(Serial.isConnected, 30000);
    Serial.printlnf("Version: %s", version);
    Serial.println("Yard Monitor initialized....");
    pinMode(HB_LED, OUTPUT);
    pinMode(MESH_STATS_LED, OUTPUT);
    
    Mesh.subscribe("Recieved_Nodes", ProcessNodes);

    //Mesh.publish("GET_Nodes");
    



}

void ProcessNodes(const char *, const char *);

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
  
  if(timeElapsed2 > TIME_INTERVAL2)
  {
     heartbeat2 = 1;
     timeElapsed2 = 0;
  }



  if(heartbeat2 && heartbeat_blocking2){
    heartbeat_blocking2 = 0;
    gLedstate2 = !gLedstate2;   
    digitalWrite(MESH_STATS_LED,gLedstate2);
    heartbeat_blocking2 = 1;
    heartbeat2 = 0;
    Serial.printlnf("GATEWAY: Sending <<<GET NODE>>> request");
    Mesh.publish("GET_Nodes");
  }

    if(heartbeat && heartbeat_blocking){
    heartbeat_blocking = 0;
    gLedstate = !gLedstate;
    digitalWrite(HB_LED,gLedstate);    
    heartbeat_blocking = 1;
    heartbeat = 0;
    
  }

}

void ProcessNodes(const char *event, const char *data)
{
  Serial.printlnf("event=%s data=%s", event, data ? data : "NULL");
}