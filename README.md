# TimeTracker

The `TimeTracker` application is aimed at helping users manage their time-logging. It can keep track of your working hours for a given projet. 

## Motivation and implementation

The real motivation of the development of this small software is to understand how web servers are working, and how to implement a small web server in c++.

## Structure

The code is structured around two sub-folders:

* `core`: implementation of the engine that manages the worked hours and persist the data
* `web`: user interface implemented as a web-server. Use localhost address on port 8080 (127.0.0.1:8080) to access the application once started. 