/* Bizeo-Ethernet library for Arduino
 * Author: Toby Lockley
 * (c) Copyright 2012 Direct Marketing Software Pty. Ltd.
 * All rights reserved.
 */

#include "BizeoEthernet.h"

#define BIZEO_WS_DOMAIN "bizeocloudws.cloudapp.net"
#define BIZEO_TIMEOUT     1000 * 2  // Timeout (ms) for an active connection
#define BIZEO_RETRIES     4  // Number of times to retry failed connection

int BizeoClass::begin()
{
    uint8_t defaultMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x00 };
    return begin(defaultMac);
}

int BizeoClass::begin(uint8_t *macAddress)
{
    bool test = Ethernet.begin(macAddress);
    if (test == 1) {
        if (_debugLevel >= 1) {
            Serial.print(F("Bizeo successfully initialized ethernet with IP: "));
            Serial.println(Ethernet.localIP());
        }
    }
    else {
        if (_debugLevel >= 1) {
            Serial.println(F("Bizeo failed to attach ethernet shield."));
        }
    }
    return test;
}

void BizeoClass::setDebugLevel(unsigned int level)
{
    _debugLevel = level;
}

int BizeoClass::getStatus(String userGuid)
{
    /*
     * Invokes Bizeo web service to retrieve current Bizeo status.
     */

    bool success = false;
    int length = 340;  // Constant length without GUID
    length += userGuid.length();
    if (_debugLevel >= 1) Serial.print(F("Connecting..."));

    // Attempt to connect
    if (_client.connect(BIZEO_WS_DOMAIN, 80)) {
        if (_debugLevel >= 1) Serial.print(F("success..."));

        while (_client.available()) _client.read();  // Flush any data on the client stream

        sendSoapHeader(length);
        _client.print(F("<GetMonitorStatus xmlns=\"http://tempuri.org/\"><MasterTaskID>"));
        _client.print(userGuid);
        _client.print(F("</MasterTaskID></GetMonitorStatus></soap:Body></soap:Envelope>"));
        
        String result = parseXML("GetMonitorStatusResult");
        _client.stop();
        
        if (result == "0") {
            // Everything's OK
            if (_debugLevel >= 1) Serial.println(F("Status: GREEN"));
            return 0;
        }
        else if (result == "1")
        {
            // Warning
            if (_debugLevel >= 1) Serial.println(F("Status: YELLOW"));
            return 1;
        }
        else if (result == "2")
        {
            // Something's wrong!
            if (_debugLevel >= 1) Serial.println(F("Status: RED"));
            return 2;
        }
        else if (result == "-2")
        {
            // Invalid GUID
            if (_debugLevel >= 1) Serial.println(F("Error: Invalid GUID"));
            return -2;
        }
        else
        {
            // Unkown error
            if (_debugLevel >= 1) Serial.println(F("Error: Unkown"));
            return -3;
        }
    }
    else {
        // Something wrong with internet connection
        if (_debugLevel >= 1) Serial.println(F("Failed to make a connection"));
        _client.stop();
        return -1;
    }
}

int BizeoClass::updateKpi(String kpiGuid, int kpiValue)
{
    /*
     * Invokes Bizeo web service to update an external KPI.
     */

    bool success = false;
    int length = 347;  // Constant length without GUID
    length += kpiGuid.length() + String(kpiValue).length();
    if (_debugLevel >= 1) Serial.print(F("Connecting..."));

    // Attempt to connect
    if (_client.connect(BIZEO_WS_DOMAIN, 80)) {
        if (_debugLevel >= 1) Serial.print(F("Success..."));

        while (_client.available()) _client.read();  // Flush any data on the client stream
        
        sendSoapHeader(length);
        _client.print(F("<UpdateExternalKPI xmlns=\"http://tempuri.org/\"><taskId>"));
        _client.print(kpiGuid);
        _client.print(F("</taskId><result>"));
        _client.print(kpiValue);
        _client.print(F("</result></UpdateExternalKPI></soap:Body></soap:Envelope>"));
        
        String result = parseXML("UpdateExternalKPIResult");
        _client.stop();
        
        if (result == "0") {
            // Success
            if (_debugLevel >= 1) Serial.println(F("KPI updated"));
            return 0;
        }
        else if (result == "1")
        {
            // Fail
            if (_debugLevel >= 1) Serial.println(F("Failed, check KPI GUID"));
            return -2;
        }
        else
        {
            // Unknown error
            if (_debugLevel >= 1) Serial.println(F("Error: Unexpected server response"));
            return -3;
        }
    }
    else {
        // Something wrong with internet connection
        if (_debugLevel >= 1) Serial.println(F("Failed to make a connection"));
        _client.stop();
        return -1;
    }
}

int BizeoClass::pub_getStatus(String userGuid)
{
// POST /PublicWS.asmx/GetMonitorStatus HTTP/1.1
// Host: bizeocloudws.cloudapp.net
// Content-Type: application/x-www-form-urlencoded
// Content-Length: length

// MasterTaskID=string
}

