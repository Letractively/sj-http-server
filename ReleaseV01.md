# Introduction #

Version 0.1 is now out !

This is a beta release with only basic functionality. Nevertheless, it demonstrates what is this project all about.


# Installation #

## Linux ##

Download the sjserver-linux-0.1.zip, unpack it and start by running the _run.sh_ script.

Requirements:
  * QT runtime libraries

## Windows ##
Download the following files:
  * sjserver-win-0.1.zip
  * win-rt-libs-0.1.zip

Unpack them into one folder (i.e. libs should located at the same level as the sj-http-server.exe). To start simply run the _sj-http-server.exe_ executable


# Running & Testing #

After starting the server, in the top-right corner there is a _Start server_ button. After pressing it, the server will listen on the configured interface / port (see below).

By default it listens on localhost and port 9090.

To test the server visit the following links:
  * http://localhost:9090 - you should see a simple static page loaded from a html file
  * http://localhost:9090/fortune-cookie - this is a dynamic page prepared by the fortune-teller plugin.

# Configuration file #

The SJ Http Server uses a configuration file, _sj-http-server.ini_. Settings can be also modified via the GUI.