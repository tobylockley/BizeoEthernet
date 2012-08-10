/* Bizeo-Ethernet library for Arduino
 * Author: Toby Lockley
 * (c) Copyright 2012 Direct Marketing Software Pty. Ltd.
 * All rights reserved.
 */
 
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
    BizeoClass() { _debugLevel = 2; }
    
    int begin();
    int begin(uint8_t *mac_address);
    void setDebugLevel(unsigned int level);
    
    // Bizeo web service functions. Default to GET
    int getStatus(String userGuid);
    int updateKpi(String kpiGuid, int value);

    // Extra web service request methods
    int post_getStatus(String userGuid);
    int post_updateKpi(String kpiGuid, int value);
    
    int soap_getStatus(String userGuid);
    int soap_updateKpi(String kpiGuid, int value);
};

extern BizeoClass Bizeo;

#endif  // __BIZEO_H

/* (c) Copyright 2012 Direct Marketing Software Pty. Ltd. */