# Joystick-Analyzer
C++ code to analyze joystick value logs, created for CASA telerobotics experiment

## Background
- We needed to record the inputs our participants were sending to the controller, which we did with the built in ROS fucntionality rosbag. This left us with thousands of lines of data to analyze
- The solution needed to allow for easy reading of data and writing of readable data

## Solution 
- Read data with C++ fstream and stored the data in a vector of vectors
- Parsed through this data and determined when a button was pushed
- Used a hash map to map indices of the vector to their corresponding buttons on our controller

## Instructions
- Clone the repo by copying the link and running `git clone`
- Compile the code
```
g++ app/main.cpp app/joystick.hpp app/joystickUtilities.cpp
```
- Run the code using the below command. You can either import your own data or use some of the same data provided in the docs folder. Be sure to name the output file something memorable! This snippet uses 
the joysticktest file in the docs folder and outputs to a file named example.txt also in the docs folder. This will overwrite the default
```
./a.out docs/joysticktest.csv docs/example.txt
```

## Limitations
- Only compatible with GNU g++ version >= 12, not sure why this is
- Data must come from the ros /joy topic or those with similar data format. This program will likely cut off data if you use another topic
- /joy must have a total input array length of either 19 or 23, otherwise the mapping will fail and provide an error
