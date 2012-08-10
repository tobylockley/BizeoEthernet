#ifndef __BIZEO_H
#define __BIZEO_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Ethernet.h>

class BizeoClass {
private:
    EthernetClient _client;
    unsigned int _debugLevel;
    String parseXML(String searchStr);
    void sendSoapHeader(unsigned int content_length);

public:
    BizeoClass() { _debugLevel = 0; }
    
    int begin();
    int begin(uint8_t *mac_address);
    void setDebugLevel(unsigned int level);
    
    // Bizeo web service functions (service1.asmx)
    int getStatus(String userGuid);
    int updateKpi(String kpiGuid, int value);

    // Bizeo PUBLIC web service functions (PublicWS.asmx)
    // These are faster, but sometimes the website goes down
    int pub_getStatus(String userGuid);
    int pub_updateKpi(String kpiGuid, int value);
};

extern BizeoClass Bizeo;

#endif  // __BIZEO_H
