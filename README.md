# BizeoEthernet Library
Interfaces to the bizeo web services through http calls. Requires an arduino, the arduino IDE (version 1.0 or later), and an ethernet shield.

## Todo
* Create similar library for WiFly.

# Installation
Copy everything into the folder: "<Arduino-Sketchbook>/libraries/BizeoEthernet"
You may have to create the libraries folder. Default sketchbook location is in:
"My Documents\Arduino" for Windows
"~/Documents/Arduino" for Mac

# Usage
This library takes away all the hassle of working with the Bizeo web services with an arduino. Feel free to browse the source code to see how they are called and parsed. An overview of all the available web services can be found [here](http://bizeocloudws.cloudapp.net/PublicWS.asmx).

This library implements all available HTTP methods (GET, POST and SOAP). If the web service functions are called without specifying which method to use, the GET method is used. This is because it sends and receives the least amount of data, so can speed up web interaction.

You cannot use this library and a WiFly at the same time (althought I don't know why you would want to). You can use other ethernet clients, but the bizeo library declares one on creation, so there will only be 3 remaining.

## Basic usage
First, you must include all relevant library files:

    #include <SPI.h>
    #include <Ethernet.h>
    #include <BizeoEthernet.h>

Then, call Bizeo.begin in the setup function. Default MAC address is (DE:AD:BE:EF:FE:01):

    void setup()
    {
        if (!Bizeo.begin()) {
          // Handle failure
        }
    }

If more than one arduino are being used on the network, specify  MAC address with:

    byte mac_address[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02 };
    
    if (!Bizeo.begin(mac_address)) {
      // Handle failure
    }

Then, use the Bizeo web calls any time you need them:

    int status = Bizeo.getStatus(user_guid);
        // Do something with status
    Bizeo.updateKpi(kpi_guid, new_value);

## Overview of Functions

**NOTE: Some return values differ from what is returned by the web service. This is to provide consistency between the functions and provide a more meaningful return value (i.e. less than zero = error).**

    int begin()

*Initializes the bizeo class and ethernet shield with default MAC address (0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x00).*

<table>
  <tr>
    <th>Input</th><th>Output</th>
  </tr>
  <tr>
    <td>None</td><td>* 1 if succeeded to obtain IP address. * 0 if failed.</td>
  </tr>
</table>
#####Input:
None

#####Output:
1 if succeeded to obtain IP address, 0 if failed


    int begin(uint8_t *mac_address)
    |
    | Initializes the bizeo class and ethernet shield with specified
    | MAC address.
    |
    |  Input: Array of 6 bytes corresponding to a mac address.
    |         E.g. byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };
    |              Bizeo.begin(mac);
    |
    | Output: 1 if succeeded to obtain IP address, 0 if failed


void setDebugLevel(unsigned int level)
|
| Sets the level of verbosity desired. Currently only values 0, 1,
| and 2 are implemented, but larger values will not cause errors,
| simply allow debug levels up to and including the value to report.
|
|  Input: 0 for no debug output, or a positive integer corresponding to
|         the level desired. Higher = more detailed information.
|
| Output: None


int getStatus(String userGuid)
|
| When a valid GUID is supplied, will return the current Bizeo
| status for the corresponding user.
|
|  Input: Bizeo user GUID, which can be extracted from the url when
|         browsing to the bizeo status page in a browser.
|
| Output: Integer value corresponding to bizeo status or error code.
|         0 = Green
|         1 = Yellow
|         2 = Red
|        -1 = Connection error
|        -2 = Invalid GUID
|        -3 = Unknown server response


int updateKpi(String kpiGuid, int value)
|
| When a valid KPI GUID and value are supplied, the server will attempt to
| update the database with the new value.
|
|  Input: Bizeo external KPI GUID, which can be found by browsing to
|         an external KPI in your browser, and clicking on settings.
|
| Output: Integer value corresponding to success or error code.
|         0 = Success
|        -1 = Connection error
|        -2 = Invalid GUID
|        -3 = Unknown server response


int pub_getStatus(String userGuid)
int pub_updateKpi(String kpiGuid, int value)
|
| These behave exactly the same as their similar functions above,
| but just use the public web service calls in their implementation.


*(c) Copyright 2012 Direct Marketing Software Pty. Ltd.*


# Heading one
stuff

## Heading two
more stuff

### Heading three
more stuff

#### Heading four
more stuff

##### Heading five
more stuff

###### Heading six
more stuff

####### Heading seven
more stuff

