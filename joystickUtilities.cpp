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
        map[3] = "right button";
        map[4] = "left button";
        map[7] = "reset button";
        // buttons
        map[8] = "A button";
        map[9] = "B button";
        map[11] = "arm down (left trigger)";
        map[12] = "arm up (right trigger)";
        map[13] = "wrist left (left bumper)";
        map[14] = "wrist right (right bumper)";
    } 
    else if(result[0].size() == 23) 
    {
        // axes
        map[2] = "right button";
        map[3] = "left button";
        map[7] = "reset button";
        // buttons
        map[8] = "A button";
        map[9] = "B button";
        map[13] = "wrist left (left bumper)";
        map[14] = "wrist right (right bumper)";
        map[15] = "arm down (left trigger)";
        map[16] = "arm up (right trigger)";
    } 
    else { // return map -1 if joystick isnt recognized
        map[-1] = "incompatible joystick";
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
    // check if index has been mapped (to see if we care about this button)
    if(map.count(index) == 0) 
    {
        return -1;
    } else {
        int count = 0;
        for (int i = 0; i < result.size(); i++) 
        {
            // count number of times button is pressed
            if(result[i][index] != 0)
            {
                count++;
            }
        }
        return count;
    }
    
}

// writes data to file and command line, calls numOccurances to get data to write
void joystick::writeFile(string name)
{
    ofstream file;
    file.open(name);
    int temp = 0;

    for(int i = 0; i < result[0].size(); i++)
    {
        temp = numOccurences(i);
        if(temp == -1) // this happens when value isnt mapped (we dont care about that button)
        {
            continue;
        } 
        else if (map.count(-1) == 1) { 
            cout << "Incompatible joystick" << endl;
            break;   
        } 
        else {
            cout << map[i] << " was pressed " << temp << " times. " << endl;
            file << map[i] << " was pressed " << temp << " times." << endl;
        }    
    }

    file.close();
}
