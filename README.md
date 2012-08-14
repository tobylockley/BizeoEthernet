# BizeoEthernet Library
Interfaces to the bizeo web services through http calls. Requires an arduino, the arduino IDE (version 1.0 or later), and an ethernet shield.

## Todo
* Create similar library for WiFly.

# Installation
Copy everything into the folder: "*Arduino-Sketchbook*/libraries/BizeoEthernet"
You may have to create the libraries folder. Default sketchbook location is in:

* Windows: "My Documents\Arduino"
* Mac: "~/Documents/Arduino"

# Usage
This library takes away all the hassle of working with the Bizeo web services with an arduino. Feel free to browse the source code to see how they are called and parsed. An overview of all the available web services can be found [here](http://bizeocloudws.cloudapp.net/PublicWS.asmx).

This library implements all available HTTP methods (GET, POST and SOAP). If the web service functions are called without specifying which method to use, the GET method is used. This is because it sends and receives the least amount of data, so can speed up web interaction.

You cannot use this library and a WiFly at the same time (althought I don't know why you would want to). You can use other ethernet clients, but the bizeo library declares one on creation, so there will only be 3 remaining.

## Basic usage
First, you must include all relevant library files:

````
#include <SPI.h>
#include <Ethernet.h>
#include <BizeoEthernet.h>
````

Then, call Bizeo.begin in the setup function. Default MAC address is (DE:AD:BE:EF:FE:01):

````c
void setup()
{
    if (!Bizeo.begin()) {
      // Handle failure
    }
}
````

If more than one arduino are being used on the network, specify  MAC address with:

````c
<span class="kt">byte</span> mac_address[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02 };

if (!Bizeo.begin(mac_address)) {
    // Handle failure
}
````

Then, use the Bizeo web calls any time you need them:

````c
int status = Bizeo.getStatus(user_guid);
    // Do something with status
Bizeo.updateKpi(kpi_guid, new_value);
````

## Overview of Functions

**Note: Some return values differ from what is returned by the web service. This is to provide consistency between the functions and provide a more meaningful return value (i.e. less than zero = error) within the arduino environment.**

--------------------------------

````c
int begin()
int begin(uint8_t *mac_address)
````

*Initializes the bizeo class and ethernet shield with default MAC address (DE:AD:BE:EF:FE:00).*

<dl>
  <dt>Input</dt>
  <dd>
  None
  </dd>
  <dt>Output</dt>
  <dd>
<pre>
  1 = Succeeded to initialize ethernet shield and obtain IP address  
  0 = Failed to initialize ethernet  
  3 = testing  
  4 = more testing  
</pre>
  </dd>
</dl>
  

--------------------------------

````c
int begin(uint8_t *mac_address)
````

*Initializes the bizeo class and ethernet shield with specified MAC address.*

#####*Input*
* Pointer to an array of 6 bytes corresponding to a mac address

#####*Output*
* 1 - Succeeded to initialize ethernet shield and obtain IP address
* 0 - Failed to initialize ethernet

--------------------------------

````c
void setDebugLevel(unsigned int level)
````

*Sets the level of verbosity desired. Currently only values 0, 1, and 2 are implemented, but larger values will not cause errors, simply allow debug levels up to and including the given value.*

######*Input*
&nbsp; Desired verbosity level
* &nbsp; 0 - No debug output
* &nbsp; 1 - Light debug messages
* &nbsp; 2 - Detailed (verbose) debug messages

######*Output*
* None  
  

--------------------------------

````c
int getStatus(String userGuid)
````

When a valid GUID is supplied, will return the current Bizeo status for the corresponding user.

######*Input*
&nbsp; Bizeo user GUID, which can be extracted from the url when browsing to the bizeo status page in a browser.

######*Output*
&nbsp; &nbsp; Integer value corresponding to bizeo status or error code.
* &nbsp; 0 -> Green
* &nbsp; 1 -> Yellow
* &nbsp; 2 -> Red
* -1 -> Connection error
* -2 -> Invalid GUID
* -3 -> Unknown server response
<br>

--------------------------------

````c
int updateKpi(String kpiGuid, int value)
````

*When a valid KPI GUID and value are supplied, the server will attempt to update the database with the new value.*
<dl>
  <dt>Input</dt>
  <dd>Bizeo external KPI GUID, which can be found by browsing to an external KPI in your browser, and clicking on settings.</dd>
  <dt>Output</dt>
&nbsp; Integer value corresponding to success or error code.
* &nbsp; 0 > Success
* -1 > Connection error
* -2 > Invalid GUID
* -3 > Unknown server response

--------------------------------

*&copy; Copyright 2012 Direct Marketing Software Pty. Ltd.*

