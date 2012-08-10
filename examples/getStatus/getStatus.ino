#include <BizeoEthernet.h>

const char USER_GUID[]  = "XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX";

// You need to increment this for each new arduino on the network
// Pass this to Bizeo.begin()
byte mac_address[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };

void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    delay(500);  // Wait for things to settle

    Serial.println(F(""));
    Serial.println(F("# BIZEO EXAMPLE"));
    Serial.println(F("# Connection: Ethernet"));
    Serial.println(F("# Function: getStatus()"));
    Serial.println(F("#"));
    Serial.println(F("# Expected results:"));
    Serial.println(F("#  0 = Green"));
    Serial.println(F("#  1 = Yellow"));
    Serial.println(F("#  2 = Red"));
    Serial.println(F("# -1 = Connection error"));
    Serial.println(F("# -2 = Invalid GUID"));
    Serial.println(F("# -3 = Unknown error"));
    Serial.println(F(""));
    
    //Bizeo.setDebugLevel(2);  // Uncomment to see verbose http output
    
    if (!Bizeo.begin()) {
        Serial.println("Bizeo failed to initialize, halting.");
        for (;;)
            ;  // Halt
    }
    
}


void loop()
{
    Serial.println("calling Bizeo.getStatus()...");
    int bizeostatus = Bizeo.getStatus(USER_GUID);
    Serial.print("int returned: ");
    Serial.println(bizeostatus);
    delay(10000);  // Delay before next status check
}