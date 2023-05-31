# Joystick-Analyzer
C++ code to analyze joystick value logs, created for CASA telerobotics experiment.

## Background
- We needed a way to measure the user input while operating the robot. The data were recorded using the ROS built in rosbag feauture and converted into a usable .csv format. This left us with thousands of lines of log files.
- Solution needed to be quick and allow for files to be easily named to correlate to each participant in the study

## Solution
- Used getline and stringstream to read data and store it into a vector, ignoring the junk values included by ROS
- Counted each time input was recieved and wrote this value to a file for future reference
- Used hash map to store a button name for each index value of data array for easy reference

## Instructions
- Clone the repo
- Compile 
```
g++ app/main.cpp app/joystickUtilities.cpp app/joystick.hpp
```
- Run the program with the input and output file names
```
/a.out <docs/input file.csv> <docs/output file.txt>
```
