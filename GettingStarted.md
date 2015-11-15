# Introduction #

Here you will find instructions concerning installation, configuration and running of the server


# Checking out the project #

```
svn checkout http://sj-http-server.googlecode.com/svn/trunk/ sj-http-server-read-only
```

# Compilation #
Go to project directory and run
```
qmake
make
```

# Running #
Go to _server_ directory and run
```
./run.sh
```

**Note**: project tested on Linux OS, should also work on Windows


# Configuration #

After starting the server a set of properties need to be set:

![http://sj-http-server.googlecode.com/svn/wiki/img/sjs-01-settings.png](http://sj-http-server.googlecode.com/svn/wiki/img/sjs-01-settings.png)

  1. WWW root directory - the directory, from which WWW content will be read (for example the _www_ directory from the project)
  1. Listening host - name/address of the interface on which the server will listen; for example (without the quotes):
    * 'any' - listens on all available interfaces
    * 'localhost' - listens only on the local interface (same as '127.0.0.1')
    * '192.168.100.101' - listen on the specified ip address
  1. Listening port - number of the port on which the server listens

# Starting the server #
Press the **Start server** button

# Accessing content #
If default host/port settings are used, the www content can be accessed vie the following address: http://localhost:9090/


# Fortune cookie application #
The fortune cookie sample application can be accessed via the following address:
http://localhost:9090/fortune-cookie

**Note**: content available at this address is created by a fortune teller plugin application (i.e. it works somewhat like Java Servlets)