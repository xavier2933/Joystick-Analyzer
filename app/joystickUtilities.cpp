/////////////////////////////////////////////////////////////////////////////////////////////
// Author: Xavier O'Keefe
//
// Purpose: fucntion definitions for joystick class
/////////////////////////////////////////////////////////////////////////////////////////////
#include "joystick.hpp"

using namespace std;

void joystick::mapValues()
{
    if(result[0].size() == 19)
    {
        // axes
        joyMap[3] = "right button";
        joyMap[4] = "left button";
        joyMap[7] = "reset button";
        // buttons
        joyMap[8] = "A button";
        joyMap[9] = "B button";
        joyMap[11] = "arm down (left trigger)";
        joyMap[12] = "arm up (right trigger)";
        joyMap[13] = "wrist left (left bumper)";
        joyMap[14] = "wrist right (right bumper)";
    } 
    else if(result[0].size() == 23) 
    {
        // axes
        joyMap[2] = "right button";
        joyMap[3] = "left button";
        joyMap[7] = "reset button";
        // buttons
        joyMap[8] = "A button";
        joyMap[9] = "B button";
        joyMap[13] = "wrist left (left bumper)";
        joyMap[14] = "wrist right (right bumper)";
        joyMap[15] = "arm down (left trigger)";
        joyMap[16] = "arm up (right trigger)";
    } 
    else { // return joyMap -1 if joystick isnt recognized
        joyMap[-1] = "incompatible joystick";
    }
}

// reads data from file and stores it in results vector
void joystick::readFile(string name)
{
    ifstream file;
    file.open(name);

    int count = 0;
    string line;
    string value;

    getline(file, line); // skips first line

    // insert each line into stringstream object s
    while (getline (file, line)) {
        vector<double> row;
        stringstream s (line);

        // read each element delimited by a comma, else go to next line
        while (getline (s, value, ','))
        {
            if (count < 4) {
                count++;
                continue;
            } else {
                count++;     
                double valueDouble = stod(value);
                row.push_back(valueDouble);
            }
        }
        result.push_back(row);
        count = 0;
    }

    file.close();
}

// counts number of times button is pressed
int joystick::numOccurences(int index)
{
    // check if index has been joyMapped (to see if we care about this button)
    if(joyMap.count(index) == 0) 
    {
        return -1;
    } else {
        int count = 0;
        for (int i = 0; i < result.size(); i++) 
        {
            // count number of times button is pressed
            if(result[i][index] != 0 && result[i-1][index] == 0)
            {
                count++;
            }
        }
        return count;
    }
    
}

// writes data to file and command line, calls numOccurances to get data to write
void joystick::writeFile(string inName, string outName)
{
    ofstream file;
    file.open(outName);
    int temp = 0;

    // print where data came from
    file << "##### Generated from " << inName  << " #####" << endl;

    for(int i = 0; i < result[0].size(); i++)
    {
        temp = numOccurences(i);
        if(temp == -1) // this happens when value isnt joyMapped (we dont care about that button)
        {
            continue;
        } 
        else if (joyMap.count(-1) == 1) { 
            cout << "Incompatible joystick" << endl;
            break;   
        } 
        else {
            cout << joyMap[i] << " was pressed " << temp << " times. " << endl;
            file << joyMap[i] << " was pressed " << temp << " times." << endl;
        }    
    }

    file.close();
}
