# EIB Relay Server #

The Relay Server provides a tunnel connection to the KNX/IP Bus through the EIB Server.
One of the main features of the EIB Server is the security channel between the EIB Server and all the others servers.
In order to provide this secure channel, the EIB Server (and the other servers) employs a propriety encryption/decryption method so that all of the messages of that channel are secured. this feature is important but has a major drawback: any other device that wish to connect to the KNX/IP device must connect directly to the EIB Server and must use the same encryption methods.

The solution to this problem is the EIB Relay server.
the Relay server implements the KNX/IP stack locally, and the exposes itself as a "KNX/IP Device" to the outside world. the Relay server also maintains a secure channel (that is not exposed) to the EIB Server itself, and this way it can receive and send messages to KNX/IP bus.

Since the EIB Relay implements the KNX/IP stack internaly, it can provide another important feature:
most of the KNX/IP devices that are currently in the market supports only single UDP connection to the KNX/IP device itself. the EIB Relay can support many concurrent connection, and therefore to provide access to the KNX/IP bus to many applications at the same time.

## General Description ##

This Relay Server is written entirely in c++ and depends on the EIBStdLib shared object (DLL) which is also part of the EIB Suite.

When the EIB Relay Server starts, it uses 1 configuration files:
  1. **Relay.conf** - this file contains the parameters that allow the WEB Server to connect to the EIB Server.

this file is essential to Relay Server in order to operate properly. (don't worry, if anything goes wrong, it will print an error telling exactly what is the problem).

## Configuration ##
There are 2 different options to create the configuration files:
  1. **_Manually_** - this option is probably better since i may have some bugs in the other option :). note that there are templates files that explains the structure of the configuration files in the templates directory of the installation.
  1. **_Interactive Configuration option_** - in this option, the WEB Server will create the files by itself, just asking you (the users) a few key questions.
    * To create the Relay.conf file - run the following command : **./run.sh EIBRelay -i** and follow the screen.

## Examples ##
#### Relay.conf ####
```
[RELAY-GENERAL]

# Initial key to encrypt and decrypt the messages required for random keys exchange
RELAY_INITIAL_KEY = EIBKEY

# Whether to try and find the EIB Server automatically on the local network.
# Note: if this flag set to 'false' then you must provide the EIB_SERVER_IP_ADDRESS by hand.
AUTO_DISCOVER_EIB_SERVER = true

# IP Address of the EIB Server
# Note: if AUTO_DISCOVER_EIB_SERVER is set to 'true' then this field is not used.
EIB_SERVER_IP_ADDRESS = 127.0.0.1

#The EIB Server port (the port that EIB Server listens to accept new clients)
EIB_SERVER_PORT = 5000

# This number allows you to set the logging level:
# 0 - No logging at all
# 1 - Error Messages are printed to screen
# 2 - Error + Info messages are printed to screen
# 3 - Error + Info + Debug messages are printed to screen
LOG_LEVEL = 3

#Login name of the AMX server. this name will be used during the authentication with the EIB Server (Case sensitive)
RELAY_SERVER_NAME = RELAY

#Network name of this server. this name rquired during the authentication with the EIB Server (Case sensitive)
RELAY_NETWORK_NAME = RELAY

#Login password of the Relay server. this password will be used during the authentication phase with the EIB Server
RELAY_SERVER_PASSWORD = RELAY

# The Network interface name that will be used to listen for KNX applications.
# Note: this interface will also be used to connect to the EIBServer.
LISTEN_INTERFACE = eth2
```

## Starting the Server ##
After both files created successfully, you can type **./run.sh EIBRelay** to start the EIB Relay Server itself.