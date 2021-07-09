# Remote Procedure Call

## Overview:
- Client Side: A client-side program which will call an RPC method along with an identifier and expects all the data collected after the last fetch.
- Intermediate Server: An RPC server will sit here which will respond to client requests and participates in reverse polling with sensor servers.
- Sensor Server: Collects data from sensors and participates in reverse polling with intermediate server.
- Sensor: Records and sends data to sensor server.

## Use Cases:
- Client program will call the RPC method using senor_id as parameter an should get all the data collected after most recent fetch.
- Server side of RPC method should be at intermediate server only which will handle client requests.
- Sensor servers and intermediate server should do reverse polling with no listener at sensor servers.
- Sensors should independently record data and send it to the sensor server.
- There should be one client, one intermediate server, one sensor server with two sensors (having different rate at which they record data).