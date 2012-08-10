BizeoEthernet

Requires an arduino, the arduino IDE (version 1.0 or later), and an
ethernet shield. Interfaces to the bizeo web services through http calls.


Todo
--------------------------------------------------------------------------------
- Fully implement public WS, possible remove service1 functionality (not needed)
- Add variant methods for GET, POST, and SOAP requests
- Add retries when a failure occurs
- Create similar library for WiFly
- Make the readme a little more readable


Installation
--------------------------------------------------------------------------------
Copy everything into the folder: "<Arduino-Sketchbook>/libraries/BizeoEthernet"
You may have to create the libraries folder. Default sketchbook location is in:
"My Documents\Arduino" for Windows
"~/Documents/Arduino" for Mac


Usage
--------------------------------------------------------------------------------
This library takes away all the hassle of working with the Bizeo SOAP services
with an arduino. Feel free to browse the source code to see how SOAP calls
are handled. An overview of all the available web services can be found at:

service1: http://bizeocloudws.cloudapp.net/service1.asmx
PublicWS: http://bizeocloudws.cloudapp.net/PublicWS.asmx

The two services are similar, but the public service allows post and get
requests, which are easier to handle with an arduino. This library uses both
services; the public service is called by prefixing pub_ to the function.

Note, the file guard for the library header is the same as that in the other
bizeo libraries. This is done on purpose, so only one bizeo service is
running on the arduino at a time.

Following is a listing of the BizeoClass methods:

NOTE: Some return values differ from what is returned by the web service.
      This is to provide consistency between the functions and provide
      a more meaningful return value (i.e. less than zero = error).

int begin()
#
# Initializes the bizeo class and ethernet shield with default
# MAC address (0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x00).
#
#  Input: None
#
# Output: 1 if succeeded to obtain IP address, 0 if failed

int begin(uint8_t *mac_address)
#
# Initializes the bizeo class and ethernet shield with specified
# MAC address.
#
#  Input: Array of 6 bytes corresponding to a mac address.
#         E.g. byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };
#              Bizeo.begin(mac);
#
# Output: 1 if succeeded to obtain IP address, 0 if failed

void setDebugLevel(unsigned int level)
#
# Sets the level of verbosity desired. Currently only values 0, 1,
# and 2 are implemented, but larger values will not cause errors,
# simply allow debug levels up to and including the value to report.
#
#  Input: 0 for no debug output, or a positive integer corresponding to
#         the level desired. Higher = more detailed information.
#
# Output: None

int getStatus(String userGuid)
#
# When a valid GUID is supplied, will return the current Bizeo
# status for the corresponding user.
#
#  Input: Bizeo user GUID, which can be extracted from the url when
#         browsing to the bizeo status page in a browser.
#
# Output: Integer value corresponding to bizeo status or error code.
#         0 = Green
#         1 = Yellow
#         2 = Red
#        -1 = Connection error
#        -2 = Invalid GUID
#        -3 = Unknown server response

int updateKpi(String kpiGuid, int value)
#
# When a valid KPI GUID and value are supplied, the server will attempt to
# update the database with the new value.
#
#  Input: Bizeo external KPI GUID, which can be found by browsing to
#         an external KPI in your browser, and clicking on settings.
#
# Output: Integer value corresponding to success or error code.
#         0 = Success
#        -1 = Connection error
#        -2 = Invalid GUID
#        -3 = Unknown server response

int pub_getStatus(String userGuid)
int pub_updateKpi(String kpiGuid, int value)
#
# These behave exactly the same as their similar functions above,
# but just use the public web service calls in their implementation.


/* (c) Copyright 2012 Direct Marketing Software Pty. Ltd. */