# BizeoEthernet Library
##### Interfaces to the Bizeo web services via simple HTTP calls. Requires an arduino, the arduino IDE (version 1.0 or later), and an ethernet shield.

This library takes away all the hassle of working with the Bizeo web services with an arduino. Feel free to browse the source code to see how they are called and parsed. An overview of all the available web services can be found [here](http://bizeocloudws.cloudapp.net/PublicWS.asmx).

This library implements all available HTTP methods (GET, POST and SOAP). If the web service functions are called without specifying which method to use, the GET method is used. This is because it sends and receives the least amount of data, so can speed up web interaction.

You cannot use this library and the equivalent BizeoWiFly library at the same time. You can use other ethernet clients, but the Bizeo library declares one on creation, so there will only be 3 available for general use.

## Todo
* Create similar library for WiFly.

## Installation
Copy everything into the folder: "*<strong>ArduinoSketchbook</strong>*/libraries/BizeoEthernet"
You may have to create the libraries folder. Default sketchbook location is in:

* Windows: "My Documents\Arduino"
* Mac: "~/Documents/Arduino"

## Usage
First, you must include all relevant library files:

````
#include <SPI.h>
#include <Ethernet.h>
#include <BizeoEthernet.h>
````

Then, call Bizeo.begin in the setup function:

````c
void setup()
{
    if (!Bizeo.begin()) {  // Uses default MAC [DE:AD:BE:EF:FE:00]
      // Handle failure
    }
}
````

If more than one arduino is being used on the network, specify separate MAC addresses with:

````c
byte mac_address[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };

if (!Bizeo.begin(mac_address)) {
    // Handle failure
}
````

Then, use the Bizeo web calls any time you need them:

````c
int status = Bizeo.getStatus(user_guid);
// Do something with status

int update = Bizeo.updateKpi(kpi_guid, new_value);
// Check the output to make sure it worked
````

Occasionally, the internet requests may fail. This can be due to an unplugged wire, an ISP malfunction, or even a server error. It is a good idea to always check the output of the web service functions to make sure they succeeded, and handle the errors when they don't (retry, give a warning, etc).

## Overview of Functions

###### Note: Some return values differ from what is returned by the web service. This is to provide consistency between the functions and provide a more meaningful return value (i.e. less than zero = error) within the arduino environment.

--------------------------------

````c
int begin()
````

Initializes the Bizeo class and ethernet shield with default MAC address (DE:AD:BE:EF:FE:00).

##### *Input*
&nbsp;&nbsp;None

##### *Output*
* ``1`` -- Succeeded to initialize ethernet shield and obtain IP address
* ``0`` -- Failed to initialize ethernet
<br><br>

--------------------------------

````c
int begin(uint8_t *mac_address)
````

Initializes the Bizeo class and ethernet shield with specified MAC address.

##### *Input*
* ``mac_address``  --  Pointer to an array of 6 bytes respresenting a mac address

##### *Output*
* ``1``  --  Succeeded to initialize ethernet shield and obtain IP address
* ``0``  --  Failed to initialize ethernet
<br><br>

--------------------------------

````c
void setDebugLevel(unsigned int level)
````

Sets the level of verbosity desired. Currently only values 0, 1, and 2 are implemented, but larger values will not cause errors, simply allow debug levels up to and including the given value.

##### *Input*
* ``level`` -- Desired verbosity level
    * ``0``  --  No debug output
    * ``1``  --  Light debug messages
    * ``2``  --  Detailed (verbose) debug messages

##### *Output*
&nbsp;&nbsp;None
<br><br>

--------------------------------

````c
int getStatus(String userGuid)
````

When a valid user GUID is supplied, will return the current Bizeo status for that user. This function uses the default of HTTP GET request to consume the web service.

##### Input
* ``userGuid``  -  Bizeo user GUID, which can be extracted from the url when browsing to the Bizeo status page in a browser

##### Output
* &nbsp;``0``  -  Green
* &nbsp;``1``  -  Yellow
* &nbsp;``2``  -  Red
* ``-1``  -  Connection error
* ``-2``  -  Invalid GUID
* ``-3``  -  Unknown server response
<br><br>

--------------------------------

````c
int getStatus(HTTP_METHOD method, String userGuid)
````
E.g: ``e.g. Bizeo.getStatus(POST, myGuid);``

Get current Bizeo status, using the HTTP request method specified. GET is the fastest, but POST and SOAP are implemented as well. This may be useful if GET requests are ever disabled on the server in the future (they are sometimes less secure).

##### Input
* ``method  ``  --  Which HTTP request method to use for this web service call. Valid arguments are:
    * ``GET``
    * ``POST``
    * ``SOAP``
* ``userGuid``  --  See above

##### Output
&nbsp;&nbsp;See above
<br><br>

--------------------------------

````c
int updateKpi(String kpiGuid, int value)
````

When a valid KPI GUID is supplied, a request is sent to the Bizeo server, which will attempt to update the KPI with the new value. This function uses the default of HTTP GET request to consume the web service.

##### Input
* ``kpiGuid``  --  Bizeo external KPI GUID, which can be found by browsing to an external KPI in your browser, and clicking on settings
* ``value``  --  New integer KPI value

##### Output
* &nbsp;``0``  --  Success
* ``-1``  --  Connection error
* ``-2``  --  Invalid GUID
* ``-3``  --  Unknown server response

There is a variant available which allows the user to specify which HTTP request method to use. GET is the fastest, but POST and SOAP are implemented as well, in case GET requests are ever disabled in the future (they are sometimes less secure). The alternate function looks like this:

````c
int updateKpi(HTTP_METHOD method, String kpiGuid, int value)
````

The extra parameter ``method`` is a custom enum (defined in the header file) representing the HTTP request method to use.  
Valid arguments are:
* ``GET``
* ``POST``
* ``SOAP``
<br><br>

--------------------------------

*&copy; Copyright 2012 Direct Marketing Software Pty. Ltd.*

