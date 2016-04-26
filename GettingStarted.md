# Getting Started #

This is a brief description of how to set up the EIB Suite.
The necessary tools for this tutorial are:
  * Linux machine (include g++ compiler)
  * KNX/IP device
  * Sheevaplug Plug computer (Optional)

# Details #
## Build & Install ##
  1. Install subversion on the computer (**sudo apt-get install subversion**)
  1. Install ncurses if not already installed (**sudo apt-get install ncurses**)
  1. Download the EIB Suite source code (**svn checkout https://eibsuite.googlecode.com/svn/trunk/ eibsuite**)
  1. change the the root directory of the project and type: **make menuconfig**
  1. In the opened window, make sure that everything is marked and then exit & save.
  1. If you want to change the default CPU target, change it from the menu and make sure you configured the cross-compiler references as well
  1. In terminal type: **make install**

When the compilation process is finished, you can find the EIB Suite binaries in the (**<root project>/bin**).
Now, before you can start and run the different componenets, a little more configuration is required:
  1. [Configure the EIBServer module](http://code.google.com/p/eibsuite/wiki/EIBServer)
  1. [Configure the WEBServer module](http://code.google.com/p/eibsuite/wiki/WEBServer)
  1. Configure the SMSServer module
  1. Configure the AMXServer module
  1. [Configure the EIBRelay module](http://code.google.com/p/eibsuite/wiki/EIBRelay)