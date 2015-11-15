# Introduction #

In order to encourage you to try the server out, it has been decided to prepare a virtual machine that contains a pre-installed server. Moreover, there is a tool (Jenkins) that can be used to get and build the server from its source code. In other words, this VM is all you need to get started with the project. Enjoy!

# VM image #

Virtual Machine has been created with the VirtualBox and is available at the following location:
https://drive.google.com/folderview?id=0B7dC_6lVVc3yN0Raay0zTE10b1U

Installation is very easy, it is enough to import the provided image as an appliance.

Note: it may be necessary to enable PAE/NX. To do this go to the VM settings, select System, then Processor and tick the 'Enable PAE/NX' option.

## The OS ##

The VM uses Ubuntu Server 12.04.2 LTS as the operating system.

## Networking ##

In order to try the server out, it is enough to provide networking. The easiest approach is to use the Host-Only Adapter, that creates a virtual network. However, if you plan to use Jenkins to build the newest sources you may require an Internet connection - try using Bridged Adapter instead.

## System User ##

The following user is configured and ready to use:

user name: sj

password: password


## How to... ##

### ... start SJ Server? ###

Call start\_sjserver command.

### ... stop SJ Server? ###

Press Ctrl-C

### ... use the SJ Server? ###

From your host run a web browser and navigate to http://sj-server-vm-address:9090/

### ... start Jenkins? ###

Call start\_jenkins command


### ... stop Jenkins? ###

Use

ps ax | grep jenkins

to find its PID and then kill it :-)


### ... use Jenkins? ###

There are three jobs, which are:
  * BUILD - gets the newset source code from the repo, builds the code and creates a ZIP package with the built binaries
  * BUILD\_AND\_RUN\_TESTS - gets the newest source code from the repo, builds the code, builds the tests and runs the tests
  * BUIKD\_AND\_DEPLOY - gets the newest source code from the repo, builds the code and installs the binaries (i.e. update the server, which can be run using the start\_sjserver command)


### Comments? ###

If you would like to share your feedback with the project team, please send an email to: samir.jorina AT gmail DOT com

We encourage you to write us a few lines if you find the project interesting, would like some improvements or find a bug. Thank you in advance.