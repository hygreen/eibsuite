# WEB Server #

The WEB Server provide web interface to the KNX/IP bus. the main features of this server are:
  1. Viewing History of specific function (Specific KNX Address)
  1. Viewing Global history (the last 100 messages sent on the KNX/IP bus)
  1. Sending specific command to the KNX/IP bus
  1. Scheduling a command for later execution

## General Description ##
The WEB Server is small & basic WEB interface to the KNX/IP bus. the server supports HTTP basic authentication and provide web interface to several actions for monitoring and controlling the KNX/IP bus.

This server is written entirely in c++ and depends on the EIBStdLib shared object (DLL) which is also part of the EIB Suite.

When the WEB Server starts, it uses 2 configuration files:
  1. **WEB.conf** - this file contains the parameters that allow the WEB Server to connect to the EIB Server.
  1. **WEBUsers.db** - this file contains the configuration about the users the allow to use the web interface. this file holds the user names, passwords and some privileges restrictions.
these 2 files are essential to WEB Server in order to operate properly. (don't worry, if anything goes wrong, it will print an error telling exactly what is the problem).

## Configuration ##
There are 2 different options to create the configuration files:
  1. **_Manually_** - this option is probably better since i may have some bugs in the other option :). note that there are templates files that explains the structure of the configuration files in the templates directory of the installation.
  1. **_Interactive Configuration option_** - in this option, the WEB Server will create the files by itself, just asking you (the users) a few key questions.
    * To create the WEB.conf file - run the following command : **./run.sh WEBServer -i** and follow the screen.
    * To create the WEBUsers.db file - run the following command : **./run.sh WEBServer -u** and follow the screen.

## Examples ##
#### WEB.conf ####
```
[WEB-GENERAL]

#initial key to encrypt and decrypt the messages required for random keys exchange
WEB_INITIAL_KEY = EIBKEY

AUTO_DISCOVER_EIB_SERVER = true

#IP Address of the EIB Server
EIB_SERVER_IP_ADDRESS = 127.0.0.1

#The EIB Server port (the port that EIB Server listens to accept new clients)
EIB_SERVER_PORT = 5000

#The port to listen to for Incoming WEB connections (browser)
WEB_SERVER_PORT = 8080

#The ip address to listen to for Incoming WEB connections (browser)
LISTEN_INTERFACE = eth0

#Login name of the AMX server. this name will be used during the authentication with the EIB Server (Case sensitive)
WEB_SERVER_NAME = WEB

#Network name of this server. this name rquired during the authentication with the EIB Server (Case sensitive)
WEB_NETWORK_NAME = WEB

#Login password of the AMX server. this password will be used during the authentication with the EIB Server
WEB_SERVER_PASSWORD = WEB

# The directory where the images files used by the WEB Server are located
WEB_SERVER_IMAGES_FOLDER = /EIBProject/WEBServer/Images
```

#### WEBUsers.db ####
```
[USER-NAME]

#the password for this user (Case sensitive)
PASSWORD = Password
```
## Starting the Server ##
After both files created successfully, you can type **./run.sh EIBServer** to start the EIB Server itself.