int BizeoClass::pub_updateKpi(String kpiGuid, int kpiValue)
{
    /*
     * Invokes Bizeo public web service to update an external KPI.
     */

    bool success = false;
    int length = 347;  // Constant length without GUID
    length += kpiGuid.length() + String(kpiValue).length();
    if (_debugLevel >= 1) Serial.print(F("Connecting..."));

    // Attempt to connect
    if (_client.connect(BIZEO_WS_DOMAIN, 80)) {
        if (_debugLevel >= 1) Serial.print(F("Success..."));

        while (_client.available()) _client.read();  // Flush any data on the client stream
        
        _client.print(F("POST /PublicWS.asmx HTTP/1.1\n"));
        _client.print(F("Host: bizeocloudws.cloudapp.net\n"));
        _client.print(F("Content-Length: "));
        _client.println(length);
        _client.print(F("Connection: close\n"));
        _client.print(F("Content-Type: text/xml; charset=utf-8\n\n"));

        _client.print(F("<?xml version=\"1.0\" encoding=\"utf-8\"?>"));
        _client.print(F("<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "));
        _client.print(F("xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" "));
        _client.print(F("xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">"));
        _client.print(F("<soap:Body>"));
        _client.print(F("<UpdateExternalKPI xmlns=\"http://tempuri.org/\"><taskId>"));
        _client.print(kpiGuid);
        _client.print(F("</taskId><result>"));
        _client.print(kpiValue);
        _client.print(F("</result></UpdateExternalKPI></soap:Body></soap:Envelope>"));
        
        String result = parseXML("UpdateExternalKPIResult");
        _client.stop();
        
        if (result == "0") {
            // Success
            if (_debugLevel >= 1) Serial.println(F("KPI updated"));
            return 0;
        }
        else if (result == "1")
        {
            // Fail
            if (_debugLevel >= 1) Serial.println(F("Failed, check KPI GUID"));
            return -2;
        }
        else
        {
            // Unknown error
            if (_debugLevel >= 1) Serial.println(F("Error: Unexpected server response"));
            return -3;
        }
    }
    else {
        // Something wrong with internet connection
        if (_debugLevel >= 1) Serial.println(F("Failed to make a connection"));
        _client.stop();
        return -1;
    }
}


/***** PRIVATE METHODS *****/

void BizeoClass::sendSoapHeader(unsigned int content_length)
{
    /*
     * SOAP header is the same for each function,
     * so save code re-entry and space by putting it here
     */

    _client.print(F("POST /service1.asmx HTTP/1.1\n"));
    _client.print(F("Host: bizeocloudws.cloudapp.net\n"));
    _client.print(F("Content-Length: "));
    _client.println(content_length);
    _client.print(F("Connection: close\n"));
    _client.print(F("Content-Type: text/xml; charset=utf-8\n\n"));

    _client.print(F("<?xml version=\"1.0\" encoding=\"utf-8\"?>"));
    _client.print(F("<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "));
    _client.print(F("xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" "));
    _client.print(F("xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">"));
    _client.print(F("<soap:Body>"));
}

String BizeoClass::parseXML(String searchStr)
{
    /* 
     * Parse data in the form of XML from web client stream.
     * Looks for an XML tag named <searchStr> and returns it's value.
     * Only works for lowest level tags, e.g  <myData> myValue </myData>
     * Also works if tag has paramters, e.g. <myData param=var>
     */

    boolean tagFlag = false;
    boolean dataFlag = false;

    String tagStr;
    String dataStr;

    unsigned long bytetimer = millis();  // Initialise timer
    char inChar;

    if (_debugLevel >= 2) Serial.println(F("\r\n------------------------------------------------------------"));
    
    while (true) {
        // Endless loop, but returns when either tag is found, or timed out.
        // i.e. If the tag is not found, it will parse the whole stream and then timeout

        if (_client.available()) {
            // Read a character from the stream
            inChar = _client.read();
            if (_debugLevel >= 2) Serial.print(inChar);  // Print http stream for debugging

            switch (inChar) {
            case '<':
                if (dataFlag) {
                    // End of data section, return found data
                    if (_debugLevel >= 2) Serial.println(F("\r\n------------------------------------------------------------"));
                    return dataStr;
                }
                // Start of new tag, set flags and clear strings
                tagFlag = true;
                dataFlag = false;
                tagStr = "";
                dataStr = "";
                break;

            case '>':
                if (tagStr == searchStr) dataFlag = true;  // Only set data flag when correct tag found
                tagFlag = false;
                break;

            default:
                if (tagFlag) {
                    if (inChar == ' ') {
                        // We want to catch the special case when we are reading a tag
                        // and the next character is a space
                        tagFlag = false;  // Clear tagFlag, but leave tagStr populated
                    }
                    else if (tagStr.length() > searchStr.length()) {
                        // Tag is longer than our search string, stop processing it
                        tagFlag = false;
                    }
                    else {
                        tagStr += inChar;  // Add character to tag buffer
                    }
                }
                if (dataFlag) {
                    dataStr += inChar;  // Add character to data buffer
                    if (dataStr.length() > 128) dataFlag = false;  // Defensive driving, discard long strings
                }
            }

            bytetimer = millis();  // Reset timer
        }
        else if ((millis() - bytetimer > BIZEO_TIMEOUT) || !_client.connected()) {
            if (_debugLevel >= 2) Serial.println(F("\r\n------------------------------------------------------------"));
            return "";  // Return an empty string
        }
    }
}

BizeoClass Bizeo;

/* (c) Copyright 2012 Direct Marketing Software Pty. Ltd. */