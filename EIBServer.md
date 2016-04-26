# EIB Server #

The EIB Server is the **major module** in the EIB Suite. this server act as rendezvous point for all other servers (i.e. SMS Server, WEB Server etc.)

---

## General Description ##
When EIB Server starts, it uses 2 configuration files:
  1. **EIB.conf** - this file contains the parameters that allow the EIB Server to connect to the KNX/IP device, and listen for new server wish to gather/control this KNX/IP device
  1. **Users.db** - this file contains the configuration about the other parts of the suite that wish to connect. this file holds the user names, passwords and some privileges restrictions.
these 2 files are essential to EIB Server in order to operate properly. (don't worry, if anything goes wrong, the EIB Server will print an error telling exactly what is the problem).

## Configuration ##
There are 2 different options to create the configuration files:
  1. **_Manually_** - this option is probably better since i may have some bugs in the other option :). note that there are templates files that explains the structure of the configuration files in the templates directory of the installation.
  1. **_Interactive Configuration option_** - in this option, the EIB Server will create the files by itself, just asking you (the users) a few key questions.
    * To create the EIB.conf file - run the following command : **./run.sh EIBServer -i** and follow the screen.
    * To create the Users.db file - run the following command : **./run.sh EIBServer -u** and follow the screen.

## Examples ##
#### EIB.conf ####
```
[EIB-GENERAL]
# The initial key to encrypt and decrypt the messages required for random keys exchange.
EIB_INITIAL_KEY = EIBKEY

# The EIB Server port - the port that EIB Server listens to accept new clients (i.e. WEBServer, SMSServer, AMXServer etc.)
LISTENING_PORT = 5000

# Maximum number of concurrent connected clients
MAX_CONCURRENT_CLIENTS = 10

# The port in which the EIB Console ( A GUI program named 'EIBConsole' ) will connect/send requests to the EIB server.
CONSOLE_MANAGER_PORT = 6000

# This number allows you to set the logging level:
# 0 - No logging at all
# 1 - Error Messages are printed to screen
# 2 - Error + Info messages are printed to screen
# 3 - Error + Info + Debug messages are printed to screen
LOG_LEVEL = 3

# The working mode with  EIB Interface. The options are :
# MODE_ROUTING - Multicast mode
# MODE_TUNNELING - Unicast mode
# MODE_BUSMONITOR - Bus monitor mode (beta)
EIB_DEVICE_MODE = MODE_TUNNELING

# IP Address of EIB Device
# if the EIB_DEVICE_MODE is MODE_ROUTING then a multicast address used by device should be provided (usually this would be 224.0.23.12)
# if the EIB_DEVICE_MODE is MODE_TUNNELING then a unicast address should be provided (usally this address is assigned to the EIBNet/IP device via DHCP server).
# Note: if AUTO_DETECT_EIB_DEVICE_ADDRESS is set to 'true' this directive will be igonored
EIB_IP_ADDRESS = 10.100.1.84

# This flag instruct the system whether to send a multicast search request at the initialization phase to find out
# The ip address of the eib interface. if set to 'false' the EIB_IP_ADDRESS directive will be used, and if set to
#'true' the EIB_IP_ADDRESS will be ignored
AUTO_DETECT_EIB_DEVICE_ADDRESS = false

# The local interface (network card) that will be used for connecting to the EIBNet/IP Device.
# Under windows: this value should be positive integer representing the NIC index (i.e. 0 or 1 or 2 etc.)
# Under linux: this value should be the interface name (i.e. eth0 or eth1 etc)
EIB_LOCAL_INTERFACE = eth0

# The local interface (network card) that will be used for accepting new connections from clients (i.e. WEBServer, SMSServer, AMXServer etc.)
# Under windows: this value should be positive integer representing the NIC index (i.e. 0 or 1 or 2 etc.)
# Under linux: this value should be the interface name (i.e. eth0 or eth1 etc)
CLIENTS_LISTEN_INTERFACE = eth0

```
#### Users.db ####
```
# Replace this block with the user name (e.g. [john])
[USER-NAME]

# The privileges assigned to this user. this field should be integer and is masked to determine the priviliges of the user
# 0x0 - No priviliges as all
# 0x1 - User can only Read messages from EIB server
# 0x2 - User can only Write messages to EIB server
# 0x4 - User can connect to EIBServer via EIBConsole
# Example: if you want to grant all priviliges for a user then use 7 (0x1 + 0x2 + 0x4)
# if you want to grant only Read policy then use 1
PRIVILIGES = 7

# The password for this user (Case sensitive)
PASSWORD = Password

# Allowed source address MASK - any EIB packet with source address that contains one of the bits specified in this mask will be sent to this user
ALLOWED_SOURCE_MASK = 0xFFFF

# Allowed source address MASK - any EIB packet with destination address that contains one of the bits specified in this mask will be sent to this user
ALLOWED_DEST_MASK = 0xFFFF

```
## Starting the Server ##
After both files created successfully, you can type **./run.sh EIBServer** to start the EIB Server itself.