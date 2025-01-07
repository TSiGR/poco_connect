# __POCO_CONNECT__

This console miniproject is created to transmit messages and commands between server and client through TCP connection based on socket architecture.
The standart working port of server is 12345.
The project consists of poco_tcpclient and poco_tcp folders.

Poco_tcp folder stores realization of server. Details: when object of server class is created, it waits for new connections from client. After receiving of request from client,
server handles messages itself or passes requests to methods of special object which, depending on the message, starts:

1. Array's handling to output only even numbers;
2. Get the handled files from the server;
3. Hang-Man game.

### INSTRUCTION

To try this project you need to install [CMake](https://cmake.org/download/) and [POCO library](https://github.com/pocoproject/poco?tab=readme-ov-file).
You can use this project on Windows and UNIX/Linux systems.

The standart building process includes the next commands:
````
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build . --config Release
````
